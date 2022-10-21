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
    if (rc == RC::FILTER_ALWAYS) {
      rc = RC::SUCCESS;
      continue;
    } else if (rc == RC::FILTER_IMPOSSIBLE) {
      tmp_stmt->filter_units_.clear();
      tmp_stmt->impossible_ = true;
      rc = RC::SUCCESS;
      break;
    } else if (rc != RC::SUCCESS) {
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
    // left = new ValueExpr(condition.left_value);
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
    // right = new ValueExpr(condition.right_value);
  }


  if (condition.left_is_attr && condition.right_is_attr) {
    rc = RC::SUCCESS;
  } else if (condition.left_is_attr && !condition.right_is_attr) {
    FieldExpr *field_expr = dynamic_cast<FieldExpr *>(left);
    rc = check_field_with_value(field_expr->field().attr_type(), condition.right_value, comp);
    right = new ValueExpr(condition.right_value);
  } else if (!condition.left_is_attr && condition.right_is_attr) {
    FieldExpr *field_expr = dynamic_cast<FieldExpr *>(right);
    rc = check_field_with_value(field_expr->field().attr_type(), condition.left_value, comp);
    left = new ValueExpr(condition.left_value);
  } else {
    left = new ValueExpr(condition.left_value);
    right = new ValueExpr(condition.right_value);
    rc = RC::SUCCESS;
  }

  if (rc != RC::FILTER_ALWAYS && rc != RC::FILTER_IMPOSSIBLE) {
    filter_unit = new FilterUnit;
    filter_unit->set_comp(comp);
    filter_unit->set_left(left);
    filter_unit->set_right(right);
  }

  return rc;
}

RC FilterStmt::check_field_with_value(AttrType field_type, Value &value, CompOp op)
{
  RC rc = RC::SUCCESS;
  if (field_type == value.type) {
    return rc;
  }
  switch (field_type) {
    case INTS:
      {
	float fv;
	int v;
	bool should_be_int = false;
	if (value.type == CHARS) {
	  fv = std::atof((char *)value.data);
	  v = std::atoi((char *)value.data);
	} else {
	  fv = *(float *)value.data;
	  v = static_cast<int>(fv);
	}
	if (fv == v) {
	  should_be_int = true;
	}
	if (!should_be_int) {
	  switch (op) {
	    case EQUAL_TO:
	      return RC::FILTER_IMPOSSIBLE;
	    case NOT_EQUAL:
	      return RC::FILTER_ALWAYS;
	    case LESS_EQUAL:
	    case GREAT_THAN:
	      break;
	    case LESS_THAN:
	    case GREAT_EQUAL:
	      v++;
	      break;
	    case STR_LIKE:
	    case STR_NOT_LIKE:
	      return RC::MISMATCH;
	    default:
	      LOG_ERROR("unknown comp\n");
	      return RC::INTERNAL;
	  }
	}
	value_destroy(&value);
	value_init_integer(&value, v);
      }
      break;
    case FLOATS:
      if (value.type == INTS) {
        float v = static_cast<float>(*(int *)value.data);
        value_destroy(&value);
        value_init_float(&value, v);
      } else {
        float v = std::atof((char *)value.data);
        value_destroy(&value);
        value_init_float(&value, v);
      }
      break;
    case CHARS:
      // cast field as number, this has to be implemented when getting real data
      break;
    case DATES:
      if (value.type == INTS) {
      } else if (value.type == FLOATS) {
        int v = static_cast<int32_t>(*(float *)value.data);
        value_destroy(&value);
        value_init_date(&value, v);
      } else {
        int32_t v;
        rc = string_to_date((char *)value.data, v);
        if (rc != RC::SUCCESS) {
          return rc;
        }
        value_destroy(&value);
        value_init_date(&value, v);
      }
      break;
    default:
      LOG_ERROR("unknown field type: %d\n", field_type);
      return RC::INTERNAL;
  }
  return rc;
}
