#pragma once

#include "../include/Regex.hpp"
#include "../include/param.hpp"
#include <iostream>
#include <string>

using namespace std;
typedef unsigned won_t;

class Item {
public:
  string category;
  string condition;
  string description;
  string buyitnow_price;
  string bid_ending_date; // YYYY.MM.DD HH:MM
  string date_posted_for_search;

  string categories[5 + 1];
  string conditions[4 + 1];
  Regex re;

  void init(void);
  void clear(void);
  void getSellItemCondition(void);
  void getSellItemCategory(void);
  void getSellItemDescription(void);
  void getSellItemBuyItNowPrice(void);
  void getSellItemBidEndingDate(void);

  void getSearchItemCondition(void);
  void getSearchItemCategory(void);
  void getSearchItemDescriptionKeyword(void);
  void getSearchItemDatePosted(void);

  void printItem(void);

private:
};
