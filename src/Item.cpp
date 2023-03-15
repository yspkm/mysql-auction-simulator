#include "../include/Item.hpp"
#include <stdlib.h>

using namespace std;

void Item::clear(void) {
  bid_ending_date = "";
  buyitnow_price = "";
  category = "";
  condition = "";
  description = "";
}

void Item::init(void) {
  clear();
  re.init();
  categories[SELL_CATEGORY_BOOKS] = "Books";
  categories[SELL_CATEGORY_CLOTHING] = "Clothing";
  categories[SELL_CATEGORY_ELECTROICS] = "Electronics";
  categories[SELL_CATEGORY_HOME] = "Home";
  categories[SELL_CATEGORY_SPORTING_GOODS] = "Sporting Goods";
  conditions[SELL_CONDITION_NEW] = "New";
  conditions[SELL_CONDITION_LIKE_NEW] = "Like-New";
  conditions[SELL_CONDITION_USED_GOOD] = "Used (Good)";
  conditions[SELL_CONDITION_USED_ACCEPTABLE] = "Used (Acceptable)";
}

void Item::getSellItemCategory(void) {
  int input;
  while (true) {
    fflush(stdin);
    cout << "----< Sell item >" << endl;
    cout << "---- select from the following category : (Enter the number)"
         << endl;
    cout << "(1) Electronics" << endl;
    cout << "(2) Books" << endl;
    cout << "(3) Home" << endl;
    cout << "(4) Clothing" << endl;
    cout << "(5) Sporting Goods" << endl;
    cin >> input;
    if (1 <= input && input <= 5)
      break;
    cout << "wrong input" << endl;
  }
  category.clear();
  category = categories[input];
}
void Item::getSearchItemCategory(void) {
  int input;
  while (true) {
    fflush(stdin);
    cout << "----< Search item >" << endl;
    cout << "---- select from the following category : (Enter the number)"
         << endl;
    cout << "(1) Electronics" << endl;
    cout << "(2) Books" << endl;
    cout << "(3) Home" << endl;
    cout << "(4) Clothing" << endl;
    cout << "(5) Sporting Goods" << endl;
    cin >> input;
    if (1 <= input && input <= 5)
      break;
    cout << "wrong input" << endl;
  }
  category = "";
  category = categories[input];
}

void Item::getSellItemCondition(void) {
  int input;
  while (true) {
    fflush(stdin);
    cout << "---- condition: (Enter the number)" << endl;
    cout << "(1) New" << endl;
    cout << "(2) Like-New" << endl;
    cout << "(3) Used (Good)" << endl;
    cout << "(4) Used (Acceptable)" << endl;
    cin >> input;
    if (1 <= input && input <= 4)
      break;
    cout << "wrong input" << endl;
  }
  condition.clear();
  condition = conditions[input];
}

void Item::getSearchItemCondition(void) {
  int input;
  while (true) {
    fflush(stdin);
    cout << "---- condition: (Enter the number)" << endl;
    cout << "(1) New" << endl;
    cout << "(2) Like-New" << endl;
    cout << "(3) Used (Good)" << endl;
    cout << "(4) Used (Acceptable)" << endl;
    cin >> input;
    if (1 <= input && input <= 4)
      break;
    cout << "wrong input" << endl;
  }
  condition.clear();
  condition = conditions[input];
}

void Item::getSellItemDescription(void) {
  char buf[512] = {0};
  description.clear();
  // one line description
  getchar();
  cout << "---- description: ";
  scanf("%[^\n]s", buf);
  getchar();
  description = buf;
  // fflush(stdin);
}

void Item::getSearchItemDescriptionKeyword(void) {
  char buf[512] = {0};
  description.clear();
  // one line description
  getchar();
  cout << "---- description keyword: ";
  scanf("%[^\n]s", buf);
  getchar();
  description = buf;
  // fflush(stdin);
}

void Item::getSellItemBuyItNowPrice(void) {
  while (true) {
    fflush(stdin);
    buyitnow_price.clear();
    cout << "---- buy-it-now price: "; // if user’s input is not numeric, repeat
                                       // this prompt.
    cin >> buyitnow_price;
    if (re.isRightNumeric(buyitnow_price))
      if (atoi(buyitnow_price.c_str()) > 0)
        break;
    cout << "wrong input" << endl;
  }
}

void Item::getSellItemBidEndingDate(void) {
  while (true) {
    fflush(stdin);
    bid_ending_date.clear();
    cout << "---- bid ending date: ";
    cin >> bid_ending_date;
    if (re.isRightDate(bid_ending_date))
      break;
    cout << "wrong input" << endl;
    cout << "e.g. 2022-12-31,23:59" << endl;
  }
}

void Item::getSearchItemDatePosted(void) {
  while (true) {
    fflush(stdin);
    date_posted_for_search.clear();
    cout << "---- date posted: ";
    cin >> date_posted_for_search;
    if (re.isRightDate(date_posted_for_search))
      break;
    cout << "wrong input" << endl;
    cout << "e.g. 2022-12-31,23:59" << endl;
  }
}

void Item::printItem(void) {
  cout << "category: " << category << endl;
  cout << "condition: " << condition << endl;
  cout << "description: " << description << endl;
  cout << "buy-it-now price: " << buyitnow_price << endl;
  cout << "bid_ending_date: " << bid_ending_date << endl;
}
