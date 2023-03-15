#ifndef _USER_H
#define _USER_H

#include <cstring>
#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class User {
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
