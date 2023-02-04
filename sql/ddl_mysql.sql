SET foreign_key_checks = 0;

drop table if exists tUser;
create table tUser(
    -- userid is user's email address
    userid varchar(50) not null,
    passwd varchar(50) not null,
    first_name varchar(50) not null,
    last_name varchar(50) not null,
    isadmin varchar(5) default "user", -- cf. "admin"
    primary key pk (userid)
);

drop table if exists tItem;
create table tItem (
	-- item 일련번호
	itemid bigint auto_increment primary key,
    userid varchar(50) not null,
    -- bid_ending
	date_bidending varchar(50) not null,
    unixtime_bidending bigint not null,
    buyitnow_price varchar(50) not null,
	-- 구매 가능?
	-- unavailabe: date_bidending < local time 
	-- available: date_bidending > local time 
	-- item_status varchar(50) not null default "available", -- "available"/"unavailable"" 
	-- 아이템 컨디션
	cond varchar(50) not null,
    category varchar(50) not null,
	date_posted varchar(50) not null,
	description varchar(100),
    foreign key tItem(userid) references tUser(userid) on delete cascade
);

drop table if exists tTrade;
create table tTrade (
	itemid bigint not null,
	buyer_userid varchar(50) not null,
	seller_userid varchar(50) not null,
	bid_price bigint not null,
    date_posted varchar(50) not null,
    unixtime_posted bigint not null,
    foreign key fk1 (buyer_userid) references tUser(userid),
    foreign key fk2 (seller_userid) references tUser(userid),
    foreign key fk3 (itemid) references tItem(itemid) on delete cascade,
    primary key pk (itemid, buyer_userid, seller_userid, bid_price)
);

delimiter $$
drop function if exists rmNull $$
create function rmNull(v int)
returns int
begin
    declare ret int;
    set ret = (select if (v is null, 0, v));
    return ret;
end $$
delimiter ;

drop view if exists cntBidder;
create view cntBidder as 
    select itemid, count(*) as cnt
    from tItem join tTrade using (itemid)
    group by itemid;

drop view if exists maxBidder;
create view maxBidder as 
	select itemid, any_value(buyer_userid) as maxbidder, max(bid_price) as max_price 
	from tItem natural join (select itemid, buyer_userid, bid_price from tTrade) as t
	group by itemid;
								
delimiter $$
drop function if exists getStatus $$
create function getStatus(itemid bigint, unixtime_current bigint, unixtime_bidending bigint) 
returns int 
begin
	declare res int;
	set res = (select cnt from cntBidder as c where itemid = c.itemid);
    if (res is null) then
        set res = 0;
	end if;
	if (unixtime_bidending < unixtime_current) then
        if (res > 0) then
		    set res = -1; -- sold
        else 
            set res = -2; -- unsold
        end if;
    end if;
	return res;
end$$ 
delimiter ;

-- 1,2,..:bid, -1:sold, -2:unsold(end) 
drop view if exists itemStatus;
create view itemStatus as
    select itemid, getStatus(itemid, UNIX_TIMESTAMP(), unixtime_bidending) as item_status
    from tItem;

drop view if exists soldItem;
create view soldItem as
    select itemid, description, max_price as price, userid as seller_userid, maxbidder as buyer_userid
    from tItem natural join maxBidder natural join itemStatus
    where item_status = -1;

drop view if exists minusBalance;
create view minusBalance as 
    select buyer_userid as userid, sum(price) as minus_price 
    from soldItem
    group by buyer_userid; 

drop view if exists plusBalance;
create view plusBalance as
    select seller_userid as userid, sum(price) as plus_price 
    from soldItem
    group by seller_userid; 

delimiter $$
drop function if exists getMinusBalance $$
create function getMinusBalance(userid varchar(50))
returns int
begin
    declare ret int;
    set ret = (select minus_price from minusBalance as m where m.userid=userid);
    set ret = rmNull(ret);
    return ret;
end $$
delimiter ;

delimiter $$
drop function if exists getPlusBalance $$
create function getPlusBalance(userid varchar(50))
returns int
begin
    declare ret int;
    set ret = (select plus_price from plusBalance as m where m.userid=userid);
    set ret = rmNull(ret);
    return ret;
end $$
delimiter ;

delimiter $$
drop function if exists getCommission $$
create function getCommission(userid varchar(50))
returns int
begin
    declare ret int;
    set ret = getPlusBalance(userid);
    set ret = rmNull(ret);
    set ret = ret * 2;
    set ret = ret / 100;
    return ret;
end $$
delimiter ;

delimiter $$
drop function if exists getBalacne $$
create function getBalacne(userid varchar(50))
returns int
begin
    declare ret int;
    set ret = rmNull(getPlusBalance(userid)-getMinusBalance(userid)-getCommission(userid));
    return ret;
end $$
delimiter ;

drop view if exists balanceSheet;
create view balanceSheet as
    select userid, getPlusBalance(userid) as plus, getCommission(userid) as comm, getMinusBalance(userid) as minus, getBalacne(userid) as balance
    from tUser;

delimiter $$
drop function if exists getTradeStatus $$
create function getTradeStatus(itemid bigint, buyer_userid varchar(50), seller_userid varchar(50), bid_price bigint)
returns varchar(50)
begin
    declare ret varchar(50);
    declare maxbidder varchar(50);
    declare status int;

    set maxbidder = (select t.maxbidder from maxBidder as t where t.itemid=itemid);
    set status = (select s.item_status from itemStatus as s where s.itemid=itemid);
    if (status = -1) then
    	-- sold
    	if (maxbidder = buyer_userid) then
    		set ret = "You won the item";
    	else
    		set ret = "You are outbidded and the item is sold.";
    	end if;
    elseif (status = -2) then
    	-- unsold
    	set ret = "error: unexpected, you bidded, but no one own??";
    else 
    	if (maxbidder = buyer_userid) then
    		set ret = "You are the highest bidder.";
    	else
    		set ret = "You are outbidded.";
    	end if;
    end if;
    return ret;
end $$
delimiter ;

delimiter $$
drop function if exists getMaxBiddingPrice $$
create function getMaxBiddingPrice(itemid bigint)
returns bigint
begin
    declare ret bigint;
    set ret = 0;
    set ret = (select max(t.bid_price) from tTrade as t where t.itemid=itemid);
    if (ret is null) then
        set ret = 0;
    end if;
    return ret;
end $$
delimiter ;

drop view if exists bidStatus;
create view bidStatus as
    select i.itemid as itemid, i.description as description, getTradeStatus(t.itemid, t.buyer_userid, t.seller_userid, t.bid_price) as bid_status, t.bid_price as bid_price, getMaxBiddingPrice(i.itemid) as price, i.date_bidending as date_bidending, t.buyer_userid as buyer
    from tItem as i, tTrade as t where i.itemid=t.itemid; 

delimiter $$
drop procedure if exists buyItNow $$
create procedure buyItNow(
    buyer_userid varchar(50),
    itemid bigint,
    unixtime_bidending bigint,
    date_bidending varchar(50)
)
begin
    declare seller_userid varchar(50);
    declare buyitnow_price bigint; 
    set seller_userid = (select t.userid from tItem as t where t.itemid = itemid);
    set buyitnow_price = (select i.buyitnow_price from tItem as i where i.itemid = itemid);

    insert tTrade values(itemid, buyer_userid, seller_userid, buyitnow_price, date_bidending, unixtime_bidending);
    update tItem as i set i.date_bidending = date_bidending where i.itemid=itemid;
    update tItem as i set i.unixtime_bidending = unixtime_bidending where i.itemid=itemid;
end $$
delimiter ;

drop table if exists currentBidSuccess;
create table currentBidSuccess(idx bigint primary key, success varchar(50));
insert into currentBidSuccess values(0, "failed");

delimiter $$
drop procedure if exists postBid;
create procedure postBid (
    buyer_userid varchar(50), -- 파라미터 선언
    itemid bigint,
    bid_price bigint,
    unixtime_posted bigint,
    date_posted varchar(50)
)
begin
    declare item_status bigint;
    declare max_bid_price bigint;
    declare seller_userid varchar(50);
    set item_status = (select s.item_status from itemStatus as s where itemid = s.itemid);
    set seller_userid = (select i.userid from tItem as i where i.itemid=itemid);
    update currentBidSuccess as c set c.success = "failed" where c.idx = 0;
    if (item_status >= 0) then
        set max_bid_price = getMaxBiddingPrice(itemid);
        if (max_bid_price < bid_price) then 
            insert into tTrade values (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted);
            update currentBidSuccess as c set c.success = "success" where c.idx = 0;
        end if;
    end if;
end $$
delimiter ;

drop view if exists adminCntUserId;
drop view if exists adminCntItem;

drop view if exists adminCntUsers;
create view adminCntUsers as
    select count(distinct userid) as num_of_users from tUser;

drop view if exists adminCntItems;
create view adminCntItems as
    select count(distinct itemid) as num_of_items from tItem;

drop view if exists adminCntBids;
create view adminCntBids as
    select count(*) as num_of_bids from tTrade;

drop view if exists adminSumCommissions;
create view adminSumCommissions as
    select rmNull(sum(b.comm)) as sum_of_commissions from balanceSheet as b;

delimiter $$
drop function if exists divWithoutZero $$
create function divWithoutZero(a bigint, b bigint)
returns float 
begin
    declare ret float;
    declare aa float;
    declare bb float;
    if (b = 0) then
        set ret = null;
    elseif (a=0) then 
        set ret = 0;
    else
        set aa = a;
        set bb = b;
        set ret = aa/bb;
    end if;
    return ret;
end $$
delimiter ;

delimiter $$
drop function if exists cntTotBids $$
create function cntTotBids()
returns bigint
begin
    declare ret bigint;
    set ret = (select count(*) from tTrade);
    return rmNull(ret);
end $$
delimiter ;

delimiter $$
drop function if exists cntTotItems $$
create function cntTotItems()
returns bigint
begin
    declare ret bigint;
    set ret = (select count(*) from tItem);
    return rmNull(ret);
end $$
delimiter ;

drop view if exists adminAvgBidsPerItem;
create view adminAvgBidsPerItem as
    select divWithoutZero(cntTotBids(), cntTotItems()) as avg_bids_per_item;

delimiter $$
drop procedure if exists adminResetBalanceMonthly;
create procedure adminResetBalanceMonthly (reset_time_stamp bigint)
begin
    delete from tItem where unixtime_bidending < reset_time_stamp;
end $$
delimiter ;

SET foreign_key_checks = 1;
