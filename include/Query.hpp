#ifndef _QUERY_H
#define _QUERY_H

#include "../include/Item.hpp"
#include "../include/User.hpp"
#include "../include/dbms.hpp"
#include "param.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Query {
public:
  MYSQL conn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  int num_field;

  // without constructor
  void init(string host, string user, string passwd, string db,
            unsigned int port);
  void clear(void);
  void showResult(void);
  void signupQuery(User *uptr);
  bool loginQuery(User *uptr);
  bool sellItemQuery(User *uptr, Item *iptr, string *cur_time,
                     time_t unixtime_bidending);

  void showMyItemRows(User *uptr);
  void showItemRowsByCategory(string category);
  void showItemRowsBySeller(string sellerid);
  void showItemRowsByDatePosted(string date);
  void showItemRowsByDescriptionKeyword(string keyword);
  void checkStatusOfYourBid(User *uptr);
  void checkYourAccount(User *uptr);

  bool buyItem(User &user, int itemid, Regex &re);
  bool bidItem(User &user, int itemid, int bid_price, Regex &re);

  // for admin
  int getAdminCntUsers(void);
  int getAdminCntItems(void);
  int getAminCntBids(void);
  int getAdminSumCommissions(void);
  double getAdminAvgBidsPerItem(void);
  void setAdminBalanceMonthlyReset(Regex &re);

  // obsolete
private:
  void anyQuery(string query);
  void insertRow(string insert_into, string values);
  void selectRow(string select, string from, string where_groupby_having);
  void deleteRow(string delete_from, string where);
  void perror(string file_name, string func_name, int line_num);
};

#endif
