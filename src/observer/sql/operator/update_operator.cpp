#include <cstring>

#include "sql/operator/update_operator.h"
#include "sql/stmt/update_stmt.h"
#include "storage/common/field_meta.h"

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
    rc = update_data(record_data, update_stmt_->update_field_meta(), update_stmt_->update_value());
    if (rc != RC::SUCCESS) {
      return rc;
    }
    record.set_data(record_data);
    rc = table->update_record(trx_, &record);
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

RC UpdateOperator::update_data(char *data, const FieldMeta *meta, const Value &val) {
  if (meta->type() != val.type) {
    LOG_ERROR("update meta's type and val's type are not equal\n");
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }
  if (meta->type() == CHARS) {
    int copy_len = strlen((char *)val.data);
    if (copy_len > meta->len()) {
      copy_len = meta->len();
    }
    strncpy(data + meta->offset(), (char *)val.data, copy_len);
    *(static_cast<char *>(data + meta->offset() + copy_len)) = '\0';
  } else {
    memcpy(data + meta->offset(), val.data, meta->len());
  }
  return RC::SUCCESS;
}
