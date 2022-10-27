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
// Created by Meiyi & Wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"

const static Json::StaticString INDEX_NAME("index_name");
const static Json::StaticString FIELD_NAME("field_name");
const static Json::StaticString INDEX_FIELD_NAMES("index_field_names");

RC IndexMeta::init(const char *name, const std::vector<const FieldMeta *> &field)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  field_.reserve(field.size());
  for (size_t i = 0; i < field.size(); i++) {
    field_.push_back(field[i]->name());
  }
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[INDEX_NAME] = name_;
  Json::Value fields_value;
  for (const std::string &field : field_) {
    Json::Value field_value;
    field_value[FIELD_NAME] = field;
    fields_value.append(std::move(field_value));
  }
  json_value[INDEX_FIELD_NAMES] = std::move(fields_value);
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[INDEX_NAME];
  const Json::Value &fields_value = json_value[INDEX_FIELD_NAMES];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!fields_value.isArray()) {
    LOG_ERROR("Field names of index [%s] is not an array. json value=%s",
        name_value.asCString(),
        fields_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }
  int field_num = fields_value.size();
  std::vector<const FieldMeta *> fields(field_num);
  for (int i = 0; i < field_num; i++) {
    const Json::Value &field_value = fields_value[i];
    if (!field_value[FIELD_NAME].isString()) {
      LOG_ERROR("field name is not a string. json value=%s", field_value.toStyledString().c_str());
      return RC::GENERIC_ERROR;
    }
    const char *field_name = field_value[FIELD_NAME].asCString();
    const FieldMeta *field = table.field(field_name);
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields[i] = field;
  }

  return index.init(name_value.asCString(), fields);
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

const char *IndexMeta::field() const
{
  return field_[0].c_str();
}

const std::vector<std::string> &IndexMeta::fields() const
{
  return field_;
}

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ << ", field=" << field_[0];
}
