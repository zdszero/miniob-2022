#pragma once

#include "sql/expr/expression.h"

RC check_leaf_node(ast *t, ExprContext &ctx, size_t &attr_cnt, size_t &aggr_cnt);
