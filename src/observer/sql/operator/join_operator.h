/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2021/6/10.
//

#pragma once

#include "sql/expr/tuple.h"
#include "sql/operator/predicate_operator.h"
#include "sql/parser/parse.h"
#include "sql/operator/operator.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "util/hash_util.h"
#include "rc.h"
#include <unordered_map>

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

class HashJoinOperator : public Operator {
  using TupleSet = std::vector<Tuple *>;
  using TempTable = std::vector<CartesianTuple>;
  using TempTableIter = TempTable::iterator;
  using TempTableIters = std::vector<TempTableIter>;
  
  class SimpleHashTable {
  public:
    void Init(const std::string &table_name, TupleSet &tuple_set)
    {
      for (Tuple *t : tuple_set) {
        temp_table_.push_back({t});
      }
      name_map_[table_name] = last_index_++;
      printf("init table size: %ld with %s\n", temp_table_.size(), table_name.c_str());
    }
    void Combine(FieldExpr *left_expr, FieldExpr *right_expr, const TupleSet &right_set)
    {
      TempTable temp_table;
      ht_.clear();
      std::string left_table_name(left_expr->table_name());
      assert(name_map_.count(left_table_name));
      printf("combine table %s with %s\n", left_table_name.c_str(), right_expr->table_name());
      // build hash table
      for (auto it = temp_table_.begin(); it != temp_table_.end(); it++) {
        TupleCell cell;
        RC rc = left_expr->get_value(*it, cell);
        assert(rc == RC::SUCCESS);
        if (cell.attr_type() == NULLS) {
          continue;
        }
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
        if (cell.attr_type() == NULLS) {
          continue;
        }
        assert(rc == RC::SUCCESS);
        if (!ht_.count(cell)) {
          continue;
        } else {
          TempTableIters &iters = ht_[cell];
          for (const TempTableIter &iter : iters) {
            CartesianTuple new_cartesian_tuple = *iter;
            new_cartesian_tuple.add_tuple(t);
            temp_table.push_back(new_cartesian_tuple);
          }
        }
      }
      printf("combine finished\n");
      name_map_[right_expr->table_name()] = last_index_++;
      printf("temp tbl size: %ld -> %ld\n", temp_table_.size(), temp_table.size());
      temp_table_.swap(temp_table);
    }
    void Product(const std::string &join_table, TupleSet &tuple_set) {
      printf("product %ldx%ld with %s\n", temp_table_.size(), tuple_set.size(), join_table.c_str());
      TempTable temp_table;
      for (const CartesianTuple &origin : temp_table_) {
        for (Tuple *t : tuple_set) {
          CartesianTuple new_cartesian_tuple = origin;
          new_cartesian_tuple.add_tuple(t);
          temp_table.push_back(new_cartesian_tuple);
        }
      }
      printf("temp tbl size: %ld -> %ld\n", temp_table_.size(), temp_table.size());
      name_map_[join_table] = last_index_++;
      temp_table_.swap(temp_table);
    }
    void Filter(const FilterUnit *filter_unit) {
      printf("filter\n");
      for (auto it = temp_table_.begin(); it != temp_table_.end();) {
        if (!PredicateOperator::do_filter_unit(*it, filter_unit)) {
          it = temp_table_.erase(it);
        } else {
          ++it;
        }
      }
      printf("temp tbl size: %ld\n", temp_table_.size());
    }
    void Clear() {
      temp_table_.clear();
      printf("clear, temp tbl size: %ld\n", temp_table_.size());
    }
    bool HasTable(const std::string &table_name) { return name_map_.count(table_name); }

    const TempTable &temp_table() { return temp_table_; }

  private:
    std::unordered_map<TupleCell, TempTableIters, TupleCellHasher> ht_;
    std::unordered_map<std::string, size_t> name_map_;
    TempTable temp_table_;
    size_t last_index_{0};
  };

public:
  HashJoinOperator(Table *table, const std::vector<JoinStmt> &join_stmts) : table_(table), join_stmts_(join_stmts)
  {}
  virtual ~HashJoinOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;
  OperatorType type() override
  {
    return OperatorType::JOIN;
  }

private:
  Table *table_;
  std::vector<JoinStmt> join_stmts_;
  SimpleHashTable ht_;
  CartesianTuple current_tuple_;
  size_t index_{0};

  RC fetch_tuple_sets(Table *tbl, TupleSet &tuple_set);
};
