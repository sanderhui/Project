from spider import CovSpider
from save_db import SaveDB
import time

if __name__ == '__main__':
    cov = CovSpider()
    db = SaveDB()
    all_data = cov.get_all_data()
    days = cov.get_day_data()
    if all_data and days:
        for i in all_data:
            db.p_details_item(i)
        # for k, v in days.items():
        #     db.p_history_item(k, v)
    else:
        print('获取数据错误')

    # content = cov.get_clond_data()
    # strtime = time.strftime('%Y-%m-%d %X')
    # for i in content:
    #     db.p_clond_item(strtime,i)
    # time.sleep(1)
    db.close_db()
