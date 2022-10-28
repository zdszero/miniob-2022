#pragma once

#include "rc.h"
#include "sql/expr/tuple.h"
#include "sql/operator/operator.h"
#include <vector>

class NestedScanOperator : public Operator {
  using TupleSet = std::vector<Tuple *>;
  class TupleSetsIterator {
  public:
    TupleSetsIterator() = default;
    void Init(std::vector<TupleSet> *tuple_sets)
    {
      if (tuple_sets->size() == 0) {
        end_ = true;
        return;
      }
      for (const TupleSet &set : *tuple_sets) {
        if (set.empty()) {
          end_ = true;
          return;
        }
      }
      tuple_sets_ = tuple_sets;
      indexes_.resize(tuple_sets->size(), 0);
    }

    TupleSet operator*()
    {
      TupleSet tuple_result;
      for (size_t i = 0; i < indexes_.size(); i++) {
        size_t index = indexes_[i];
        if (index < tuple_sets_->at(i).size()) {
          tuple_result.push_back(tuple_sets_->at(i)[index]);
        }
      }
      return tuple_result;
    }

    // only use prefix increment operator
    void operator++()
    {
      int i = static_cast<int>(indexes_.size() - 1);
      while (i >= 0) {
        indexes_[i]++;
        if (indexes_[i] < tuple_sets_->at(i).size()) {
          return;
        }
        indexes_[i] = 0;
        i--;
      }
      end_ = true;
    }

    bool End()
    {
      return end_;
    }

  private:
    bool end_{false};
    std::vector<TupleSet> *tuple_sets_;
    std::vector<size_t> indexes_;
  };

public:
  NestedScanOperator(const std::vector<Table *> &tables) : tables_(tables)
  {}
  virtual ~NestedScanOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;
  OperatorType type() override
  {
    return OperatorType::NESTED_SCAN;
  }

private:
  std::vector<Table *> tables_;
  std::vector<TupleSet> tuple_sets_;
  CartesianTuple current_tuple_;
  TupleSetsIterator iter;
};
