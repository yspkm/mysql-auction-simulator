#ifndef _USER_H
#define _USER_H

#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class User
{
public:
    string email; // email
    string passwd;
    string first_name;
    string last_name;

    bool is_admin;
    bool is_signup;

    // Methods
    void init(void);
    void doLogin(void);
    void getLoginInfo(void);
    void getSignUpInfo(void);
    void printUserInfo(void); // for test
    void getSearchSeller(void);

private:
};

#endif