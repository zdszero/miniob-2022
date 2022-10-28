#pragma once

#include "sql/operator/operator.h"

class UpdateStmt;
class Trx;

class UpdateOperator : public Operator {
public:
  UpdateOperator(UpdateStmt *update_stmt, Trx *trx) : update_stmt_(update_stmt), trx_(trx)
  {}
  ~UpdateOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override
  {
    return nullptr;
  }
  OperatorType type() override
  {
    return OperatorType::UPDATE;
  }

private:
  UpdateStmt *update_stmt_ = nullptr;
  Trx *trx_ = nullptr;

  RC update_data(char *data, const FieldMeta *meta, Value &val);
};
