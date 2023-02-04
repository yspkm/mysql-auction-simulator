#include <string>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <assert.h>
#include "../include/Query.hpp"
#define BUFSIZE 512

#include <stdio.h>

void Query::clear(void)
{
    mysql_close(&conn);
}

void Query::perror(string file_name, string func_name, int line_num)
{
    std::cout << "error: !\n";
    std::cout << "\tfile: " << file_name << endl;
    std::cout << "\tfunc: " << func_name << endl;
    std::cout << "\tline: " << line_num << endl;
    std::cout << "\t" << mysql_error(&conn) << endl;
    // mysql_close(conn);
}

void Query::showResult(void)
{
    while ((row = mysql_fetch_row(res)))
    {
        for (int i = 0; i < num_field; i++)
            std::cout << (row[i] ? row[i] : "NULL") << " ";
        std::cout << endl;
    }
}

void Query::selectRow(string select, string from, string where_groupby_having)
{
    string query = select + " " + from + " " + where_groupby_having;
    anyQuery(query);
    showResult();
    mysql_free_result(res);
}

void Query::anyQuery(string query)
{
    if (mysql_query(&conn, (char *)query.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    num_field = mysql_num_fields(res);
    // showResult();
}

void Query::init(string host, string user, string passwd, string db, unsigned int port)
{
    mysql_init(&conn);
    res = NULL;
    if (!mysql_real_connect(&conn, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, NULL, 0))
        perror(__FILE__, __FUNCTION__, __LINE__);
}

void Query::insertRow(string insert_into, string values)
{
    string sql = insert_into + " " + values;
    anyQuery(sql);
}

void Query::deleteRow(string delete_from, string where)
{
    string sql = delete_from + " " + where;
    anyQuery(sql);
}

void Query::signupQuery(User *uptr)
{
    string sql = "";
    sql.append("insert ");
    sql.append("into ");
    sql.append("tUser(");
    sql.append("userid, first_name, last_name, passwd, isadmin) ");
    string admin = string(uptr->is_admin ? "admin" : "user");
    sql.append("values( \"" + uptr->email + "\", \"" + uptr->first_name + "\", \"" + uptr->last_name + "\", \"" + uptr->passwd + "\", \"" + admin.c_str());
    sql.append("\");");
    if (mysql_query(&conn, (char *)sql.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    sql.clear();
}

bool Query::loginQuery(User *uptr)
{
    res = NULL;
    bool ret = true;
    string sql = "";
    sql += "select passwd, isadmin from tUser where userid=\"" + uptr->email + "\";";
    if (mysql_query(&conn, (char *)sql.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    if (NULL == (res = mysql_store_result(&conn)))
    {
        perror(__FILE__, __FUNCTION__, __LINE__);
    }
    if (NULL == (row = mysql_fetch_row(res)))
    {
        cout << "no userid " << uptr->email << "\n";
        ret = false;
    }
    else
    {
        sql.clear();
        sql.append(row[0]);
        if (uptr->passwd != sql)
        {
            cout << "wrong passwd" << endl;
            ret = false;
        }
        else if (uptr->is_admin)
        {
            if (string(row[1]) != "admin")
            {
                cout << "you are not admin" << endl;
                ret = false;
            }
        }
    }
    if (res)
        mysql_free_result(res);
    sql.clear();
    return ret;
}

bool Query::sellItemQuery(User *uptr, Item *iptr, string *cur_time, time_t unixtime_bidending)
{
    res = NULL;
    bool ret;
    ret = true;
    string sql = "";
    sql = "";

    sql.append("insert into tItem(");
    sql.append("userid, date_bidending, cond, category, date_posted, description, unixtime_bidending, buyitnow_price) ");
    sql.append("values( \"" + uptr->email + "\" ," + " \"" + iptr->bid_ending_date + "\"" + ", " + " \"" + iptr->condition + "\", \"" + iptr->category + "\", \"" + *cur_time + "\" ");
    sql.append(",\"" + iptr->description + "\"" + +", \"" + to_string(unixtime_bidending) + "\", \"" + iptr->buyitnow_price + "\");");

    if (mysql_query(&conn, (char *)sql.c_str()))
    {
        ret = false;
        perror(__FILE__, __FUNCTION__, __LINE__);
    }
    // for safety
    if (NULL != (res = mysql_store_result(&conn)))
    {
        mysql_free_result(res);
        cout << "free" << endl;
    }

    sql.clear();
    return ret;
}

#define ITEMID_FIELD 0
#define BIDENDINGDATE_FIELD 2
#define BUYITNOW_PRICE 4
#define CONDITION_FIELD 5
#define DESCRIBE_FIELD 8
#define POSTEDDATE_FIELD 7
#define CATEGORY_FIELD 6
#define STATUS_FIELD 9
#define MAXBIDDER_FIELD 10
#define PRICE_FIELD 11

void Query::showMyItemRows(User *uptr)
{
    char buf[512] = {0};
    sprintf(buf, "select * from tItem natural join itemStatus natural left outer join maxBidder where userid = \"%s\";", uptr->email.c_str());
    string sql = buf;
    res = NULL;
    if (mysql_query(&conn, (char *)sql.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        cout << "----< Status of Your Item Listed on Auction >" << endl;
        num_field = mysql_num_fields(res);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "Item [" << row[ITEMID_FIELD] << "]" << endl;
            cout << "  description: " << (row[DESCRIBE_FIELD] ? row[DESCRIBE_FIELD] : "") << endl;
            cout << "  status: " << (atoi(row[STATUS_FIELD]) == -2 ? "unsold" : (atoi(row[STATUS_FIELD]) == -1 ? "sold" : string(row[STATUS_FIELD]) + " bids")) << endl;
            cout << "  current bidding price: " << (row[PRICE_FIELD] ? row[PRICE_FIELD] : "0") << endl;
            cout << "  current highest bidder: " << (row[MAXBIDDER_FIELD] ? row[MAXBIDDER_FIELD] : "") << endl;
            cout << "  date posted: " << row[POSTEDDATE_FIELD] << endl;
            cout << "  bid ending date: " << row[BIDENDINGDATE_FIELD] << endl;
        }
        cout << endl;
        mysql_free_result(res);
    }
    sql.clear();
}

void Query::showItemRowsByCategory(string category)
{
    char buf[512] = {0};
    sprintf(buf, "select * from tItem natural join itemStatus natural left outer join maxBidder where category = \"%s\";", category.c_str());
    string sql = buf;
    res = NULL;
    if (mysql_query(&conn, (char *)sql.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        cout << "----< Search results: " << category << ">" << endl;
        num_field = mysql_num_fields(res);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "Item [" << row[ITEMID_FIELD] << "]" << endl;
            cout << "  description: " << (row[DESCRIBE_FIELD] ? row[DESCRIBE_FIELD] : "") << endl;
            cout << "  status: " << (atoi(row[STATUS_FIELD]) == -2 ? "unsold" : (atoi(row[STATUS_FIELD]) == -1 ? "sold" : string(row[STATUS_FIELD]) + " bids")) << endl;
            cout << "  current bidding price: " << (row[PRICE_FIELD] ? row[PRICE_FIELD] : "0") << endl;
            cout << "  current highest bidder: " << (row[MAXBIDDER_FIELD] ? row[MAXBIDDER_FIELD] : "") << endl;
            cout << "  date posted: " << row[POSTEDDATE_FIELD] << endl;
            cout << "  bid ending date: " << row[BIDENDINGDATE_FIELD] << endl;
        }
        cout << endl;
        mysql_free_result(res);
    }
    sql.clear();
}

void Query::showItemRowsBySeller(string sellerid)
{
    char buf[512] = {0};
    sprintf(buf, "select * from tItem natural join itemStatus natural left outer join maxBidder where userid = \"%s\";", sellerid.c_str());
    string sql = buf;
    res = NULL;
    if (mysql_query(&conn, (char *)sql.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        cout << "----< Search results: " << sellerid << ">" << endl;
        num_field = mysql_num_fields(res);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "Item [" << row[ITEMID_FIELD] << "]" << endl;
            cout << "  description: " << (row[DESCRIBE_FIELD] ? row[DESCRIBE_FIELD] : "") << endl;
            cout << "  status: " << (atoi(row[STATUS_FIELD]) == -2 ? "unsold" : (atoi(row[STATUS_FIELD]) == -1 ? "sold" : string(row[STATUS_FIELD]) + " bids")) << endl;
            cout << "  current bidding price: " << (row[PRICE_FIELD] ? row[PRICE_FIELD] : "0") << endl;
            cout << "  current highest bidder: " << (row[MAXBIDDER_FIELD] ? row[MAXBIDDER_FIELD] : "") << endl;
            cout << "  date posted: " << row[POSTEDDATE_FIELD] << endl;
            cout << "  bid ending date: " << row[BIDENDINGDATE_FIELD] << endl;
        }
        cout << endl;
        mysql_free_result(res);
    }
    sql.clear();
}

void Query::showItemRowsByDatePosted(string date)
{
    char buf[512] = {0};
    sprintf(buf, "select * from tItem natural join itemStatus natural left outer join maxBidder where date_posted like \"%%%s%%\";", date.c_str());
    string sql = buf;
    res = NULL;
    if (mysql_query(&conn, (char *)sql.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        cout << "----< Search results: " << date << ">" << endl;
        num_field = mysql_num_fields(res);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "Item [" << row[ITEMID_FIELD] << "]" << endl;
            cout << "  description: " << (row[DESCRIBE_FIELD] ? row[DESCRIBE_FIELD] : "") << endl;
            cout << "  status: " << (atoi(row[STATUS_FIELD]) == -2 ? "unsold" : (atoi(row[STATUS_FIELD]) == -1 ? "sold" : string(row[STATUS_FIELD]) + " bids")) << endl;
            cout << "  current bidding price: " << (row[PRICE_FIELD] ? row[PRICE_FIELD] : "0") << endl;
            cout << "  current highest bidder: " << (row[MAXBIDDER_FIELD] ? row[MAXBIDDER_FIELD] : "") << endl;
            cout << "  date posted: " << row[POSTEDDATE_FIELD] << endl;
            cout << "  bid ending date: " << row[BIDENDINGDATE_FIELD] << endl;
        }
        cout << endl;
        mysql_free_result(res);
    }
    sql.clear();
}

void Query::showItemRowsByDescriptionKeyword(string keyword)
{
    char buf[512] = {0};
    sprintf(buf, "select * from tItem natural join itemStatus natural left outer join maxBidder where description like \"%%%s%%\";", keyword.c_str());
    string sql = buf;
    res = NULL;
    if (mysql_query(&conn, (char *)sql.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        cout << "----< Search results: " << keyword << ">" << endl;
        num_field = mysql_num_fields(res);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "Item [" << row[ITEMID_FIELD] << "]" << endl;
            cout << "  description: " << (row[DESCRIBE_FIELD] ? row[DESCRIBE_FIELD] : "") << endl;
            cout << "  status: " << (atoi(row[STATUS_FIELD]) == -2 ? "unsold" : (atoi(row[STATUS_FIELD]) == -1 ? "sold" : string(row[STATUS_FIELD]) + " bids")) << endl;
            cout << "  current bidding price: " << (row[PRICE_FIELD] ? row[PRICE_FIELD] : "0") << endl;
            cout << "  current highest bidder: " << (row[MAXBIDDER_FIELD] ? row[MAXBIDDER_FIELD] : "") << endl;
            cout << "  date posted: " << row[POSTEDDATE_FIELD] << endl;
            cout << "  bid ending date: " << row[BIDENDINGDATE_FIELD] << endl;
        }
        cout << endl;
        mysql_free_result(res);
    }
    sql.clear();
}

void Query::checkYourAccount(User *uptr)
{
    res = NULL;
    cout << "----< Check your Account >" << endl;
    string sql;
    char buf_plus[512] = {0};
    char buf_minus[512] = {0};
    char buf_balance[512] = {0};
    sprintf(buf_plus, "select itemid, description, price from soldItem where seller_userid = \"%s\";", uptr->email.c_str());
    sprintf(buf_minus, "select itemid, description, price from soldItem where buyer_userid = \"%s\";", uptr->email.c_str());
    sprintf(buf_balance, "select plus, comm, minus, balance from balanceSheet where userid = \"%s\";", uptr->email.c_str());

    sql.clear();
    sql = buf_plus;
    if (mysql_query(&conn, (char *)sql.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        num_field = mysql_num_fields(res);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "[Sold Item " << row[0] << "]" << endl;
            cout << "  description: " << (row[1] ? row[1] : "") << endl;
            cout << "  sold price: " << (row[2] ? row[2] : "0") << endl;
        }
        cout << endl;
        mysql_free_result(res);
    }
    sql.clear();
    sql = buf_minus;
    res = NULL;
    if (mysql_query(&conn, (char *)sql.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        num_field = mysql_num_fields(res);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "[Purchased Item " << row[0] << "]" << endl;
            cout << "  description: " << (row[1] ? row[1] : "") << endl;
            cout << "  purchased price: " << (row[2] ? row[2] : "0") << endl;
        }
        cout << endl;
        mysql_free_result(res);
    }
    sql.clear();
    sql = buf_balance;
    if (mysql_query(&conn, (char *)sql.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        num_field = mysql_num_fields(res);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "[Your Balance Summary]" << endl;
            cout << "  sold: " << (row[0] ? row[0] : "0") << " won" << endl;
            cout << "  commission: " << (row[1] ? row[1] : "0") << " won" << endl;
            cout << "  purchased: " << (row[2] ? row[2] : "0") << " won" << endl;
            cout << "  total balance: " << (row[3] ? row[3] : "0") << " won" << endl;
            cout << endl;
        }
        mysql_free_result(res);
    }
    sql.clear();
}

void Query::checkStatusOfYourBid(User *uptr)
{
    char buf[512] = {0};
    sprintf(buf, "select itemid, description, bid_status, bid_price, price, date_bidending from bidStatus where buyer = \"%s\";", uptr->email.c_str());
    string sql = buf;
    res = NULL;
    if (mysql_query(&conn, (char *)sql.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        cout << "----< Check Status of your Bid >" << endl;
        num_field = mysql_num_fields(res);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "Item [" << row[0] << "]" << endl;
            cout << "  description: " << (row[1] ? row[1] : "") << endl;
            cout << "  status: " << (row[2] ? row[2] : "") << endl;
            cout << "  your bidding price: " << (row[3] ? row[3] : "") << endl;
            cout << "  current highest bidder: " << (row[4] ? row[4] : "") << endl;
            cout << "  bid ending date: " << (row[5] ? row[5] : "") << endl;
        }
        cout << endl;
        mysql_free_result(res);
    }
    sql.clear();
}

#include <stdio.h>
bool Query::buyItem(User &user, int itemid, Regex &re)
{
    bool ret = false;
    char buf[512] = {0};
    string cur_time = re.getCurTimeString();
    time_t unix_time = re.getUnixTime(cur_time);
    string cur_time_unix = to_string(unix_time);
    string itemid_str = to_string(itemid);

    sprintf(buf, "select item_status from itemStatus where itemid = \"%s\";", itemid_str.c_str());
    string sql = buf;

    if (mysql_query(&conn, (char *)sql.c_str()))
        perror(__FILE__, __FUNCTION__, __LINE__);
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        while ((row = mysql_fetch_row(res)))
        {
            if (!row[0])
            {
                cout << "there's no itemid: " << itemid << endl;
                return false;
            }
            else if (atoi(row[0]) == -2)
            {
                cout << "unsold and bid endded item, you cannot buy it" << endl;
                return false;
            }
            else if (atoi(row[0]) == -1)
            {
                cout << "sold item, you cannot buy it" << endl;
                return false;
            }
            else if (atoi(row[0]) != 0)
            {
                cout << "you cannot buy it now, there are bids" << endl;
                return false;
            }
            break;
        }
        cout << endl;
        mysql_free_result(res);
    }

    res = NULL;

    sql.clear();
    memset(buf, 0x0, sizeof(buf) / sizeof(char));
    sprintf(buf, "call buyItNow(\"%s\",\"%s\",\"%s\",\"%s\");", user.email.c_str(), itemid_str.c_str(), cur_time_unix.c_str(), cur_time.c_str());
    sql = buf;
    if (mysql_query(&conn, (char *)sql.c_str()))
    {
        perror(__FILE__, __FUNCTION__, __LINE__);
        return false;
    }
    ret = true;
    return ret;
}

bool Query::bidItem(User &user, int itemid, int bid_price, Regex &re)
{
    bool ret = false;
    char buf[512] = {0};
    string cur_time = re.getCurTimeString();
    time_t unix_time = re.getUnixTime(cur_time);
    string cur_time_unix = to_string(unix_time);
    string itemid_str = to_string(itemid);
    string bid_price_str = to_string(bid_price);

    sprintf(buf, "call postBid(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\");", user.email.c_str(), itemid_str.c_str(), bid_price_str.c_str(), cur_time_unix.c_str(), cur_time.c_str());
    string sql = buf;
    if (mysql_query(&conn, (char *)sql.c_str()))
    {
        perror(__FILE__, __FUNCTION__, __LINE__);
        return false;
    }

    res = NULL;

    sql.clear();
    memset(buf, 0x0, sizeof(buf) / sizeof(char));
    sprintf(buf, "select success from currentBidSuccess where idx = 0");
    sql = buf;
    if (mysql_query(&conn, (char *)sql.c_str()))
    {
        perror(__FILE__, __FUNCTION__, __LINE__);
        return false;
    }
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        while ((row = mysql_fetch_row(res)))
        {
            if (!row[0])
            {
                cout << "there's no itemid: " << itemid << endl;
                return false;
            }
            else if (string(row[0]) == "failed")
            {
                return false;
            }
            else if (string(row[0]) == "success")
            {
                return true;
            }
        }
        cout << endl;
        mysql_free_result(res);
    }

    ret = true;
    return ret;
}

int Query::getAdminCntUsers(void)
{
    int ret = 0;
    string sql = "select num_of_users from adminCntUsers;";
    if (mysql_query(&conn, (char *)sql.c_str()))
    {
        perror(__FILE__, __FUNCTION__, __LINE__);
        return false;
    }
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        while ((row = mysql_fetch_row(res)))
        {
            if (row[0] == NULL)
            {
                ret = -1;
                break;
            }
            else
            {
                ret = atoi(row[0]);
                break;
            }
        }
        mysql_free_result(res);
    }
    return ret;
}
int Query::getAdminCntItems(void)
{
    int ret = 0;
    string sql = "select num_of_items from adminCntItems;";
    if (mysql_query(&conn, (char *)sql.c_str()))
    {
        perror(__FILE__, __FUNCTION__, __LINE__);
        return false;
    }
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        while ((row = mysql_fetch_row(res)))
        {
            if (row[0] == NULL)
            {
                ret = -1;
                break;
            }
            else
            {
                ret = atoi(row[0]);
                break;
            }
        }
        mysql_free_result(res);
    }
    return ret;
}
int Query::getAminCntBids(void)
{
    int ret = 0;
    string sql = "select num_of_bids from adminCntBids;";
    if (mysql_query(&conn, (char *)sql.c_str()))
    {
        perror(__FILE__, __FUNCTION__, __LINE__);
        return false;
    }
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        while ((row = mysql_fetch_row(res)))
        {
            if (row[0] == NULL)
            {
                ret = -1;
                break;
            }
            else
            {
                ret = atoi(row[0]);
                break;
            }
        }
        mysql_free_result(res);
    }
    return ret;
}

int Query::getAdminSumCommissions(void)
{
    int ret = 0;
    string sql = "select sum_of_commissions from adminSumCommissions;";
    if (mysql_query(&conn, (char *)sql.c_str()))
    {
        perror(__FILE__, __FUNCTION__, __LINE__);
        return false;
    }
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        while ((row = mysql_fetch_row(res)))
        {
            if (row[0] == NULL)
            {
                ret = -1;
                break;
            }
            else
            {
                ret = atoi(row[0]);
                break;
            }
        }
        mysql_free_result(res);
    }
    return ret;
}

double Query::getAdminAvgBidsPerItem(void)
{
    double ret = 0.0;
    string sql = "select avg_bids_per_item from adminAvgBidsPerItem;";
    if (mysql_query(&conn, (char *)sql.c_str()))
    {
        perror(__FILE__, __FUNCTION__, __LINE__);
        return false;
    }
    if (NULL == (res = mysql_store_result(&conn)))
        perror(__FILE__, __FUNCTION__, __LINE__);
    else
    {
        while ((row = mysql_fetch_row(res)))
        {
            if (row[0] == NULL)
            {
                ret = -1.0;
                break;
            }
            else
            {
                ret = atof(row[0]);
                break;
            }
        }
        mysql_free_result(res);
    }
    return ret;
}
#define BUFSIZE 512
void Query::setAdminBalanceMonthlyReset(Regex &re)
{
    string sql;
    char *buf = (char *)malloc(BUFSIZ * sizeof(char));
    struct tm *t;
    time_t cur_time = time(NULL);
    t = localtime(&cur_time);
    int year = t->tm_year + 1900;
    int month = t->tm_mon + 1;

    memset(buf, 0x0, BUFSIZE * sizeof(char));
    sprintf(buf, "%d-%d-1,00:00", year, month);
    string time_string;
    time_string.clear();
    time_string = buf;
    time_t unix_time = re.getUnixTime(time_string);
    memset(buf, 0x0, BUFSIZE * sizeof(char));
    sprintf(buf, "call adminResetBalanceMonthly(\"%ld\");", unix_time);
    sql.clear();
    sql = buf;
    if (mysql_query(&conn, (char *)sql.c_str()))
    {
        perror(__FILE__, __FUNCTION__, __LINE__);
    }
    free(buf);
}