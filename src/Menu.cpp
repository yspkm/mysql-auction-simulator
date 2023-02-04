#include "../include/Menu.hpp"

void Menu::init(string host, string mysql_user, string passwd, string db, unsigned int port)
{
    user.init();
    other.init();
    query.init(host, mysql_user, passwd, db, port);
    item.init();
    re.init();
}

void Menu::enterInitMenu(void)
{
LOGIN:
    user.init();
    user.doLogin();
    if (!re.isRightEmail(user.email))
    {
        cout << "wrong email form" << endl;
        goto LOGIN;
    }
    if (user.is_signup)
    {
        cout << "signup done" << endl;
        query.signupQuery(&user);
        goto LOGIN;
    }
    if (query.loginQuery(&user))
        cout << "login succeeded" << endl;
    else
    {
        cout << "login failed" << endl;
        goto LOGIN;
    }
}

bool Menu::enterMainMenu(void)
{
    char choice;
    int itemid;
    string bid_str;
    // 5. The 2nd level menus for normal user or administrator
LOOP:
    cout << "----< Main menu > : (Enter the number)" << endl;
    cout << "----(1) Sell item" << endl;
    cout << "----(2) Status of Your Item Listed on Auction" << endl; // Seller’s menu
    cout << "----(3) Search item" << endl;
    cout << "----(4) Check Status of your Bid // Buyer’s menu" << endl;
    cout << "----(5) Check your Account" << endl;
    cout << "----(Q) Quit" << endl;
    cin >> choice;

    switch (choice)
    {
    case MAIN_MENU_CHOICE_SELL_ITEM:
        if (enterSellItemMenu())
            cout << "success!" << endl;
        break;
    case MAIN_MENU_CHOICE_STATUS_OF_YOUR_ITEM_LISTED_ON_AUCTION:
        query.showMyItemRows(&user);
        break;
    case MAIN_MENU_CHOICE_SEARCH_ITEM:
        if (!enterSearchMenu())
            return false;
    RETYPE:
        cout << "--- Which item do you want to bid? (Enter the number or ’B’ to go back to the previous menu): ";
        cin >> bid_str;
        if (bid_str == "B")
            break;
        else if (!re.isRightNumeric(bid_str))
        {
            cout << "wrong input" << endl;
            goto RETYPE;
        }
        itemid = atoi(bid_str.c_str());
        while (true)
        {
            cout << "--- Bidding price? (Enter the price or ’buy’ to pay for the buy-it-now price) :";
            bid_str.clear();
            cin >> bid_str;
            if (bid_str == "buy")
                goto BUY;
            if (re.isRightNumeric(bid_str))
            {
                if (re.isRightNumeric(bid_str))
                    goto BID;
                cout << "wrong input" << endl;
            }
        }
    BUY:
        if (query.buyItem(user, itemid, re))
            cout << "success" << endl;
        else
            cout << "failed" << endl;
        break;
    BID:
        if (query.bidItem(user, itemid, atoi(bid_str.c_str()), re))
            cout << "success" << endl;
        else
            cout << "failed" << endl;
        break;
    case MAIN_MENU_CHOICE_CHECK_STATUS_OF_YOUR_BID:
        query.checkStatusOfYourBid(&user);
        break;
    case MAIN_MENU_CHOICE_CHECK_YOUR_ACCOUNT:
        query.checkYourAccount(&user);
        break;
    case MAIN_MENU_QUIT:
        cout << "logout" << endl;
        return false;
        break;
    default:
        cout << "wrong input" << endl;
        goto LOOP;
    }
    return true;
}

bool Menu::enterSellItemMenu(void)
{
    item.init();
    item.getSellItemCategory();
    item.getSellItemCondition();
    item.getSellItemDescription();
    item.getSellItemBuyItNowPrice();
    item.getSellItemBidEndingDate();

    cur_time.clear();
    cur_time = re.getCurTimeString();
    if (re.getUnixTime(item.bid_ending_date) <= re.getUnixTime(cur_time))
    {
        cout << "bid ending date before local time !" << endl;
        return false;
    }
    query.sellItemQuery(&user, &item, &cur_time, re.getUnixTime(item.bid_ending_date));
    return true;
}

void Menu::clear(void)
{
    query.clear();
}

bool Menu::enterSearchMenu(void)
{
    bool ret;
    int input;
LOOP:
    cout << "----< Search item >" << endl;
    cout << "----(1) Search items by category" << endl;
    cout << "----(2) Search items by description keyword" << endl;
    cout << "----(3) Search items by seller" << endl;
    cout << "----(4) Search items by date posted" << endl;
    cout << "----(5) Go Back" << endl;
    cout << "----(6) Quit" << endl;
    cout << "(Enter the number): ";
    cin >> input;
    ret = true;
    switch (input)
    {
    case SEARCH_ITEM_BY_CATEGORY:
        item.category.clear();
        item.getSearchItemCategory();
        cout << item.category << endl;
        query.showItemRowsByCategory(item.category);
        break;
    case SEARCH_ITEM_BY_DESCRIPTION_KEYWORD:
        item.getSearchItemDescriptionKeyword();
        query.showItemRowsByDescriptionKeyword(item.description);
        break;
    case SEARCH_ITEM_BY_SELLER:
        other.getSearchSeller();
        query.showItemRowsBySeller(other.email);
        break;
    case SEARCH_ITEM_BY_DATE_POSTED:
        item.getSearchItemDatePosted();
        query.showItemRowsByDatePosted(item.date_posted_for_search);
        break;
    case SEARCH_ITEM_GO_BACK:
        break;
    case SEARCH_ITEM_QUIT:
        ret = false;
        break;
    default:
        cout << "wrong input(1~6)" << endl;
        goto LOOP;
    }
    return ret;
}

bool Menu::enterAdminMainMenu(void)
{
    char choice;
    string bid_str;
    struct tm *t;
    time_t unixtime = time(NULL);
    t = localtime(&unixtime);
    int year = t->tm_year + 1900;
    int mon = t->tm_mon + 1;
LOOP:
    choice = '\0';
    cout << "----< Admin Main menu > : (Enter the number)" << endl;
    cout << "----(0) Reset Balance Monthly" << endl;
    cout << "----(1) Number of Users" << endl;
    cout << "----(2) Number of Items" << endl;
    cout << "----(3) Number of Trades" << endl;
    cout << "----(4) Average Trades per Item(#Trades/#Items)" << endl;
    cout << "----(5) Sum of Commissions" << endl;
    cout << "----(Q) Quit" << endl;
    cin >> choice;
    switch (choice)
    {
    case ADMIN_MAIN_MENU_RESET_BALANCE_MONTHLY:
        cout << "Reset Balance This Month: " << year << "-" << mon << "-"
             << "1,"
             << "00:00" << endl;
        query.setAdminBalanceMonthlyReset(re);
        break;
    case ADMIN_MAIN_MENU_NUMBER_OF_USERS:
        cout << "Number of Users: " << query.getAdminCntUsers() << endl;
        break;
    case ADMIN_MAIN_MENU_NUMBER_OF_ITEMS:
        cout << "Number of Items: " << query.getAdminCntItems() << endl;
        break;
    case ADMIN_MAIN_MENU_NUMBER_OF_TRADES:
        cout << "Number of Trades: " << query.getAminCntBids() << endl;
        break;
    case ADMIN_MAIN_MENU_AVERAGE_TRADES_PER_ITEMS:
        cout << "Average Trades per Item: " << query.getAdminAvgBidsPerItem() << endl;
        break;
    case ADMIN_MAIN_MENU_SUM_OF_COMMISSIONS:
        cout << ">> Sum of Commissions: " << query.getAdminSumCommissions() << endl;
        break;
    case ADMIN_MAIN_MENU_QUIT:
        cout << "logout" << endl;
        return false;
        break;
    default:
        cout << "wrong input" << endl;
        goto LOOP;
    }
    return true;
}
