#pragma once

#include "sql/operator/operator.h"

class NoTableOperator : public Operator {
public:
  NoTableOperator() = default;

  RC open() override
  {
    is_first_ = true;
    return RC::SUCCESS;
  }
  RC next() override
  {
    if (is_first_) {
      is_first_ = false;
      return RC::SUCCESS;
    }
    return RC::RECORD_EOF;
  }
  RC close() override
  {
    return RC::SUCCESS;
  }
  Tuple *current_tuple() override
  {
    return &unused_tuple_;
  }
  OperatorType type() override
  {
    return OperatorType::NOTABLE;
  }

private:
  bool is_first_{true};
  RowTuple unused_tuple_;
};
