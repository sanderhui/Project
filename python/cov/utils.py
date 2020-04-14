import time
import pymysql

import decimal
import flask.json


class MyJSONEncoder(flask.json.JSONEncoder):

    def default(self, obj):
        if isinstance(obj, decimal.Decimal):
            # Convert decimal instances to strings.
            return str(obj)
        return super(MyJSONEncoder, self).default(obj)


def get_time():
    time_str = time.strftime("%Y{}%m{}%d{} %X")
    return time_str.format("年", "月", "日")


def get_conn():
    db_params = {
        'host': '127.0.0.1',
        'port': 3306,
        'user': 'root',
        'password': '593445',
        'database': 'cov',
        'charset': 'utf8',
    }
    conn = pymysql.connect(**db_params)
    cursor = conn.cursor()
    return conn, cursor


def close_conn(coon, cursor):
    cursor.close()
    coon.close()


def query(sql, *args):
    conn, cursor = get_conn()
    cursor.execute(sql, *args)
    res = cursor.fetchall()
    close_conn(conn, cursor)
    return res


def get_total_data():
    sql = "select sum(confirm),(select suspect from history order by did desc limit 1),\
            sum(heal),sum(dead) from details where \
            update_time=(select update_time from details order by update_time desc limit 1)"
    res = query(sql)
    return res[0]


def get_m_data():
    sql = "select province,sum(confirm) from details where \
           update_time=(select update_time from details order by update_time desc limit 1) \
           group by province"
    res = query(sql)
    return res


def get_p1_data():
    sql = "select did,confirm,suspect,heal,dead from history"
    res = query(sql)
    return res


def get_p2_data():
    sql = "select did,confirm_add,suspect_add from history"
    res = query(sql)
    return res


def get_r1_data():
    sql = "select city,confirm from (select city,confirm from details where update_time=(" \
          "select update_time from details order by update_time limit 1) " \
          "and province not in ('湖北','北京','天津','重庆','上海') " \
          "union all select province as city ,sum(confirm) as confirm from details where update_time=(" \
          "select update_time from details order by update_time limit 1)" \
          "and province in ('上海','北京','天津','重庆') group by province) as a order by confirm desc limit 5"
    res = query(sql)
    return res


def get_r2_data():
    sql = "select content from hotsearch order by id desc limit 20"
    res = query(sql)
    return res


if __name__ == '__main__':
    # print(get_time())
    # a = get_total_data()
    # b = get_m_data()
    # print(b)
    # c = get_p1_data()
    # print(c)
    # d = get_p2_data()
    # print(d)
    # e = get_r1_data()
    # print(e)
    d = get_r2_data()
    print(d)
