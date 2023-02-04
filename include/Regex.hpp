#pragma once

#include <regex>
#include <string.h>
#include <stdbool.h>
#include <time.h>

using namespace std;

class Regex
{
public:
    regex conn_re;
    regex date_re;
    regex email_re;
    regex numeric_re;
    regex name_re;
    smatch match;

    void init(void);
    bool isRightConn(string conn);
    bool isRightDate(string date);
    bool isRightEmail(string email);
    bool isRightNumeric(string number);
    bool isRightName(string name);
    bool getConn(string conn);

    time_t getUnixTime(string date);
    string getCurTimeString();

private:
};