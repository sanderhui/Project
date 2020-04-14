import requests
import json
import time
from selenium import webdriver


class CovSpider(object):
    def __init__(self):
        self.all_url = "https://view.inews.qq.com/g2/getOnsInfo?name=disease_h5"
        self.day_url = "https://view.inews.qq.com/g2/getOnsInfo?name=disease_other"
        self.clond_url = "https://voice.baidu.com/act/virussearch/virussearch?from=osari_map&tab=0&infomore=1"
        self.headers = {
            'user-agent': "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.122 Safari/537.36"
        }
        self.driver_path = r"D:\often\chromedriver_win32\chromedriver.exe"  # 路径

    def get_clond_data(self):
        option = webdriver.ChromeOptions()
        option.add_argument("--headless")  # 隐藏
        option.add_argument("--no-sandbox")

        driver = webdriver.Chrome(executable_path=self.driver_path, options=option)  # 创建driver
        driver.get(self.clond_url)
        btn = driver.find_element_by_xpath("//div[@class='VirusHot_1-4-9_1Fqxy-']")
        btn.click()
        time.sleep(1)
        titles = driver.find_elements_by_xpath(
            '//*[@id="main"]/div/div/section/div[2]/div/div[2]/section/a/div/span[2]')
        context = [i.text for i in titles]
        print(context)
        driver.close()
        return context

    def get_all_data(self):
        res = requests.get(self.all_url, headers=self.headers)
        all_data = json.loads(res.text)
        dict_data = json.loads(all_data['data'])

        details = []  # 当日详细细数据
        update_time = dict_data['lastUpdateTime']
        data_country = dict_data['areaTree']
        data_province = data_country[0]['children']  # 省份
        for pro_infos in data_province:
            province = pro_infos['name']
            for city_infos in pro_infos['children']:
                city = city_infos['name']
                confirm = city_infos['total']['confirm']
                suspect = city_infos['total']['suspect']
                dead = city_infos['total']['dead']
                deadRate = city_infos['total']['deadRate']
                heal = city_infos['total']['heal']
                healRate = city_infos['total']['healRate']
                details.append({
                    'update_time': update_time,
                    'province': province,
                    'city': city,
                    'confirm': confirm,
                    'suspect': suspect,
                    'dead': dead,
                    'deadRate': deadRate,
                    'heal': heal,
                    'healRate': healRate
                })
        return details

    def get_day_data(self):
        res = requests.get(self.day_url, headers=self.headers)
        all_data = json.loads(res.text)
        dict_data = json.loads(all_data['data'])

        history = {}
        for day in dict_data['chinaDayList']:
            confirm = day['confirm']
            suspect = day['suspect']
            dead = day['dead']
            heal = day['heal']
            nowConfirm = day['nowConfirm']
            nowSevere = day['nowSevere']

            date = '2020.' + day['date']
            date = time.strftime("%Y-%m-%d", time.strptime(date, '%Y.%m.%d'))

            history[date] = {
                'confirm': confirm,
                'suspect': suspect,
                'dead': dead,
                'heal': heal,
                'nowConfirm': nowConfirm,
                'nowSevere': nowSevere
            }

        for day in dict_data['chinaDayAddList']:
            confirm = day['confirm']
            suspect = day['suspect']
            dead = day['dead']
            heal = day['heal']
            date = '2020.' + day['date']
            date = time.strftime("%Y-%m-%d", time.strptime(date, '%Y.%m.%d'))

            history[date].update({
                'confirm_add': confirm,
                'suspect_add': suspect,
                'dead_add': dead,
                'heal_add': heal,
            })

        return history


if __name__ == '__main__':
    cov = CovSpider()
    # a = cov.get_day_data()
    # b = cov.get_all_data()
    # print(a)
    # print(b)
    cov.get_clond_data()
