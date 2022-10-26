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
// Created by wangyunlai on 2022/9/28
//

#pragma once

#include "sql/expr/expression.h"
#include <string>

std::string double2string(double v);
std::string value2string(const Value &value);
bool is_numeric_type(AttrType type);
std::string mathop_to_string(MathOp mathop);
std::string aggregate_func_string(AggrType aggr_type);
std::string comp_to_string(CompOp comp);
void print_expr(Expression *expr, int level=0);
