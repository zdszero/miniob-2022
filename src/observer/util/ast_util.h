#pragma once

#include "sql/parser/parse_defs.h"
#include <string>

bool evaluate(ast* &t);
std::string ast_to_string(ast *t);
