var right2 = echarts.init(document.getElementById('right2'), 'dark');

right2_option = {
    title: {
        text: '今日疫情热搜',//标题
        x: 'center',
        textStyle: {

            color:'white'
        },
        left:'left'

    },
    // backgroundColor: '#F7F7F7',
    tooltip: {
        show: false
    },
    series: [{
        name: '疫情热搜',//数据提示窗标题
        type: 'wordCloud',
        sizeRange: [12, 55],//画布范围，如果设置太大会出现少词（溢出屏幕）
        rotationRange: [-45,0,45, 90],//数据翻转范围
        //shape: 'circle',
        textPadding: 0,
        autoSize: {
            enable: true,
            minSize: 6
        },
        textStyle: {
            normal: {
                color: function() {
                    return 'rgb(' + [
                        Math.round(Math.random() * 255),
                        Math.round(Math.random() * 255),
                        Math.round(Math.random() * 255)
                    ].join(',') + ')';
                }
            },
            emphasis: {
                shadowBlur: 10,
                shadowColor: '#333'
            }
        },
        data: []//name和value建议用小写，大写有时会出现兼容问题
    }]
};


right2.setOption(right2_option);