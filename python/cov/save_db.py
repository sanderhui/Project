import pymysql


class SaveDB(object):
    def __init__(self):
        db_params = {
            'host': '127.0.0.1',
            'port': 3306,
            'user': 'root',
            'password': '593445',
            'database': 'cov',
            'charset': 'utf8',
        }
        self.conn = pymysql.connect(**db_params)
        self.cursor = self.conn.cursor()

        self.details_sql = "insert into details(id,update_time,province," \
                           "city,confirm,suspect,dead,heal,deadRate,healRate) " \
                           "values(null,'%s','%s','%s','%s','%s','%s','%s','%s','%s')"
        self.history_sql = "insert into history values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"

        self.clond_sql = "insert into hotsearch(id,update_time,content) values(null,'%s','%s')"

    def p_clond_item(self,strtime,item):
        self.cursor.execute(self.clond_sql % (strtime, item))
        self.conn.commit()
    def p_details_item(self, item):

        self.cursor.execute(self.details_sql % (
            item['update_time'], item['province'], item['city'],
            item['confirm'],
            item['suspect'], item['dead'],
            item['heal'], item['deadRate'],
            item['healRate']
        ))
        self.conn.commit()

    def p_history_item(self, key, item):
        if 'confirm_add' in item:
            confirm_add = item['confirm_add']
        else:
            confirm_add = 0

        if 'suspect_add' in item:
            suspect_add = item['suspect_add']
        else:
            suspect_add = 0

        if 'dead_add' in item:
            dead_add = item['dead_add']
        else:
            dead_add = 0

        if 'healadd' in item:
            healadd = item['healadd']
        else:
            healadd = 0

        self.cursor.execute(self.history_sql % (
            key, item['confirm'], confirm_add,
            item['suspect'], suspect_add, item['dead'],
            dead_add, item['heal'], healadd,
            item['nowConfirm'], item['nowSevere']
        ))
        self.conn.commit()

    def close_db(self):
        self.conn.close()


"""

# alter table  history  rename date to did;
history表

CREATE TABLE history (
    did datetime NOT NULL COMMENT '日期',
    confirm int(11) DEFAULT NULL COMMENT'累计确诊',
    confirm_add int(11) DEFAULT NULL COMMENT'当日新增确诊',
    suspect int(11) DEFAULT NULL COMMENT'剩余疑似',
    suspect_add int(11) DEFAULT NULL COMMENT'当日新增疑似',
    dead int(11) DEFAULT NULL COMMENT'累计死亡',
    dead_add int(11) DEFAULT NULL COMMENT'当日新增死亡',
    heal int(11) DEFAULT NULL COMMENT'累计治愈',
    healadd int(11) DEFAULT NULL COMMENT'当日新增治愈',
    nowConfirm int(11) DEFAULT NULL COMMENT'现存确诊',
    nowSevere int(11) DEFAULT NULL COMMENT'现存重症',
    PRIMARY KEY(did)
);



create table details(
    id int(11) not null auto_increment,
    update_time datetime not null comment '数据最后更新时间',
    province varchar(50) default null comment '省',
    city varchar(50) default null comment '市',
    confirm int(11) default null comment '累计确诊',
    suspect int(11) default null comment '剩余疑似',
    dead int(11) default null comment '累计死亡',
    heal int(11) default null comment '累计治愈',
    deadRate FLOAT(5,2) default null comment '死亡率',
    healRate FLOAT(5,2) default null comment '治愈率',
    primary key(id) 
);


create table hotsearch(
    id int(11) not null auto_increment,
    update_time datetime default null on update current_timestamp,
    content varchar(255) default null,
    primary key(id) 
);

"""
# insert into details(id,update_time,province,city,confirm,suspect,dead,heal,deadRate,healRate) values(null,'2020-02-26 10:56:58',武汉,哈哈,4422,2313,231,322,0.44,32.33);"

# select city,confirm from details where update_time=(select update_time from details order by update_time limit 1) and province not in ('湖北','北京','天津','重庆','上海') union all select province as city ,sum(confirm) as confirm from details where update_time=(select update_time from details order by update_time limit 1) and province in ('上海','北京','天津','重庆') group by province