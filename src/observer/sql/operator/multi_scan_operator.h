#pragma once

#include "rc.h"
#include "sql/expr/tuple.h"
#include "sql/operator/operator.h"
#include "sql/stmt/select_stmt.h"
#include "util/hash_util.h"
#include <cassert>
#include <unordered_map>
#include <vector>

using TupleSet = std::vector<Tuple *>;

struct TupleCellHasher {
public:
  hash_t operator()(const TupleCell &cell) const
  {
    AttrType type = cell.attr_type();
    size_t type_hash = HashUtil::Hash(&type);
    size_t val_hash = HashUtil::HashBytes(cell.data(), cell.length());
    return HashUtil::CombineHashes(type_hash, val_hash);
  }
};

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
  virtual ~NestedScanOperator()
  {
    for (Operator *oper : children_) {
      delete oper;
    }
  }

  RC open() override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;

private:
  std::vector<Table *> tables_;
  std::vector<TupleSet> tuple_sets_;
  CartesianTuple current_tuple_;
  TupleSetsIterator iter;
};

class HashJoinOperator : public Operator {
  using TempTable = std::vector<TupleSet>;
  using TempTableIter = TempTable::iterator;
  using TempTableIters = std::vector<TempTableIter>;
  
  class SimpleHashTable {
  public:
    void Init(const std::string &table_name, TupleSet &tuple_set)
    {
      for (Tuple *t : tuple_set) {
        temp_table_.push_back(TupleSet{t});
      }
      name_map_[table_name] = 0;
      printf("init table size: %ld\n", temp_table_.size());
    }
    void Combine(FieldExpr *left_expr, FieldExpr *right_expr, const TupleSet &right_set)
    {
      TempTable temp_table;
      ht_.clear();
      std::string left_table_name(left_expr->table_name());
      assert(name_map_.count(left_table_name));
      size_t name_idx = name_map_[left_table_name];
      printf("combine table %s with %s\n", left_table_name.c_str(), right_expr->table_name());
      // build hash table
      for (auto it = temp_table_.begin(); it != temp_table_.end(); it++) {
        Tuple *t = it->at(name_idx);
        TupleCell cell;
        RC rc = left_expr->get_value(*t, cell);
        assert(rc == RC::SUCCESS);
        if (!ht_.count(cell)) {
          ht_.insert({cell, TempTableIters{it}});
        } else {
          ht_[cell].push_back(it);
        }
      }
      // combine and filter
      for (Tuple *t : right_set) {
        TupleCell cell;
        RC rc = right_expr->get_value(*t, cell);
        assert(rc == RC::SUCCESS);
        if (!ht_.count(cell)) {
          continue;
        } else {
          TempTableIters &iters = ht_[cell];
          for (const TempTableIter &iter : iters) {
            TupleSet new_set = *iter;  // copy
            new_set.push_back(t);
            temp_table.push_back(new_set);
          }
        }
      }
      printf("combine finished\n");
      name_map_[right_expr->table_name()] = name_map_.size() + 1;
      assert(temp_table.size() <= temp_table.size());
      printf("temp tbl size: %ld -> %ld\n", temp_table_.size(), temp_table.size());
      temp_table_.swap(temp_table);
    }

    const TempTable &temp_table() { return temp_table_; }

  private:
    std::unordered_map<TupleCell, TempTableIters, TupleCellHasher> ht_;
    std::unordered_map<std::string, size_t> name_map_;
    TempTable temp_table_;
  };

public:
  HashJoinOperator(Table *table, const std::vector<JoinUnit> &join_units) : table_(table), join_units_(join_units)
  {}
  virtual ~HashJoinOperator() {
    for (Operator *oper : children_) {
      delete oper;
    }
  }

  RC open() override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;

private:
  Table *table_;
  std::vector<JoinUnit> join_units_;
  SimpleHashTable ht_;
  CartesianTuple current_tuple_;
  size_t index_{0};

  RC fetch_tuple_sets(Table *tbl, TupleSet &tuple_set);
};
