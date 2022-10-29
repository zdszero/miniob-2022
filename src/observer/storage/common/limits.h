#pragma once

#include "sql/parser/parse_defs.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <limits>

static constexpr int MINIOB_INT_NULL = std::numeric_limits<int>::lowest();
static constexpr int32_t MINIOB_DATE_NULL = 0;
static constexpr float MINIOB_FLOAT_NULL = std::numeric_limits<float>::lowest();
static constexpr char MINIOB_CHARS_NULL = std::numeric_limits<char>::lowest();

void set_mem_null(void *dst, AttrType attr_type, size_t attr_len);
bool is_mem_null(void *dst, AttrType attr_type, size_t attr_len);
