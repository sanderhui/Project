$(function () {
    setInterval(getTime, 1000)
    get_t_data();
    get_m_data();
    get_pic1();
    get_pic2();
    get_r1();
    get_r2();
    setInterval(get_t_data, 1000*3600)
    setInterval(get_m_data, 1000*3600)
    setInterval(get_pic1, 1000*3600)
    setInterval(get_pic2, 1000*3600)
    setInterval(get_r1, 1000*3600)
    setInterval(get_r2, 1000*3600)

    function get_r2() {
        $.ajax({
            url: '/get_r2/',
            type: 'GET',
        })
            .done(function (data) {
                if (data['code'] == 200) {

                    right2_option.series[0].data=data['kws'];

                    right2.setOption(right2_option)
                } else {
                    alert('返回错误');
                }

            })
            .fail(function () {
                alert('服务器超时，请重试！');
            });
    }


    function get_r1() {
        $.ajax({
            url: '/get_r1/',
            type: 'GET',
        })
            .done(function (data) {
                if (data['code'] == 200) {
                    right1_option.xAxis[0].data=data['city'];   //series是数组要取0
                    right1_option.series[0].data=data['confirm'];

                    right1.setOption(right1_option)
                } else {
                    alert('返回错误');
                }

            })
            .fail(function () {
                alert('服务器超时，请重试！');
            });
    }

    function get_pic2() {
        $.ajax({
            url: '/get_pic2/',
            type: 'GET',
        })
            .done(function (data) {
                if (data['code'] == 200) {
                    left2_option.xAxis.data=data['day'];   //series是数组要取0
                    left2_option.series[0].data=data['confirm_add'];
                    left2_option.series[1].data=data['suspect_add'];

                    left2.setOption(left2_option)
                } else {
                    alert('返回错误');
                }

            })
            .fail(function () {
                alert('服务器超时，请重试！');
            });
    }



    function get_pic1() {
        $.ajax({
            url: '/get_pic1/',
            type: 'GET',
        })
            .done(function (data) {
                if (data['code'] == 200) {
                    left1_option.xAxis.data=data['day'];   //series是数组要取0
                    left1_option.series[0].data=data['confirm'];
                    left1_option.series[1].data=data['suspect'];
                    left1_option.series[2].data=data['heal'];
                    left1_option.series[3].data=data['dead'];
                    left1.setOption(left1_option)
                } else {
                    alert('返回错误');
                }

            })
            .fail(function () {
                alert('服务器超时，请重试！');
            });
    }


    function get_m_data() {
        $.ajax({
            url: '/get_map_data/',
            type: 'GET',
        })
            .done(function (data) {
                if (data['code'] == 200) {
                    optionMap.series[0].data=data['data'];   //series是数组要取0
                    myChart.setOption(optionMap)
                } else {
                    alert('返回错误');
                }

            })
            .fail(function () {
                alert('服务器超时，请重试！');
            });
    }


    function getTime() {
        $.ajax({
            url: '/getTime/',
            type: 'GET',
        })
            .done(function (data) {
                if (data['code'] == 200) {
                    $('#show_time').html(data['data'])
                } else {
                    alert('返回错误');
                }

            })
            .fail(function () {
                alert('服务器超时，请重试！');
            });
    }


    function get_t_data() {
        $.ajax({
            url: '/get_t_data/',
            type: 'GET',
        })
            .done(function (data) {
                if (data['code'] == 200) {
                    $('.number h2').eq(0).text(data['confirm'])
                    $('.number h2').eq(1).text(data['suspect'])
                    $('.number h2').eq(2).text(data['heal'])
                    $('.number h2').eq(3).text(data['dead'])
                } else {
                    alert('返回错误');
                }

            })
            .fail(function () {
                alert('服务器超时，请重试！');
            });
    }
})