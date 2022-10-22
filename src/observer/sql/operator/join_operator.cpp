#include "sql/operator/join_operator.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/stmt/filter_stmt.h"
#include <cassert>
#include <cstring>

RC HashJoinOperator::open()
{
  TupleSet tuple_set;
  RC rc = fetch_tuple_sets(table_, tuple_set);
  if (rc != RC::SUCCESS) {
    LOG_WARN("fail to fetch tuple set of table %s", table_->name());
    return rc;
  }
  ht_.Init(table_->name(), tuple_set);
  for (JoinStmt &stmt : join_stmts_) {
    RC rc = fetch_tuple_sets(stmt.join_table, tuple_set);
    if (rc != RC::SUCCESS) {
      LOG_WARN("fail to fetch tuple set of table %s", stmt.join_table->name());
      return rc;
    }
    for (FilterUnit *unit : stmt.filter_stmt->filter_units()) {
      ExprType left_type = unit->left()->type();
      ExprType right_type = unit->right()->type();
      assert(left_type != ExprType::NONE && right_type != ExprType::NONE);
      if (left_type == ExprType::FIELD && right_type == ExprType::FIELD) {
        const char *left_tbl_name = static_cast<FieldExpr *>(unit->left())->table_name();
        const char *right_tbl_name = static_cast<FieldExpr *>(unit->right())->table_name();
        if (ht_.HasTable(left_tbl_name) && ht_.HasTable(right_tbl_name)) {
          ht_.Filter(unit);
          continue;
        }
        if (!ht_.HasTable(left_tbl_name) && !ht_.HasTable(right_tbl_name)) {
          LOG_ERROR("tables %s and %s not in previous join tables\n", left_tbl_name, right_tbl_name);
          return RC::INTERNAL;
        }
        if (!ht_.HasTable(left_tbl_name)) {
          unit->swap_left_right();
        }
        FieldExpr *left_expr = static_cast<FieldExpr *>(unit->left());
        FieldExpr *right_expr = static_cast<FieldExpr *>(unit->right());
        left_tbl_name = left_expr->table_name();
        right_tbl_name = right_expr->table_name();
        assert(strcmp(right_expr->table_name(), stmt.join_table->name()) == 0);
        if (unit->comp() == CompOp::EQUAL_TO) {
          ht_.Combine(left_expr, right_expr, tuple_set);
        } else {
          ht_.Product(right_tbl_name, tuple_set);
          ht_.Filter(unit);
        }
      } else if (left_type == ExprType::FIELD || right_type == ExprType::FIELD) {
        FieldExpr *field_expr;
        if (left_type == ExprType::FIELD) {
          field_expr = static_cast<FieldExpr *>(unit->left());
        } else {
          field_expr = static_cast<FieldExpr *>(unit->right());
        }
        std::string table_name = field_expr->table_name();
        if (ht_.HasTable(table_name)) {
          ht_.Filter(unit);
        } else {
          for (auto itr = tuple_set.begin(); itr != tuple_set.end();) {
            Tuple *t = *itr;
            if (!PredicateOperator::do_filter_unit(*t, unit)) {
              itr = tuple_set.erase(itr);
            } else {
              itr++;
            }
          }
          ht_.Product(table_name, tuple_set);
        }
      } else {
        RowTuple tuple;  // unused
        if (!PredicateOperator::do_filter_unit(tuple, unit)) {
          ht_.Clear();
        } else {
          ht_.Product(stmt.join_table->name(), tuple_set);
        }
      }
    }
    // ht_.Combine(stmt.filter_stmt, tuple_set);
  }
  return RC::SUCCESS;
}

RC HashJoinOperator::next()
{
  if (index_ >= ht_.temp_table().size()) {
    return RC::RECORD_EOF;
  }
  current_tuple_ = ht_.temp_table()[index_++];
  return RC::SUCCESS;
}

RC HashJoinOperator::close()
{
  return RC::SUCCESS;
}

Tuple *HashJoinOperator::current_tuple()
{
  return &current_tuple_;
}

RC HashJoinOperator::fetch_tuple_sets(Table *tbl, TupleSet &tuple_set)
{
  tuple_set.clear();
  auto *scan_oper = new TableScanOperator(tbl);
  add_child(scan_oper);
  RC rc = scan_oper->open();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  while ((rc = scan_oper->next()) == RC::SUCCESS) {
    tuple_set.push_back(scan_oper->current_tuple_copy());
  }
  return RC::SUCCESS;
}
