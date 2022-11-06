#pragma once

#include "sql/operator/delete_operator.h"
#include "sql/operator/join_operator.h"
#include "sql/operator/no_table_operator.h"
#include "sql/operator/operator.h"
#include "sql/operator/multi_scan_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/aggregate_operator.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/operator/update_operator.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/update_stmt.h"
#include "storage/trx/trx.h"

class OperatorFactory {
public:
  static Operator *create(Stmt *stmt, Trx *trx)
  {
    Operator *oper = nullptr;
    switch (stmt->type()) {
      case StmtType::SELECT:
        oper = create_select_operator(static_cast<SelectStmt *>(stmt), trx);
        break;
      case StmtType::UPDATE:
        oper = create_update_operator(static_cast<UpdateStmt *>(stmt), trx);
        break;
      case StmtType::DELETE:
        oper = create_delete_operator(static_cast<DeleteStmt *>(stmt), trx);
        break;
      default:
        LOG_ERROR("stmt type %s is unknown in OperatorFactory");
        break;
    }
    return oper;
  }

private:
  static Operator *create_select_operator(SelectStmt *select_stmt, Trx *trx)
  {
    // Operator *scan_oper = try_to_create_index_scan_operator(select_stmt->filter_stmt());
    // if (nullptr == scan_oper) {
    //   scan_oper = new TableScanOperator(table);
    // }
    Operator *scan_oper = nullptr;
    Operator *pred_oper = nullptr;
    Operator *no_table_oper = nullptr;
    bool has_table = true;
    if (select_stmt->tables().size() == 0) {
      has_table = false;
    }
    if (has_table) {
      if (select_stmt->join_stmts().empty()) {
        scan_oper = new NestedScanOperator(select_stmt->tables());
      } else {
        scan_oper = new HashJoinOperator(select_stmt->tables()[0], select_stmt->join_stmts());
      }
      pred_oper = new PredicateOperator(select_stmt->filter_stmt());
      pred_oper->add_child(scan_oper);
    } else {
      no_table_oper = new NoTableOperator();
    }

    if (select_stmt->select_attributes()) {
      auto project_oper = new ProjectOperator();
      if (has_table) {
        project_oper->add_child(pred_oper);
      } else {
        project_oper->add_child(no_table_oper);
      }
      size_t idx = 0;
      for (Expression *expr : select_stmt->exprs()) {
        project_oper->add_projection(expr, select_stmt->tables().size() > 1, select_stmt->table_alias(), select_stmt->field_alias()[idx]);
        idx++;
      }
      return project_oper;
    } else {
      auto aggregate_oper = new AggregateOperator(select_stmt->exprs());
      aggregate_oper->add_child(pred_oper);
      return aggregate_oper;
    }
  }

  static Operator *create_update_operator(UpdateStmt *update_stmt, Trx *trx)
  {
    TableScanOperator *scan_oper = new TableScanOperator(update_stmt->table());
    PredicateOperator *pred_oper = new PredicateOperator(update_stmt->filter_stmt());
    pred_oper->add_child(scan_oper);
    UpdateOperator *update_oper = new UpdateOperator(update_stmt, trx);
    update_oper->add_child(pred_oper);
    return update_oper;
  }

  static Operator *create_delete_operator(DeleteStmt *delete_stmt, Trx *trx)
  {
    TableScanOperator* scan_oper = new TableScanOperator(delete_stmt->table());
    PredicateOperator* pred_oper = new PredicateOperator(delete_stmt->filter_stmt());
    pred_oper->add_child(scan_oper);
    DeleteOperator *delete_oper = new DeleteOperator(delete_stmt, trx);
    delete_oper->add_child(pred_oper);
    return delete_oper;
  }
};
