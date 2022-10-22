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

RC HashJoinOperator::open() {
  TupleSet tuple_set;
  RC rc = fetch_tuple_sets(table_, tuple_set);
  if (rc != RC::SUCCESS) {
    LOG_WARN("fail to fetch tuple set of table %s", table_->name());
    return rc;
  }
  ht_.Init(table_->name(), tuple_set);
  for (JoinUnit &unit : join_units_) {
    RC rc = fetch_tuple_sets(unit.join_table, tuple_set);
    if (rc != RC::SUCCESS) {
      LOG_WARN("fail to fetch tuple set of table %s", unit.join_table->name());
      return rc;
    }
    ht_.Combine(&unit.left, &unit.right, tuple_set);
  }
  return RC::SUCCESS;
}

RC HashJoinOperator::next() {
  if (index_ >= ht_.temp_table().size()) {
    return RC::RECORD_EOF;
  }
  current_tuple_.set_tuples(ht_.temp_table()[index_++]);
  return RC::SUCCESS;
}

RC HashJoinOperator::close() {
  return RC::SUCCESS;
}

Tuple *HashJoinOperator::current_tuple() {
  return &current_tuple_;
}

RC HashJoinOperator::fetch_tuple_sets(Table *tbl, TupleSet &tuple_set) {
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
