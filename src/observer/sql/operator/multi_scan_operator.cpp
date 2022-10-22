#include "multi_scan_operator.h"
#include "sql/operator/table_scan_operator.h"
#include <cassert>

RC NestedScanOperator::open() {
  RC rc = RC::SUCCESS;
  for (Table *table : tables_) {
    add_child(new TableScanOperator(table));
  }
  for (Operator *oper : children_) {
    rc = oper->open();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("fail to open child operator\n");
      return rc;
    }
  }
  for (Operator *oper : children_) {
    TupleSet tuple_set;
    TableScanOperator *scan_oper = static_cast<TableScanOperator *>(oper);
    while ((rc = oper->next()) == RC::SUCCESS) {
      tuple_set.push_back(scan_oper->current_tuple_copy());
    }
    tuple_sets_.push_back(tuple_set);
  }
  iter.Init(&tuple_sets_);
  return RC::SUCCESS;
}

RC NestedScanOperator::next() {
  if (iter.End()) {
    return RC::RECORD_EOF;
  }
  current_tuple_.set_tuples(*iter);
  ++iter;
  return RC::SUCCESS;
}

RC NestedScanOperator::close() {
  RC rc = RC::SUCCESS;
  for (Operator *oper : children_) {
    rc = oper->close();
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  return rc;
}


Tuple *NestedScanOperator::current_tuple()
{
  return &current_tuple_;
}
