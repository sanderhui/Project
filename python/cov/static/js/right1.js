var right1 = echarts.init(document.getElementById('right1'), 'dark');
right1_option = {
    title:{
        text:"非湖北地区top5",
        textStyle:{
            color:'white',
        },
        left:'left'
    },
    color: ['#3398DB'],
    tooltip: {
        trigger: 'axis',
        axisPointer: {            // 坐标轴指示器，坐标轴触发有效
            type: 'shadow'        // 默认为直线，可选为：'line' | 'shadow'
        }
    },
    grid: {
        left: '3%',
        right: '4%',
        bottom: '3%',
        containLabel: true
    },
    xAxis: [
        {
            type: 'category',
            data: [],
            axisTick: {
                alignWithLabel: true
            }
        }
    ],
    yAxis: [
        {
            type: 'value'
        }
    ],
    series: [
        {
            name: '累计确诊',
            type: 'bar',
            barWidth: '60%',
            data: []
        }
    ]
};

right1.setOption(right1_option);