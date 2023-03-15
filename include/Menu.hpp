#ifndef _MENU_H
#define _MENU_H

#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "../include/Item.hpp"
#include "../include/Query.hpp"
#include "../include/Regex.hpp"
#include "../include/User.hpp"

using namespace std;

class Menu {
public:
  User user, other;
  Query query;
  Item item;
  Regex re;
  string cur_time;

  void enterInitMenu(void);      // 1st
  bool enterMainMenu(void);      // 2nd
  bool enterAdminMainMenu(void); // 2nd for admin

  bool enterSellItemMenu(void);
  bool enterSearchMenu(void);
  void sellItem(void);
  void searchItem(void);

  void init(string host, string user, string passwd, string db,
            unsigned int port);

  void clear(void);

private:
};

#endif
