#pragma once

#include "rc.h"
#include <string>

bool is_leap_year(int year);
RC string_to_date(const char *str, int32_t &date);
std::string date_to_string(int32_t date);
std::string format_date(int32_t date, const std::string &format);
