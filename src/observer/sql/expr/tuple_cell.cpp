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
// Created by WangYunlai on 2022/07/05.
//

#include "sql/expr/tuple_cell.h"
#include "storage/common/field.h"
#include "common/log/log.h"
#include "util/comparator.h"
#include "util/date.h"
#include "util/util.h"
#include <cassert>
#include <cstdlib>

void TupleCell::to_string(std::ostream &os) const
{
  switch (attr_type_) {
  case INTS: {
    os << *(int *)data_;
  } break;
  case FLOATS: {
    float v = *(float *)data_;
    os << double2string(v);
  } break;
  case DATES: {
    int32_t date = *(int32_t *)data_;
    os << date_to_string(date);
  } break;
  case CHARS: {
    for (int i = 0; i < length_; i++) {
      if (data_[i] == '\0') {
        break;
      }
      os << data_[i];
    }
  } break;
  default: {
    LOG_WARN("unsupported attr type: %d", attr_type_);
  } break;
  }
}

int TupleCell::compare(const TupleCell &other) const
{
  assert(this->attr_type_ != UNDEFINED && other.attr_type_ != UNDEFINED);
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS: return compare_int(this->data_, other.data_);
      case FLOATS: return compare_float(this->data_, other.data_);
      case CHARS: return compare_string(this->data_, this->length_, other.data_, other.length_);
      case DATES:return compare_int(this->data_, other.data_);
      default:
        LOG_ERROR("unsupported type: %d", this->attr_type_);
        return RC::INTERNAL;
    }
  }
  switch (this->attr_type_) {
    case INTS:
      {
        float myfv = static_cast<float>(*(int *)this->data_);
        float otherfv;
        if (other.attr_type_ == FLOATS) {
          otherfv = *(float *)other.data_;
        } else {
          assert(other.attr_type_ == CHARS);
          otherfv = std::atof(other.data_);
        }
        return compare_float(&myfv, &otherfv);
      }
    case FLOATS:
      {
        float myfv = *(float *)this->data_;
        float otherfv;
        if (other.attr_type_ == INTS) {
          otherfv = static_cast<float>(*(int *)other.data_);
        } else {
          assert(other.attr_type_ == CHARS);
          otherfv = std::atof(other.data_);
        }
        return compare_float(&myfv, &otherfv);
      }
    case CHARS:
      {
        float myfv = std::atof(this->data_);
        float otherfv;
        if (other.attr_type_ == INTS) {
          otherfv = static_cast<float>(*(int *)other.data_);
          return compare_float(&myfv, &otherfv);
        } else if (other.attr_type_ == FLOATS) {
          return compare_float(&myfv, other.data_);
        } else {
          int32_t date;
          RC rc = string_to_date(this->data_, date);
          assert(rc == RC::SUCCESS);
          return compare_int(&date, other.data_);
        }
      }
    case DATES:
      {
        if (other.attr_type_ == CHARS) {
          int32_t date;
          RC rc = string_to_date(other.data_, date);
          assert(rc == RC::SUCCESS);
          return compare_int(this->data_, &date);
        } else if (other.attr_type_ == FLOATS) {
          int v = static_cast<int>(*(float *)other.data_);
          return compare_int(this->data_, &v);
        }
        assert(other.attr_type_ == INTS);
        return compare_int(this->data_, other.data_);
      }
    default:
      LOG_ERROR("unsupported type: %d", this->attr_type_);
      return RC::INTERNAL;
  }
}


bool TupleCell::wildcard_compare(const TupleCell &other, bool is_not) const {
  if (attr_type_ != AttrType::CHARS || other.attr_type_ != AttrType::CHARS) {
    LOG_ERROR("type is not char in wildcard compare\n");
    return false;
  }
  bool ret = wildcard_match(this->data_, other.data_);
  if (is_not) {
    return !ret;
  }
  return ret;
}
