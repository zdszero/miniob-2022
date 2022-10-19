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

#include "rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/expr/expression.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "util/date.h"
#include "util/util.h"
#include <cassert>

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
		      Condition *conditions, int condition_num,
		      FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
		       const RelAttr &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name)) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(std::string(attr.relation_name));
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name);
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name);
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name);
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
				  Condition &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;
  
  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  Expression *left = nullptr;
  Expression *right = nullptr;
  if (condition.left_is_attr) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);  
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    left = new FieldExpr(table, field);
  } else {
    left = new ValueExpr(condition.left_value);
  }

  if (condition.right_is_attr) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);  
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      delete left;
      return rc;
    }
    right = new FieldExpr(table, field);
  } else {
    right = new ValueExpr(condition.right_value);
  }

  filter_unit = new FilterUnit;
  filter_unit->set_comp(comp);
  filter_unit->set_left(left);
  filter_unit->set_right(right);

  if (left->type() == ExprType::FIELD && right->type() == ExprType::FIELD) {
    LOG_ERROR("field and field filter has not been implemented yet\n");
    return RC::INTERNAL;
  } else if (left->type() == ExprType::FIELD && right->type() == ExprType::VALUE) {
    FieldExpr *field_expr = dynamic_cast<FieldExpr *>(left);
    rc = check_field_with_value(field_expr->field().attr_type(), condition.right_value);
  } else if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
    FieldExpr *field_expr = dynamic_cast<FieldExpr *>(right);
    rc = check_field_with_value(field_expr->field().attr_type(), condition.left_value);
  } else {
    rc = check_values(condition.left_value, condition.right_value);
  }

  return rc;
}

RC FilterStmt::check_field_with_value(AttrType field_type, Value &expr_value) {
  RC rc = RC::SUCCESS;
  assert(expr_value.type != DATES);
  AttrType tmp;
  switch (field_type) {
    case INTS:
    case FLOATS:
      if (!is_numeric_type(expr_value.type) && !is_number((char *)expr_value.data, tmp)) {
	return RC::MISMATCH;
      }
      break;
    case CHARS:
      if (is_numeric_type(expr_value.type)) {
      	return RC::MISMATCH;
      }
      break;
    case DATES:
      if (is_numeric_type(expr_value.type)) {
      	return RC::MISMATCH;
      }
      int32_t date;
      rc = string_to_date((char *)expr_value.data, date);
      if (rc != SUCCESS) {
      	return RC::MISMATCH;
      }
      break;
    default:
      LOG_ERROR("unknown field type: %d\n", field_type);
      return RC::INTERNAL;
  }
  return rc;
}

RC FilterStmt::check_values(Value &left, Value &right) {
  if (is_numeric_type(left.type) && is_numeric_type(right.type)) {
    return RC::SUCCESS;
  }
  if (left.type == CHARS && right.type == CHARS) {
    return RC::SUCCESS;
  }
  // char and numeric
  AttrType tmp;
  if (left.type == CHARS && !is_number((char *)left.data, tmp)) {
    return RC::MISMATCH;
  }
  if (right.type == CHARS && !is_number((char *)right.data, tmp)) {
    return RC::MISMATCH;
  }
  return RC::SUCCESS;
}
