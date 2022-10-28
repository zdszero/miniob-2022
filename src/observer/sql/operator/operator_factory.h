#pragma once

#include "sql/operator/join_operator.h"
#include "sql/operator/multi_scan_operator.h"
#include "sql/operator/operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/aggregate_operator.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"

class OperatorFactory {
public:
  static Operator *create(Stmt *stmt)
  {
    Operator *oper = nullptr;
    switch (stmt->type()) {
      case StmtType::SELECT:
        oper = create_select_operator(stmt);
        break;
      default:
        LOG_ERROR("stmt type %s is unknown in OperatorFactory");
        break;
    }
    return oper;
  }

  static void destory_operator(Operator *oper)
  {
    if (oper->children_.size() == 0) {
      delete oper;
      return;
    }
    for (Operator *child : oper->children_) {
      destory_operator(child);
    }
    delete oper;
  }

private:
  static Operator *create_select_operator(Stmt *stmt)
  {
    SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
    Operator *scan_oper;
    if (select_stmt->join_stmts().empty()) {
      scan_oper = new NestedScanOperator(select_stmt->tables());
    } else {
      scan_oper = new HashJoinOperator(select_stmt->tables()[0], select_stmt->join_stmts());
    }

    auto pred_oper = new PredicateOperator(select_stmt->filter_stmt());
    pred_oper->add_child(scan_oper);
    if (select_stmt->select_attributes()) {
      printf("use project operator\n");
      auto project_oper = new ProjectOperator();
      project_oper->add_child(pred_oper);
      for (Expression *expr : select_stmt->exprs()) {
        project_oper->add_projection(expr, select_stmt->tables().size() > 1);
      }
      return project_oper;
    } else {
      printf("use aggregate operator\n");
      auto aggregate_oper = new AggregateOperator(select_stmt->exprs());
      aggregate_oper->add_child(pred_oper);
      return aggregate_oper;
    }
  }
};
