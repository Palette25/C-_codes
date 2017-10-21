#include "date.hpp"

Date::Date() {
  setDate(2017, 1, 28);
}

Date::Date(int _year, int _month, int _day) {
  setDate(_year, _month, _day);
}

bool Date::equals(const Date& that) const {
  return year == that.getYear() &&
     month == that.getMonth() &&
     day == that.getDay();
}

bool Date::smallerThan(const Date& that) const {
  if (year == that.getYear()) {
    if (month == that.getMonth()) {
      return day < that.getDay();
    }
    return month < that.getMonth();
  }
  return year < that.getYear();
}

void Date::normalize() {
  while (month > 12) {
    year++;
    month -= 12;
  }
  while (day > daysOfMonth(year, month)) {
    day -= daysOfMonth(year, month);
    month++;
    if (month > 12) {
      year++;
      month -= 12;
    }
  }
}