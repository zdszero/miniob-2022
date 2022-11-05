#include "util/check.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include <cstring>

inline bool is_star(const char *name)
{
  if (name == nullptr) {
    return false;
  }
  return std::strcmp("*", name) == 0;
}

static RC check_attribute(const RelAttr &attr, ExprContext &ctx)
{
  const char *table_name = attr.relation_name;
  const char *field_name = attr.attribute_name;
  if (common::is_blank(table_name)) {
    // id from tbl1, tbl2
    if (strcmp("*", field_name) != 0 && ctx.GetTableSize() > 1) {
      LOG_WARN("invalid. I do not know the attr's table. attr=%s", table_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
  } else {
    // *.id
    if (strcmp("*", table_name) == 0 && strcmp("*", field_name) != 0) {
      LOG_WARN("invalid field name while table is *. attr=%s", field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    // inexist_table.attr
    if (!ctx.HasTable(table_name)) {
      LOG_WARN("no such table in from list: %s", table_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
  }
  // t.invalid_id from t
  if (strcmp("*", field_name) != 0) {
    Table *tbl = ctx.GetTable(attr);
    const TableMeta &table_meta = tbl->table_meta();
    const FieldMeta *field_meta = table_meta.field(field_name);
    if (field_meta == nullptr) {
      LOG_WARN("no such field. field=%s.%s", table_name, field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    ctx.AddFieldMeta(attr, field_meta);
  }
  return RC::SUCCESS;
}

static RC check_attribute_node(ast *t, ExprContext &ctx, size_t &attr_cnt, size_t &aggr_cnt)
{
  assert(t->nodetype == NodeType::ATTRN);
  RC rc = check_attribute(t->attr, ctx);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  attr_cnt++;
  return RC::SUCCESS;
}

static RC check_aggregate_node(ast *t, ExprContext &ctx, size_t &attr_cnt, size_t &aggr_cnt)
{
  assert(t->nodetype == NodeType::AGGRN);
  if (t->aggr.is_attr) {
    RC rc = check_attribute(t->aggr.attr, ctx);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    const char *field_name = t->aggr.attr.attribute_name;
    if (is_star(field_name) && t->aggr.aggr_type != AggrType::COUNTS) {
      LOG_WARN("aggregate * with invalid aggregate function\n");
      return RC::SQL_SYNTAX;
    }
  } else {
    // do nothing
  }
  aggr_cnt++;
  return RC::SUCCESS;
}

static RC check_func_node(ast *t, ExprContext &ctx, size_t &attr_cnt, size_t &aggr_cnt)
{
  assert(t->nodetype == NodeType::FUNCN);
  RC rc = RC::SUCCESS;
  FuncType functype = t->func.functype;
  if (t->func.left->nodetype != NodeType::ATTRN && t->func.left->nodetype != NodeType::VALN) {
    LOG_WARN("func can only have attribute or value as first child");
    return RC::SQL_SYNTAX;
  }
  rc = check_leaf_node(t->func.left, ctx, attr_cnt, aggr_cnt);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  if (functype == LENGTHF) {
    if (t->func.left->nodetype == NodeType::VALN && t->func.left->val.type != CHARS) {
      LOG_WARN("length() func can only have chars as argument");
      return RC::SQL_SYNTAX;
    }
  } else {
    if (functype == ROUNDF && t->func.right == nullptr) {
      return RC::SUCCESS;
    }
    if (t->func.right->nodetype != NodeType::VALN) {
      LOG_WARN("round() and date_format() can only have value as 2nd child");
      return RC::SQL_SYNTAX;
    }
    rc = check_leaf_node(t->func.right, ctx, attr_cnt, aggr_cnt);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    if (functype == ROUNDF) {
      if (t->func.right->val.type != INTS) {
        LOG_WARN("round() func can only have ints as 2nd argument");
        return RC::SQL_SYNTAX;
      }
    }
    if (functype == DATE_FORMATF) {
      if (t->func.right->val.type != CHARS) {
        LOG_WARN("date_format() func can only have chars as 2nd argument");
        return RC::SQL_SYNTAX;
      }
    }
  }
  return RC::SUCCESS;
}

RC check_leaf_node(ast *t, ExprContext &ctx, size_t &attr_cnt, size_t &aggr_cnt)
{
  if (t == nullptr) {
    return RC::SUCCESS;
  }
  assert(t->nodetype != NodeType::UNDEFINEDN);
  RC rc = RC::SUCCESS;
  if (t->nodetype == NodeType::ATTRN) {
    rc = check_attribute_node(t, ctx, attr_cnt, aggr_cnt);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  } else if (t->nodetype == NodeType::AGGRN) {
    rc = check_aggregate_node(t, ctx, attr_cnt, aggr_cnt);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  } else if (t->nodetype == NodeType::VALN) {
    // do nothing
  } else if (t->nodetype == NodeType::OPN) {
    rc = check_leaf_node(t->op.left, ctx, attr_cnt, aggr_cnt);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    rc = check_leaf_node(t->op.right, ctx, attr_cnt, aggr_cnt);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    if (aggr_cnt > 0 && attr_cnt > 0) {
      LOG_WARN("attribute and aggregate cannot used in expression together\n");
      return RC::SQL_SYNTAX;
    }
  } else if (t->nodetype == NodeType::FUNCN) {
    return check_func_node(t, ctx, attr_cnt, aggr_cnt);
  }
  return rc;
}
