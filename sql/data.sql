set foreign_key_checks = 0;
-- user 
INSERT INTO tUser (userid, passwd, first_name, last_name, isadmin) VALUES('a@a.a', '1', 'a', 'a', 'admin');
INSERT INTO tUser (userid, passwd, first_name, last_name, isadmin) VALUES('b@b.b', '1', 'b', 'b', 'user');
INSERT INTO tUser (userid, passwd, first_name, last_name, isadmin) VALUES('c@c.c', '1', 'c', 'c', 'user');
INSERT INTO tUser (userid, passwd, first_name, last_name, isadmin) VALUES('d@d.d', '1', 'd', 'd', 'user');
INSERT INTO tUser (userid, passwd, first_name, last_name, isadmin) VALUES('e@e.e', '1', 'e', 'e', 'user');
INSERT INTO tUser (userid, passwd, first_name, last_name, isadmin) VALUES('f@f.f', '1', 'f', 'f', 'user');
INSERT INTO tUser (userid, passwd, first_name, last_name, isadmin) VALUES('g@g.g', '1', 'g', 'g', 'user');
INSERT INTO tUser (userid, passwd, first_name, last_name, isadmin) VALUES('h@h.h', '1', 'h', 'h', 'user');
INSERT INTO tUser (userid, passwd, first_name, last_name, isadmin) VALUES('i@i.i', '1', 'i', 'i', 'user');
INSERT INTO tUser (userid, passwd, first_name, last_name, isadmin) VALUES('j@j.j', '1', 'j', 'j', 'user');
INSERT INTO tUser (userid, passwd, first_name, last_name, isadmin) VALUES('k@k.k', '1', 'k', 'k', 'user');

-- items
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(1, 'a@a.a', '2022-11-21,22:32', 1669037520, '10000', 'Used (Acceptable)', 'Sporting Goods', '2022-11-21,22:18', 'desc 1');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(2, 'a@a.a', '2022-11-21,22:39', 1669037940, '1000', 'Used (Good)', 'Sporting Goods', '2022-11-21,22:20', 'desc 2');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(3, 'a@a.a', '2022-12-01,12:31', 1669865460, '30000', 'Like-New', 'Home', '2022-11-21,22:20', 'desc 3');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(4, 'a@a.a', '2022-12-01,12:10', 1669864200, '120000', 'New', 'Books', '2022-11-21,22:21', 'desc4');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(5, 'b@b.b', '2022-11-21,22:22', 1669036920, '200000', 'New', 'Electronics', '2022-11-21,22:22', 'desc 5 !!test test test test');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(6, 'c@c.c', '2022-11-21,22:26', 1669037160, '200000', 'Like-New', 'Home', '2022-11-21,22:23', 'desc 6 home home');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(7, 'd@d.d', '2022-12-01,12:00', 1669863600, '2000', 'Like-New', 'Electronics', '2022-11-21,22:24', 'desc desc test ');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(8, 'd@d.d', '2022-11-21,23:00', 1669039200, '20000', 'New', 'Sporting Goods', '2022-11-21,22:25', 'basket ball');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(9, 'g@g.g', '2022-11-21,22:28', 1669037280, '3181838', 'Used (Good)', 'Books', '2022-11-21,22:26', 'jwjfoihgew;');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(10, 'b@b.b', '2022-11-21,22:30', 1669037400, '200000', 'Used (Good)', 'Electronics', '2022-11-21,22:30', 'linux server');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(11, 'h@h.h', '2022-12-31,12:31', 1672457460, '122121', 'New', 'Electronics', '2022-11-21,22:32', 'new new buy it');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(12, 'j@j.j', '2022-11-21,22:40', 1669038000, '3999', 'Used (Acceptable)', 'Electronics', '2022-11-21,22:39', 'old tv');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(13, 'j@j.j', '2022-11-21,22:41', 1669038060, '9999', 'Used (Good)', 'Electronics', '2022-11-21,22:41', 'old tv, useful');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(14, 'g@g.g', '2022-11-21,22:45', 1669038300, '9999', 'Like-New', 'Books', '2022-11-21,22:43', 'The C Programming Language');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(15, 'j@j.j', '2022-11-21,22:45', 1669038300, '7777', 'Like-New', 'Clothing', '2022-11-21,22:45', 't-shirt');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(16, 'h@h.h', '2022-11-21,22:48', 1669038480, '99999', 'Used (Good)', 'Books', '2022-11-21,22:47', 'hello world');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(17, 'c@c.c', '2022-11-21,22:58', 1669039080, '7777', 'New', 'Home', '2022-11-21,22:56', 'home c home c');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(18, 'f@f.f', '2022-11-21,22:59', 1669039140, '2999', 'Like-New', 'Books', '2022-11-21,22:57', 'like like book like new');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(19, 'd@d.d', '2022-11-21,23:10', 1669039800, '29999', 'Used (Good)', 'Books', '2022-11-21,23:5', 'book for developer');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(20, 'e@e.e', '2022-11-22,00:00', 1669042800, '77777', 'New', 'Books', '2022-11-21,23:7', 'new phone');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(21, 'd@d.d', '2022-12-31,12:31', 1672457460, '77777', 'New', 'Electronics', '2022-11-21,23:8', 'ubuntu');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(22, 'b@b.b', '2022-11-21,23:11', 1669039860, '2999', 'Used (Good)', 'Sporting Goods', '2022-11-21,23:9', 'used ball');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(23, 'e@e.e', '2022-11-22,16:00', 1669100400, '12000', 'Used (Good)', 'Electronics', '2022-11-22,15:50', 'Used Computer, with comma, # %% ''.*');
INSERT INTO tItem (itemid, userid, date_bidending, unixtime_bidending, buyitnow_price, cond, category, date_posted, description) VALUES(24, 'a@a.a', '2022-11-25,23:17', 1669385820, '3900', 'Like-New', 'Home', '2022-11-25,23:15', 'kitchen towel with white silk like new ! ');

-- trades

INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(1, 'h@h.h', 'a@a.a', 10000, '2022-11-21,22:32', 1669037520);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(2, 'j@j.j', 'a@a.a', 1000, '2022-11-21,22:39', 1669037940);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(5, 'c@c.c', 'b@b.b', 200000, '2022-11-21,22:22', 1669036920);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(6, 'd@d.d', 'c@c.c', 10000, '2022-11-21,22:24', 1669037040);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(7, 'c@c.c', 'd@d.d', 200, '2022-11-21,22:46', 1669038360);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(7, 'h@h.h', 'd@d.d', 300, '2022-11-21,22:47', 1669038420);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(7, 'k@k.k', 'd@d.d', 100, '2022-11-21,22:29', 1669037340);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(8, 'c@c.c', 'd@d.d', 1000, '2022-11-21,22:49', 1669038540);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(8, 'e@e.e', 'd@d.d', 999, '2022-11-21,22:26', 1669037160);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(10, 'd@d.d', 'b@b.b', 200000, '2022-11-21,22:30', 1669037400);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(13, 'c@c.c', 'j@j.j', 9999, '2022-11-21,22:41', 1669038060);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(14, 'j@j.j', 'g@g.g', 9995, '2022-11-21,22:44', 1669038240);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(15, 'b@b.b', 'j@j.j', 7777, '2022-11-21,22:45', 1669038300);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(16, 'd@d.d', 'h@h.h', 99999, '2022-11-21,22:48', 1669038480);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(17, 'b@b.b', 'c@c.c', 777, '2022-11-21,22:57', 1669039020);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(18, 'g@g.g', 'f@f.f', 777, '2022-11-21,22:58', 1669039080);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(18, 'h@h.h', 'f@f.f', 999, '2022-11-21,22:58', 1669039080);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(19, 'h@h.h', 'd@d.d', 20000, '2022-11-21,23:6', 1669039560);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(20, 'b@b.b', 'e@e.e', 2000, '2022-11-21,23:7', 1669039620);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(21, 'f@f.f', 'd@d.d', 99999, '2022-11-21,23:9', 1669039740);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(22, 'c@c.c', 'b@b.b', 1999, '2022-11-21,23:10', 1669039800);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(23, 'c@c.c', 'e@e.e', 11000, '2022-11-22,15:51', 1669099860);
INSERT INTO tTrade (itemid, buyer_userid, seller_userid, bid_price, date_posted, unixtime_posted) VALUES(24, 'h@h.h', 'a@a.a', 2500, '2022-11-25,23:15', 1669385700);

set foreign_key_checks = 1;
