#pragma once

#include "rc.h"
#include <ctime>
#include <cstdint>
#include <cstdio>
#include <string>

inline bool is_leap_year(int year) {
  if (year % 100 == 0) {
    return (year % 400 == 0);
  }
  return year % 4 == 0;
}

inline RC string_to_date(const char *str, int32_t &date) {
  int year, month, day;
  int ret = sscanf(str, "%d-%d-%d", &year, &month, &day);
  if (ret != 3) {
    return RC::INVALID_ARGUMENT;
  }

  // validate
  if (year < 1900 || year > 9999 ||
      (month <= 0 || month > 12) ||
      (day < 0 || day > 31)) {
    return RC::INVALID_ARGUMENT;
  }
  
  int max_day_in_month[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  const int max_day = max_day_in_month[month - 1];
  if (day > max_day) {
    return RC::INVALID_ARGUMENT;
  }
  if (month == 2 && !is_leap_year(year) && day > 28) {
    return RC::INVALID_ARGUMENT;
  }

  date = year * 10000 + month * 100 + day;
  return RC::SUCCESS;
}

inline std::string date_to_string(int32_t date) {
  char buf[30];
  int year, month, day;
  year = date / 10000;
  date %= 10000;
  month = date / 100;
  day = date % 100;
  sprintf(buf, "%4d-%02d-%02d", year, month, day);
  return {buf};
}

inline void init_tm(int32_t date, tm *times) {
  int year, month, day;
  year = date / 10000;
  date %= 10000;
  month = date / 100;
  day = date % 100;
  times->tm_year = year;
  times->tm_mon = month;
  times->tm_mday = day;
}
