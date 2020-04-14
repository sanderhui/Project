import string

from flask import Flask, render_template, jsonify
import utils
from jieba.analyse import extract_tags

app = Flask(__name__)
app.json_encoder = utils.MyJSONEncoder


@app.route('/')
def index():
    return render_template('main.html')


@app.route('/getTime/')
def getTime():
    data = utils.get_time()
    return jsonify({'code': 200, 'message': 'ok', 'data': data})


@app.route('/get_t_data/')
def get_t_data():
    data = utils.get_total_data()
    return jsonify({
        'code': 200,
        'message': 'ok',
        'confirm': data[0],
        'suspect': data[1],
        'heal': data[2],
        'dead': data[3]
    })


@app.route('/get_map_data/')
def get_map_data():
    data = []
    for k, v in utils.get_m_data():
        data.append({"name": k, "value": v})
    return jsonify({'code': 200, 'message': 'ok', 'data': data})


@app.route('/get_pic1/')
def get_pic1():
    data = utils.get_p1_data()
    day, confirm, suspect, heal, dead = [], [], [], [], []
    for a, b, c, d, e in data[7:]:
        day.append(a.strftime('%m-%d'))
        confirm.append(b)
        suspect.append(c)
        heal.append(d)
        dead.append(e)
    return jsonify({
        'code': 200,
        'message': 'ok',
        'day': day,
        'confirm': confirm,
        'suspect': suspect,
        'heal': heal,
        'dead': dead,

    })


@app.route('/get_pic2/')
def get_pic2():
    data = utils.get_p2_data()
    day, confirm_add, suspect_add = [], [], []
    for a, b, c in data[7:]:
        day.append(a.strftime('%m-%d'))
        confirm_add.append(b)
        suspect_add.append(c)
    return jsonify({
        'code': 200,
        'message': 'ok',
        'day': day,
        'confirm_add': confirm_add,
        'suspect_add': suspect_add,

    })


@app.route('/get_r1/')
def get_r1():
    data = utils.get_r1_data()
    city, confirm = [], []
    for a, b in data:
        city.append(a)
        confirm.append(b)

    return jsonify({
        'code': 200,
        'message': 'ok',
        'city': city,
        'confirm': confirm,

    })


@app.route('/get_r2/')
def get_r2():
    data = utils.get_r2_data()
    d = []
    for i in data:
        k = i[0].rstrip(string.digits)
        v = i[0][len(k):]
        ks = extract_tags(k)
        for j in ks:
            if not j.isdigit():
                d.append({'name': j, 'value': v})

    return jsonify({
        'code': 200,
        'message': 'ok',
        "kws": d

    })


@app.route('/test/')
def test():
    return render_template('test_echarts.html')


if __name__ == '__main__':
    app.run()
