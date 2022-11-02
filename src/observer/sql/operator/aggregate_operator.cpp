#include "sql/operator/aggregate_operator.h"
#include "common/lang/string.h"
#include "sql/operator/predicate_operator.h"

Aggregator::Aggregator(AggregateExpr *expr) : field_(expr->field()), aggr_type_(expr->aggr_type())
{
  cell_.set_type(NULLS);
}

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
      TupleCell cell;
      RC rc = t->find_cell(field_, cell);
      if (cell.attr_type() == NULLS) {
        return;
      }
      if (cell_.attr_type() == NULLS) {
        cell_ = cell;
        return;
      }
      int compare_res = cell.compare(cell_);
      assert(rc == RC::SUCCESS);
      if (compare_res > 0) {
        cell_ = cell;
      }
    } break;
    case MINS: {
      TupleCell cell;
      RC rc = t->find_cell(field_, cell);
      if (cell.attr_type() == NULLS) {
        return;
      }
      if (cell_.attr_type() == NULLS) {
        cell_ = cell;
        return;
      }
      int compare_res = cell.compare(cell_);
      assert(rc == RC::SUCCESS);
      if (compare_res < 0) {
        cell_ = cell;
      }
    } break;
    case AVGS: {
      TupleCell cell;
      RC rc = t->find_cell(field_, cell);
      assert(rc == RC::SUCCESS);
      if (cell.attr_type() != NULLS) {
        count_++;
        sum_ += cell.cast_to_number();
        cell_ = cell;
      }
    } break;
    case SUMS: {
      TupleCell cell;
      RC rc = t->find_cell(field_, cell);
      assert(rc == RC::SUCCESS);
      if (cell.attr_type() != NULLS) {
        sum_ += cell.cast_to_number();
        cell_ = cell;
      }
    } break;
    case COUNTS: {
      TupleCell cell;
      RC rc = t->find_cell(field_, cell);
      assert(rc == RC::SUCCESS);
      if (cell.attr_type() != NULLS) {
        count_++;
        cell_ = cell;
      }
    } break;
    default:
      LOG_ERROR("unknown aggregation type\n");
      break;
  }
}

TupleCell Aggregator::get_result()
{
  if (aggr_type_ == MAXS || aggr_type_ == MINS) {
    return cell_;
  } else if (aggr_type_ == COUNTS) {
    return TupleCell(INTS, (char *)&count_, sizeof(int));
  } else if (cell_.attr_type() == NULLS) {
    return cell_;
  } else if (aggr_type_ == SUMS) {
    return TupleCell(FLOATS, (char *)&sum_, sizeof(float));
  } else if (aggr_type_ == AVGS) {
    avg_ = sum_ / count_;
    return TupleCell(FLOATS, (char *)&avg_, sizeof(float));
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
      collect_aggr_exprs(static_cast<CompoundExpr *>(expr), aggr_exprs);
    }
  }
  if (having_ != nullptr) {
    if (having_->left()->type() == ExprType::AGGREGATE) {
      aggr_exprs.push_back(static_cast<AggregateExpr *>(having_->left()));
    }
    if (having_->right()->type() == ExprType::AGGREGATE) {
      aggr_exprs.push_back(static_cast<AggregateExpr *>(having_->right()));
    }
  }

  if (is_group_by_) {
    while ((rc = child->next()) == RC::SUCCESS) {
      Tuple *t = child->current_tuple();
      std::vector<TupleCell> group_cells;
      for (Expression *group_by : group_bys_) {
        TupleCell group_cell;
        group_by->get_value(*t, group_cell);
        group_cells.push_back(group_cell);
      }
      if (!group_by_tbls_.count(group_cells)) {
        AggregationTable agt;
        for (AggregateExpr *expr : aggr_exprs) {
          agt.add_expr(expr);
        }
        group_by_tbls_.insert({group_cells, agt});
      }
      group_by_tbls_[group_cells].add_tuple(t);
    }

    for (auto it = group_by_tbls_.begin(); it != group_by_tbls_.end(); it++) {
      auto &cells = it->first;
      auto &agt = it->second;
      for (AggregateExpr *expr : aggr_exprs) {
        expr->set_cell(agt.get_result(expr));
      }
      RowTuple unused;
      if (having_ != nullptr && PredicateOperator::do_filter_unit(unused, having_) == false) {
        continue;
      }
      std::vector<std::string> v;
      v.reserve(exprs_.size());
      for (Expression *expr : exprs_) {
        TupleCell cell;
        if (expr->type() == ExprType::FIELD) {
          size_t idx = 0;
          for (; idx < group_bys_.size(); idx++) {
            FieldExpr *cur_expr = static_cast<FieldExpr *>(expr);
            FieldExpr *group_expr = static_cast<FieldExpr *>(group_bys_[idx]);
            if (strcmp(cur_expr->field_name(), group_expr->field_name()) == 0) {
              break;
            }
          }
          cell = cells[idx];
        } else {
          RowTuple unused;
          expr->get_value(unused, cell);
        }
        std::stringstream ss;
        cell.to_string(ss);
        v.push_back(ss.str());
      }
      results_.push_back(v);
    }

  } else {
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
    
    RowTuple unused;
    if (having_ != nullptr && PredicateOperator::do_filter_unit(unused, having_)) {
      return RC::SUCCESS;
    }

    int i = 0;
    results_.push_back(std::vector<std::string>{});
    results_[0].reserve(exprs_.size());
    for (Expression *expr : exprs_) {
      assert(expr->type() != ExprType::FIELD);
      RowTuple unused;
      TupleCell cell;
      expr->get_value(unused, cell);
      std::stringstream ss;
      cell.to_string(ss);
      results_[0].push_back(ss.str());
      if (i == 0) {
        cell_ = cell;
      }
      i++;
    }
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
