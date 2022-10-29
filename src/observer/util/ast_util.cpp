#include "util/ast_util.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "util/util.h"
#include <cassert>
#include <cstdlib>
#include <sstream>

static bool can_evaluate(ast *t)
{
  if (t == nullptr) {
    return true;
  }
  assert(t->nodetype != NodeType::UNDEFINEDN);
  if (t->nodetype == NodeType::OPN) {
    return can_evaluate(t->op.left) && can_evaluate(t->op.right);
  } else if (t->nodetype == NodeType::VALN) {
    return true;
  } else {
    return false;
  }
}

static bool is_null(ast *t)
{
  if (t == nullptr) {
    return false;
  }
  if (t->nodetype == NodeType::OPN) {
    return is_null(t->op.left) || is_null(t->op.right);
  } else if (t->nodetype == NodeType::VALN) {
    return (t->val.type == NULLS);
  } else {
    return false;
  }
}

static float get_float_value(Value *v)
{
  float ret = 0;
  switch (v->type) {
    case INTS:
      ret = static_cast<float>(*(int *)v->data);
      break;
    case FLOATS:
      ret = *(float *)v->data;
      break;
    case CHARS:
      ret = std::atof((char *)v->data);
      break;
    case DATES:
      ret = static_cast<float>(*(int32_t *)v->data);
      break;
    case NULLS:
    default:
      assert(false);
  }
  return ret;
}

static float evaluate_util(ast *t)
{
  if (t == nullptr) {
    return 0;
  }
  if (t->nodetype == NodeType::OPN) {
    switch (t->op.mathop) {
      case MATH_ADD:
        return evaluate_util(t->op.left) + evaluate_util(t->op.right);
      case MATH_SUB:
        return evaluate_util(t->op.left) - evaluate_util(t->op.right);
      case MATH_MUL:
        return evaluate_util(t->op.left) * evaluate_util(t->op.right);
      case MATH_DIV:
        return evaluate_util(t->op.left) / evaluate_util(t->op.right);
      default:
        assert(false);
    }
  } else if (t->nodetype == NodeType::VALN) {
    return get_float_value(&t->val);
  } else {
    assert(false);
  }
}

bool evaluate(ast* &t)
{
  assert(t != nullptr);
  // has ATTRN inside
  if (!can_evaluate(t)) {
    return false;
  }
  if (t->nodetype == VALN) {
    return true;
  }
  if (is_null(t)) {
    node_destroy(t);
    Value new_val;
    value_init_null(&new_val);
    t = new_value_node(&new_val);
    return true;
  }
  float res = evaluate_util(t);
  node_destroy(t);
  Value new_val;
  value_init_float(&new_val, res);
  t = new_value_node(&new_val);
  return true;
}

static void ast_to_string_helper(ast *t, std::ostream &os) {
  if (t == nullptr) {
    return;
  }
  for (int i = 0; i < t->l_brace; i++) {
    os << "(";
  }
  if (t->nodetype == NodeType::VALN) {
    os << value2string(t->val);
  } else if (t->nodetype == NodeType::ATTRN) {
    if (t->attr.relation_name != nullptr) {
      os << t->attr.relation_name << ".";
    }
    os << t->attr.attribute_name;
  } else if (t->nodetype == NodeType::AGGRN) {
    os << aggregate_func_string(t->aggr.aggr_type) << "(";
    if (t->aggr.attr.relation_name != nullptr) {
      os << t->aggr.attr.relation_name << ".";
    }
    os << t->aggr.attr.attribute_name;
    os << ")";
  } else if (t->nodetype == NodeType::OPN) {
    ast_to_string_helper(t->op.left, os);
    os << mathop_to_string(t->op.mathop);
    ast_to_string_helper(t->op.right, os);
  }
  for (int i = 0; i < t->r_brace; i++) {
    os << ")";
  }
}

std::string ast_to_string(ast *t)
{
  std::stringstream ss;
  ast_to_string_helper(t, ss);
  return ss.str();
}
