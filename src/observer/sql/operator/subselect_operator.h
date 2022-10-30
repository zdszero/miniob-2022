#pragma once

#include "sql/operator/operator.h"
#include "sql/stmt/select_stmt.h"
#include <vector>

// not a generic operator
class SubSelectOperator {
public:
  SubSelectOperator(SelectStmt *select_stmt, Trx *trx);
  ~SubSelectOperator();

  RC HasResult(bool &ret) const;
  RC GetOneResult(TupleCell &cell) const;
  RC GetResultList(std::vector<TupleCell> &cells) const;

private:
  SelectStmt *select_stmt_{nullptr};
  Operator *oper_{nullptr};
};
