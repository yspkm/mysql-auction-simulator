#include "../include/Regex.hpp"
#include "assert.h"

void Regex::init(void) {
  conn_re.assign("[j|o]{1}dbc:mysql://(\\w*):(\\d*)/(\\w*)");
  // e.g. 2022-12-31,23:59 --> 2023-01-01,00:00
  date_re.assign("^(\\d{4})\\-(0?[1-9]|1[012])\\-(0?[1-9]|[12][0-9]|3[01])\\,(["
                 "0-1]?[0-9]|2[0-3])\\:([0-5][0-9])$");
  email_re.assign("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
  numeric_re.assign("^([0-9]+)");
  name_re.assign("^([a-zA-Z]+)");
}

bool Regex::isRightNumeric(string number) {
  return regex_match(number, numeric_re);
}

bool Regex::isRightConn(string conn) { return regex_match(conn, conn_re); }

bool Regex::isRightEmail(string email) { return regex_match(email, email_re); }

bool Regex::isRightDate(string date) { return regex_match(date, date_re); }
bool Regex::getConn(string conn) {
  bool ret;
  ret = isRightConn(conn);
  if (ret == true)
    assert(regex_match(conn, match, conn_re) != 0);
  return ret;
}

#include <iostream>
time_t Regex::getUnixTime(string date) {
  time_t ret = 0;
  string year, month, day, hour, min;
  struct tm ts;
  if (isRightDate(date)) {
    sscanf(date.c_str(), "%d-%d-%d,%d:%d", &ts.tm_year, &ts.tm_mon, &ts.tm_mday,
           &ts.tm_hour, &ts.tm_min);
    ts.tm_year -= 1900;
    ts.tm_mon -= 1;
    ts.tm_sec = 0;
    ts.tm_isdst = -1;
    ret = mktime(&ts);
  }
  return ret;
}

string Regex::getCurTimeString(void) {
  string ret;
  char buf[128] = {0};
  memset(buf, 0x0, sizeof(buf) / sizeof(buf[0]));
  time_t t = time(NULL);
  struct tm *ts = localtime(&t);
  sprintf(buf, "%d-%d-%d,%d:%d", ts->tm_year + 1900, ts->tm_mon + 1,
          ts->tm_mday, ts->tm_hour, ts->tm_min);
  ret.clear();
  ret.append(buf);
  return ret;
}
