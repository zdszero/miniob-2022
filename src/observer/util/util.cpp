/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai on 2022/9/28
//

#include <string.h>
#include "util/util.h"

std::string double2string(double v)
{
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", v);
  size_t len = strlen(buf);
  while (buf[len - 1] == '0') {
    len--;
      
  }
  if (buf[len - 1] == '.') {
    len--;
  }

  return std::string(buf, len);
}

bool is_numeric_type(AttrType type)
{
  return type == INTS || type == FLOATS;
}

bool is_number(const std::string &s, AttrType &to_type)
{
  if (s.empty())
    return false;
  int dots_count = 0;
  for (char c : s) {
    if (c == '.') {
      dots_count++;
      continue;
    }
    if (c >= '0' && c <= '9') {
      continue;
    }
    return false;
  }
  if (dots_count == 0) {
    to_type = INTS;
    return true;
  }
  if (dots_count > 1) {
    return false;
  }
  // dots_count == 1
  to_type = FLOATS;
  return true;
}
