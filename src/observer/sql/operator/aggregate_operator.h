#pragma once

#include "sql/expr/tuple.h"
#include "sql/parser/parse_defs.h"
#include "sql/operator/operator.h"
#include "util/util.h"
#include <cassert>
#include <sstream>
#include <vector>

class Aggregator {
public:
  Aggregator() = default;

  void add_tuple(AggrType aggr_type, const Field &field, Tuple *t)
  {
    aggr_type_ = aggr_type;
    bool is_star = (field.meta() == nullptr);
    if (is_star) {
      assert(aggr_type == COUNTS);
      count_++;
      return;
    }
    switch (aggr_type) {
      case MAXS: {
        if (!first_time_) {
          TupleCell cell;
          RC rc = t->find_cell(field, cell);
          int compare_res = cell.compare(cell_);
          assert(rc == RC::SUCCESS);
          if (compare_res > 0) {
            cell_ = cell;
          }
        } else {
          RC rc = t->find_cell(field, cell_);
          assert(rc == RC::SUCCESS);
        }
      } break;
      case MINS: {
        if (!first_time_) {
          TupleCell cell;
          RC rc = t->find_cell(field, cell);
          int compare_res = cell.compare(cell_);
          assert(rc == RC::SUCCESS);
          if (compare_res < 0) {
            cell_ = cell;
          }
        } else {
          RC rc = t->find_cell(field, cell_);
          assert(rc == RC::SUCCESS);
        }
      } break;
      case AVGS: {
        count_++;
        RC rc = t->find_cell(field, cell_);
        assert(rc == RC::SUCCESS);
        sum_ += cell_.cast_to_number();
      } break;
      case SUMS: {
        RC rc = t->find_cell(field, cell_);
        assert(rc == RC::SUCCESS);
        sum_ += cell_.cast_to_number();
      } break;
      case COUNTS:
        count_++;
        break;
      default:
        LOG_ERROR("unknown aggregation type\n");
        break;
    }
    first_time_ = false;
  }

  std::string to_string()
  {
    switch (aggr_type_) {
      case MAXS:
      case MINS: {
        std::stringstream ss;
        cell_.to_string(ss);
        return ss.str();
      }
      case AVGS: {
        float avg = sum_ / count_;
        return double2string((double)avg);
      }
      case SUMS: {
        if (attr_type_ == INTS || attr_type_ == DATES) {
          return std::to_string(static_cast<int>(sum_));
        }
        return double2string((double)sum_);
      }
      case COUNTS: {
        return std::to_string(count_);
      }
      default:
        LOG_ERROR("unknown aggregation type\n");
        break;
    }
    return "";
  }

private:
  AggrType aggr_type_;
  AttrType attr_type_;
  bool first_time_{true};
  TupleCell cell_;
  float sum_{0};
  int count_{0};
};

class AggregateOperator : public Operator {
public:
  AggregateOperator(const std::vector<Expression *> &exprs);
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
    return aggr_fields_;
  }

private:
  std::vector<Expression *> aggr_fields_;
  std::vector<Aggregator> aggregators_;
  std::vector<std::string> results_;
};
