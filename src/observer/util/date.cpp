#include "rc.h"
#include <cstdint>
#include <cstdio>
#include <string>
#include <sstream>

static std::string month_string[12] = {"January", "February", "March", "April",
  "May", "June", "July", "August", "September", "October", "November",
  "December"};

static std::string day_post[10] = {"st", "nd", "rd", "th", "th", "th", "th", "th", "th", "th"};

bool is_leap_year(int year)
{
  if (year % 100 == 0) {
    return (year % 400 == 0);
  }
  return year % 4 == 0;
}

RC string_to_date(const char *str, int32_t &date)
{
  int year, month, day;
  int ret = sscanf(str, "%d-%d-%d", &year, &month, &day);
  if (ret != 3) {
    return RC::INVALID_ARGUMENT;
  }

  // validate
  if (year < 1900 || year > 9999 || (month <= 0 || month > 12) || (day < 0 || day > 31)) {
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

std::string date_to_string(int32_t date)
{
  char buf[30];
  int year, month, day;
  year = date / 10000;
  date %= 10000;
  month = date / 100;
  day = date % 100;
  sprintf(buf, "%4d-%02d-%02d", year, month, day);
  return {buf};
}

std::string format_date(int32_t date, const std::string &format)
{
  int year, month, day;
  year = date / 10000;
  date %= 10000;
  month = date / 100;
  day = date % 100;
  std::stringstream ss;
  for (size_t i = 0; i < format.size();) {
    if (format[i] == '%') {
      if (i + 2 > format.size()) {
        i++;
        continue;
      }
      std::string sub = format.substr(i, 2);
      if (sub == "%Y") {
        ss << year;
      } else if (sub == "%y") {
        ss << year % 100;
      } else if (sub == "%M") {
        ss << month_string[month-1];
      } else if (sub == "%m") {
        if (month < 10) {
          ss << "0";
        }
        ss << month;
      } else if (sub == "%D") {
        ss << day << day_post[day % 10 - 1];
      } else if (sub == "%d") {
        if (day < 10) {
          ss << "0";
        }
        ss << day;
      } else {
        i++;
        continue;
      }
      i += 2;
    } else {
      ss << format[i];
      i++;
    }
  }
  return ss.str();
}
