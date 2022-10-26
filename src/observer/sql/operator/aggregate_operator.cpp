#include "sql/operator/aggregate_operator.h"
#include "common/lang/string.h"

static void collect_aggr_exprs(Expression *expr, std::vector<AggregateExpr *> &aggr_exprs)
{
  if (expr == nullptr) {
    return;
  }
  if (expr->type() == ExprType::COMPOUND) {
    CompoundExpr *compound_expr = static_cast<CompoundExpr *>(expr);
    Expression *left = compound_expr->get_left_expr();
    Expression *right = compound_expr->get_right_expr();
    collect_aggr_exprs(left, aggr_exprs);
    collect_aggr_exprs(right, aggr_exprs);
  } else if (expr->type() == ExprType::AGGREGATE) {
    AggregateExpr *aggr_expr = static_cast<AggregateExpr *>(expr);
    aggr_exprs.push_back(aggr_expr);
  }
}

static std::string evaluate_expr(Expression *expr)
{
  assert(expr->type() != ExprType::FIELD);
  RowTuple unused;
  TupleCell cell;
  expr->get_value(unused, cell);
  std::stringstream ss;
  cell.to_string(ss);
  return ss.str();
}

void Aggregator::add_tuple(Tuple *t)
{
  bool is_star = (field_.meta() == nullptr);
  if (is_star) {
    assert(aggr_type_ == COUNTS);
    count_++;
    return;
  }
  switch (aggr_type_) {
    case MAXS: {
      if (!first_time_) {
        TupleCell cell;
        RC rc = t->find_cell(field_, cell);
        int compare_res = cell.compare(cell_);
        assert(rc == RC::SUCCESS);
        if (compare_res > 0) {
          cell_ = cell;
        }
      } else {
        RC rc = t->find_cell(field_, cell_);
        assert(rc == RC::SUCCESS);
      }
    } break;
    case MINS: {
      if (!first_time_) {
        TupleCell cell;
        RC rc = t->find_cell(field_, cell);
        int compare_res = cell.compare(cell_);
        assert(rc == RC::SUCCESS);
        if (compare_res < 0) {
          cell_ = cell;
        }
      } else {
        RC rc = t->find_cell(field_, cell_);
        assert(rc == RC::SUCCESS);
      }
    } break;
    case AVGS: {
      count_++;
      RC rc = t->find_cell(field_, cell_);
      assert(rc == RC::SUCCESS);
      sum_ += cell_.cast_to_number();
    } break;
    case SUMS: {
      RC rc = t->find_cell(field_, cell_);
      assert(rc == RC::SUCCESS);
      sum_ += cell_.cast_to_number();
    } break;
    case COUNTS:
      count_++;
      break;
    default:
      LOG_ERROR("unknown aggregation type\n");
      break;
  }
  first_time_ = false;
}

TupleCell Aggregator::get_result()
{
  if (aggr_type_ == MAXS || aggr_type_ == MINS) {
    return cell_;
  } else if (aggr_type_ == SUMS) {
    return TupleCell(FLOATS, (char *)&sum_);
  } else if (aggr_type_ == COUNTS) {
    return TupleCell(INTS, (char *)&count_);
  } else if (aggr_type_ == AVGS) {
    avg_ = sum_ / count_;
    return TupleCell(FLOATS, (char *)&avg_);
  } else {
    assert(false);
  }
}

void AggregationTable::add_expr(AggregateExpr *expr)
{
  auto iter = ht_.find(expr);
  if (iter != ht_.end()) {
    return;
  }
  ht_.insert({expr, Aggregator(expr)});
}

void AggregationTable::add_tuple(Tuple *t)
{
  for (auto it = ht_.begin(); it != ht_.end(); it++) {
    it->second.add_tuple(t);
  }
}

TupleCell AggregationTable::get_result(AggregateExpr *expr)
{
  assert(ht_.count(expr));
  return ht_.at(expr).get_result();
}

RC AggregateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("aggregate operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  // collect all aggregate exprssions
  std::vector<AggregateExpr *> aggr_exprs;
  for (Expression *expr : exprs_) {
    if (expr->type() == ExprType::AGGREGATE) {
      aggr_exprs.push_back(static_cast<AggregateExpr *>(expr));
    } else if (expr->type() == ExprType::VALUE) {
      continue;
    } else if (expr->type() == ExprType::COMPOUND) {
      print_expr(expr, 0);
      collect_aggr_exprs(static_cast<CompoundExpr *>(expr), aggr_exprs);
    }
  }
  printf("aggregates size: %ld\n", aggr_exprs.size());

  // add all tuples to hash table
  for (AggregateExpr *expr : aggr_exprs) {
    agt_.add_expr(expr);
  }

  while ((rc = child->next()) == RC::SUCCESS) {
    Tuple *t = child->current_tuple();
    agt_.add_tuple(t);
  }

  for (AggregateExpr *expr : aggr_exprs) {
    expr->set_cell(agt_.get_result(expr));
  }

  results_.reserve(exprs_.size());
  for (Expression *expr : exprs_) {
    results_.push_back(evaluate_expr(expr));
  }

  return RC::SUCCESS;
}

RC AggregateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

RC AggregateOperator::next()
{
  return RC::RECORD_EOF;
}

Tuple *AggregateOperator::current_tuple()
{
  return nullptr;
}
