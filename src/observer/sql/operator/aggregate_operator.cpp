#include "sql/operator/aggregate_operator.h"
#include "common/lang/string.h"

AggregateOperator::AggregateOperator(const std::vector<AggrField> &aggr_fields) : aggr_fields_(aggr_fields)
{
  aggregators_.reserve(aggr_fields.size());
  for (size_t i = 0; i < aggr_fields.size(); i++) {
    // create aggregator
    aggregators_.push_back(Aggregator());
  }
}

RC AggregateOperator::open() {
  if (children_.size() != 1) {
    LOG_WARN("aggregate operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  while ((rc = child->next()) == RC::SUCCESS) {
    Tuple *t = child->current_tuple();
    for (size_t i = 0; i < aggr_fields_.size(); i++) {
      AggrField &aggr = aggr_fields_[i];
      aggregators_[i].add_tuple(aggr.aggr_type(), aggr.field(), t);
    }
  }

  results_.reserve(aggr_fields_.size());
  for (size_t i = 0; i < aggr_fields_.size(); i++) {
    results_.push_back(aggregators_[i].to_string());
  }

  return RC::SUCCESS;
}

RC AggregateOperator::close() {
  children_[0]->close();
  return RC::SUCCESS;
}

RC AggregateOperator::next() {
  return RC::RECORD_EOF;
}

Tuple *AggregateOperator::current_tuple() {
  return nullptr;
}
