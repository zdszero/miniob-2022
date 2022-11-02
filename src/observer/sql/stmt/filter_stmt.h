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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include <vector>
#include <unordered_map>
#include "common/log/log.h"
#include "rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"

class Db;
class Table;
class FieldMeta;

class FilterUnit {
public:
  FilterUnit() = default;
  ~FilterUnit()
  {
    if (left_) {
      delete left_;
      left_ = nullptr;
    }
    if (right_) {
      delete right_;
      right_ = nullptr;
    }
    for (Value &v : cell_values_) {
      value_destroy(&v);
    }
    if (correlated_) {
      delete sub_select_;
    }
    if (left_is_select_) {
      delete left_select_;
    }
    if (right_is_select_) {
      delete right_select_;
    }
  }

  void set_comp(CompOp comp) { comp_ = comp; }
  void set_left(Expression *expr) { left_ = expr; }
  void set_right(Expression *expr) { right_ = expr; }
  void set_condition_type(ConditionType condition_type) { condition_type_ = condition_type; }
  void swap_left_right()
  {
    Expression *tmp = left_;
    left_ = right_;
    right_ = tmp;
    switch (comp_) {
      case EQUAL_TO: {
        comp_ = EQUAL_TO;
      } break;
      case LESS_EQUAL: {
        comp_ = GREAT_THAN;
      } break;
      case NOT_EQUAL: {
        comp_ = NOT_EQUAL;
      } break;
      case LESS_THAN: {
        comp_ = GREAT_EQUAL;
      } break;
      case GREAT_EQUAL: {
        comp_ = LESS_THAN;
      } break;
      case GREAT_THAN: {
        comp_ = LESS_EQUAL;
      } break;
      default: {
        LOG_ERROR("cannot reverse comp type\n");
        break;
      }
    }
  }
  void set_exists(bool exists) { exists_ = exists; }
  void set_cells(const std::vector<Value> &values)
  {
    cell_values_ = values;
    for (const Value &v : values) {
      in_cells_.push_back(TupleCell(v));
    }
  }
  void set_sub_select(SelectStmt *select_stmt)
  {
    correlated_ = true;
    sub_select_ = select_stmt;
  }
  void set_condition_op(ConditionOp condop) { condop_ = condop; }
  void set_left_select(SelectStmt *left_select)
  {
    left_select_ = left_select;
    left_is_select_ = true;
  }
  void set_right_select(SelectStmt *right_select)
  {
    right_select_ = right_select;
    right_is_select_ = true;
  }
  // getter
  ConditionOp condition_op() const               { return condop_;          }
  SelectStmt *sub_select() const                 { return sub_select_;      }
  SelectStmt *left_select() const                { return left_select_;     }
  SelectStmt *right_select() const               { return right_select_;    }
  bool is_correlated() const                     { return correlated_;      }
  const std::vector<TupleCell> &in_cells() const { return in_cells_;        }
  ConditionType condition_type() const           { return condition_type_;  }
  Expression *left() const                       { return left_;            }
  Expression *right() const                      { return right_;           }
  CompOp comp() const                            { return comp_;            }
  bool exists() const                            { return exists_;          }
  bool left_is_select() const                    { return left_is_select_;  }
  bool right_is_select() const                   { return right_is_select_; }

private:
  CompOp comp_ = NO_OP;
  ConditionOp condop_;
  ConditionType condition_type_;
  bool left_is_select_{false};
  bool right_is_select_{false};
  Expression *left_{nullptr};
  Expression *right_{nullptr};
  SelectStmt *left_select_{nullptr};
  SelectStmt *right_select_{nullptr};
  bool exists_{false};
  bool correlated_{false};
  SelectStmt *sub_select_{nullptr};
  std::vector<TupleCell> in_cells_;
  std::vector<Value> cell_values_;
};

class FilterStmt {
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  const std::vector<FilterUnit *> &filter_units() const
  {
    return filter_units_;
  }

public:
  static RC create(Db *db, ExprContext &ctx, Condition *conditions, int condition_num, FilterStmt *&stmt);

  static RC create_filter_unit(Db *db, ExprContext &ctx, Condition &condition, FilterUnit *&filter_unit, bool is_having=false);

private:
  std::vector<FilterUnit *> filter_units_;  // 默认当前都是AND关系
                                            //
  static RC create_filter_unit_compare(Db *db, ExprContext &ctx, Condition &condition, FilterUnit *&filter_unit);
  static RC create_filter_unit_exists(Db *db, ExprContext &ctx, Condition &condition, FilterUnit *&filter_unit);
  static RC create_filter_unit_in(Db *db, ExprContext &ctx, Condition &condition, FilterUnit *&filter_unit);
};
