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
// Created by WangYunlai on 2022/07/01.
//

#pragma once

#include "sql/operator/operator.h"
#include "rc.h"
#include <unordered_map>

using NameMap = std::unordered_map<std::string, std::string>;

class ProjectOperator : public Operator
{
public:
  ProjectOperator()
  {}

  virtual ~ProjectOperator()
  {
    for (ProjectTuple *t : sorted_tuples_) {
      delete t->tuple();
      delete t;
    }
  }

  void add_projection(Expression *expr, bool is_multi_table, const NameMap &table_alias, const char *alias);
  void set_order(const std::vector<OrderPolicy> &policies, const std::vector<Expression *> &order_exprs) {
    order_policies_ = policies;
    order_exprs_ = order_exprs;
  }
  RC open() override;
  RC next() override;
  RC close() override;
  Tuple * current_tuple() override;
  OperatorType type() override
  {
    return OperatorType::PROJECT;
  }

  int tuple_cell_num() const
  {
    return tuple_.cell_num();
  }

  RC tuple_cell_spec_at(int index, const TupleCellSpec *&spec) const;

private:
  ProjectTuple tuple_;
  std::vector<OrderPolicy> order_policies_;
  std::vector<Expression *> order_exprs_;
  std::vector<ProjectTuple *> sorted_tuples_;
  size_t next_idx_{0};
};
