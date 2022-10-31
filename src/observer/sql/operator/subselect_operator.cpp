#include "sql/operator/subselect_operator.h"
#include "sql/operator/operator_factory.h"

SubSelectOperator::SubSelectOperator(SelectStmt *select_stmt, Trx *trx) : select_stmt_(select_stmt)
{
  oper_ = OperatorFactory::create(select_stmt, trx);
}

SubSelectOperator::~SubSelectOperator()
{
  delete oper_;
}

RC SubSelectOperator::HasResult(bool &ret) const
{
  RC rc = RC::SUCCESS;
  if (oper_->type() == OperatorType::AGGREGATE) {
    AggregateOperator *aggr_oper = static_cast<AggregateOperator *>(oper_);
    RC rc = aggr_oper->open();
    if (rc != RC::SUCCESS) {
      return rc;
    }
    assert(aggr_oper->aggr_fields().size() == 1);
    return RC::SUCCESS;
  } else if (oper_->type() == OperatorType::PROJECT) {
    ProjectOperator *project_oper = static_cast<ProjectOperator *>(oper_);
    RC rc = project_oper->open();
    if (rc != RC::SUCCESS) {
      return rc;
    }
    if ((rc = project_oper->next()) == RC::SUCCESS) {
      ret = true;
    } else {
      ret = false;
    }
    return RC::SUCCESS;
  } else {
    assert(false);
  }
  return rc;

}

RC SubSelectOperator::GetOneResult(TupleCell &cell) const
{
  RC rc = RC::SUCCESS;
  if (select_stmt_->exprs().size() != 1) {
    LOG_WARN("select more than one fields in sub-select");
    return RC::SQL_SYNTAX;
  }
  if (oper_->type() == OperatorType::AGGREGATE) {
    AggregateOperator *aggr_oper = static_cast<AggregateOperator *>(oper_);
    RC rc = aggr_oper->open();
    if (rc != RC::SUCCESS) {
      return rc;
    }
    assert(aggr_oper->aggr_fields().size() == 1);
    cell = aggr_oper->first_result();
  } else if (oper_->type() == OperatorType::PROJECT) {
    ProjectOperator *project_oper = static_cast<ProjectOperator *>(oper_);
    project_oper->open();
    RC rc = project_oper->next();
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot fetch even one tuple in update-select");
      return rc;
    }
    Tuple *tuple = project_oper->current_tuple();
    Expression *expr = select_stmt_->exprs()[0];
    expr->get_value(*tuple, cell);
    rc = project_oper->next();
    if (rc != RC::RECORD_EOF) {
      LOG_WARN("fetch more than one tuple in update-select");
      return RC::GENERIC_ERROR;
    }
    return RC::SUCCESS;
  } else {
    assert(false);
  }
  return rc;
}

RC SubSelectOperator::GetResultList(std::vector<TupleCell> &cells) const
{
  if (select_stmt_->exprs().size() != 1) {
    LOG_WARN("fetch more than one fields in sub select");
    return RC::SQL_SYNTAX;
  }
  RC rc = RC::SUCCESS;
  if (oper_->type() == OperatorType::AGGREGATE) {
    AggregateOperator *aggr_oper = static_cast<AggregateOperator *>(oper_);
    RC rc = aggr_oper->open();
    if (rc != RC::SUCCESS) {
      return rc;
    }
    assert(aggr_oper->aggr_fields().size() == 1);
    cells.push_back(aggr_oper->first_result());
  } else if (oper_->type() == OperatorType::PROJECT) {
    ProjectOperator *project_oper = static_cast<ProjectOperator *>(oper_);
    project_oper->open();
    Expression *expr = select_stmt_->exprs()[0];
    TupleCell cell;
    while ((rc = project_oper->next()) == RC::SUCCESS) {
      Tuple *tuple = project_oper->current_tuple();
      expr->get_value(*tuple, cell);
      cells.push_back(cell);
    }
    return RC::SUCCESS;
  } else {
    assert(false);
  }
  return rc;
}
