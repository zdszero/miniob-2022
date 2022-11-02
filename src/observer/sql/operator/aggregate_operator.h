#pragma once

#include "sql/operator/operator.h"
#include "util/hash_util.h"
#include "util/util.h"
#include <cassert>
#include <sstream>
#include <vector>

class FilterUnit;

struct TupleCellsHasher {
public:
  hash_t operator()(const std::vector<TupleCell> &cells) const
  {
    hash_t ret = hash_one_cell(cells[0]);
    for (size_t i = 1 ; i < cells.size(); i++) {
      ret = HashUtil::CombineHashes(ret, hash_one_cell(cells[i]));
    }
    return ret;
  }
  hash_t hash_one_cell(const TupleCell &cell) const
  {
    AttrType type = cell.attr_type();
    size_t type_hash = HashUtil::Hash(&type);
    size_t val_hash = HashUtil::HashBytes(cell.data(), cell.length());
    return HashUtil::CombineHashes(type_hash, val_hash);
  }
};

class Aggregator {
public:
  Aggregator(AggregateExpr *expr);

  void add_tuple(Tuple *t);
  std::string to_string();
  TupleCell get_result();

private:
  Field field_;
  AggrType aggr_type_;
  AttrType attr_type_;
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
  OperatorType type() override                                 { return OperatorType::AGGREGATE; }
  const std::vector<std::vector<std::string>> &results() const { return results_;                }
  const std::vector<Expression *> &aggr_fields() const         { return exprs_;                  }
  TupleCell first_result() const                               { return cell_;                   }
  void set_group_by(const std::vector<Expression *> &group_bys) {
    group_bys_ = group_bys;
    if (group_bys.size() > 0) {
      is_group_by_ = true;
    } else {
      is_group_by_ = false;
    }
  }
  void set_having(FilterUnit *having) {
    having_ = having;
  }

private:
  std::vector<Expression *> exprs_;
  AggregationTable agt_;
  std::vector<std::vector<std::string>> results_;
  TupleCell cell_;
  bool is_group_by_{false};
  std::vector<Expression *> group_bys_;
  std::unordered_map<std::vector<TupleCell>, AggregationTable, TupleCellsHasher> group_by_tbls_;
  FilterUnit *having_{nullptr};
};
