#ifndef _MENU_H
#define _MENU_H

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <ctype.h>

#include "../include/User.hpp"
#include "../include/Query.hpp"
#include "../include/Item.hpp"
#include "../include/Regex.hpp"

using namespace std;

class Menu
{
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

    void init(string host, string user, string passwd, string db, unsigned int port);

    void clear(void);

private:
};

#endif