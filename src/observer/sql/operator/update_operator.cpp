#include <cstring>

#include "common/lang/defer.h"
#include "sql/operator/update_operator.h"
#include "sql/operator/operator_factory.h"
#include "sql/stmt/update_stmt.h"
#include "storage/common/field_meta.h"
#include "util/util.h"

RC UpdateOperator::open() {
  if (children_.size() != 1) {
    LOG_WARN("delete operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  std::vector<Value> update_vals(update_stmt_->units().size());
  for (size_t pair_num = 0; pair_num < update_stmt_->units().size(); pair_num++) {
    value_init_null(&update_vals[pair_num]);
  }
  DEFER([&update_vals]() {
    for (auto &val : update_vals) {
      value_destroy(&val);
    }
  });
  for (size_t pair_num = 0; pair_num < update_stmt_->units().size(); pair_num++) {
    auto &unit = update_stmt_->units()[pair_num];
    if (unit.is_select) {
      SelectStmt *select_stmt = unit.select_stmt;
      Operator *oper = OperatorFactory::create(select_stmt, nullptr);
      DEFER([oper](){ delete oper; });
      if (oper->type() == OperatorType::AGGREGATE) {
        AggregateOperator *aggr_oper = static_cast<AggregateOperator *>(oper);
        aggr_oper->open();
        assert(aggr_oper->aggr_fields().size() == 1);
        TupleCell cell = aggr_oper->first_result();
        update_vals[pair_num] = cell.to_value();
      } else if (oper->type() == OperatorType::PROJECT) {
        ProjectOperator *project_oper = static_cast<ProjectOperator *>(oper);
        project_oper->open();
        RC rc = project_oper->next();
        if (rc != RC::SUCCESS) {
          LOG_WARN("cannot fetch even one tuple in update-select");
          return rc;
        }
        Tuple *tuple = project_oper->current_tuple();
        assert(select_stmt->exprs().size() == 1);
        Expression *expr = select_stmt->exprs()[0];
        TupleCell cell;
        expr->get_value(*tuple, cell);
        update_vals[pair_num] = cell.to_value();
        rc = project_oper->next();
        if (rc != RC::RECORD_EOF) {
          LOG_WARN("fetch more than one tuple in update-select");
          return RC::GENERIC_ERROR;
        }
      } else {
        assert(false);
      }
    }
  }

  Table *table = update_stmt_->table();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();
    char *record_data = record.data();
    int record_len = table->table_meta().record_size();
    char *new_data = (char *)malloc(record_len);
    memcpy(new_data, record_data, record_len);
    Record new_record;
    for (size_t pair_num = 0; pair_num < update_stmt_->units().size(); pair_num++) {
      auto &unit = update_stmt_->units()[pair_num];
      if (unit.is_select) {
        // update_val has been set
      } else {
        Expression * expr = unit.update_expr;
        TupleCell cell;
        rc = expr->get_value(*tuple, cell);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("failed to get value in update operator");
          return rc;
        }
        update_vals[pair_num] = cell.to_value();
      }
      rc = update_data(new_data, unit.update_field_meta, update_vals[pair_num]);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
    new_record.set_data(new_data);
    new_record.set_rid(record.rid());
    rc = table->update_record(trx_, &record, &new_record);
    free(new_data);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC UpdateOperator::next() {
  return RC::RECORD_EOF;
}

RC UpdateOperator::close() {
  children_[0]->close();
  return RC::SUCCESS;
}

RC UpdateOperator::update_data(char *data, const FieldMeta *meta, Value &val) {
  RC rc;
  if ((rc = try_to_cast_value(meta->type(), meta->nullable(), val)) != RC::SUCCESS) {
    return rc;
  }
  if (val.type == NULLS) {
    set_mem_null(data + meta->offset(), meta->type(), meta->len());
  } else {
    if (meta->type() == CHARS) {
      int copy_len = strlen((char *)val.data);
      if (copy_len > meta->len()) {
        copy_len = meta->len();
      }
      strncpy(data + meta->offset(), (char *)val.data, copy_len);
      if (copy_len < meta->len()) {
        *(static_cast<char *>(data + meta->offset() + copy_len)) = '\0';
      }
    } else {
      memcpy(data + meta->offset(), val.data, meta->len());
    }
  }
  return RC::SUCCESS;
}
