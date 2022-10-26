#pragma once

#include "sql/expr/tuple.h"
#include "sql/parser/parse_defs.h"
#include "sql/operator/operator.h"
#include "util/hash_util.h"
#include "util/util.h"
#include <cassert>
#include <sstream>
#include <vector>

class Aggregator {
public:
  Aggregator(AggregateExpr *expr) : field_(expr->field()), aggr_type_(expr->aggr_type())
  {}

  void add_tuple(Tuple *t);
  std::string to_string();
  TupleCell get_result();

private:
  Field field_;
  AggrType aggr_type_;
  AttrType attr_type_;
  bool first_time_{true};
  TupleCell cell_;
  float sum_{0};
  float avg_;
  int count_{0};
};

class AggregationTable {
public:
  AggregationTable() = default;
  void add_expr(AggregateExpr *expr);
  void add_tuple(Tuple *t);
  TupleCell get_result(AggregateExpr *expr);

private:
  std::unordered_map<AggregateExpr *, Aggregator> ht_;
};

class AggregateOperator : public Operator {
public:
  AggregateOperator(const std::vector<Expression *> &exprs) : exprs_(exprs)
  {}
  virtual ~AggregateOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;

  const std::vector<std::string> &results() const
  {
    return results_;
  }
  const std::vector<Expression *> &aggr_fields() const
  {
    return exprs_;
  }

private:
  std::vector<Expression *> exprs_;
  AggregationTable agt_;
  std::vector<std::string> results_;
};
