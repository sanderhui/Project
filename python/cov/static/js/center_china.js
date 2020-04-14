

var mydata = [];

var optionMap = {
                // backgroundColor: '#FFFFFF', 地图颜色
                // 标题
                title: {
                    text: '',
                    subtext: '',
                    x:'left'
                },

                tooltip : {
                    trigger: 'item'
                },

                //左侧小导航图标
                visualMap: {
                    show : true,
                    x: 'left',
                    y: 'bottom',
                    splitList: [
                        {start: 1, end:9},{start: 10, end: 99},
                        {start: 100, end: 999},{start: 1000, end: 9999},
                        {start: 10000},
                    ],
                    color: ['#8a3310', '#c64918', '#e55b25','#f2ad92', '#f9dcd1']
                },

                //配置属性
                series: [{
                    name: '累计确诊人数',
                    type: 'map',
                    mapType: 'china',
                    roam: true,//拖动缩放
                    itemStyle:{
                        normal:{
                            borderWidth:.5,//区域边框宽度
                            borderColor:'#009fe8',
                            areaColor:'#fff',
                        },
                        emphasis: {
                            borderWidth:.5,//区域边框宽度
                            borderColor:'#4b0082',
                            areaColor:'#fff',
                        }
                    },

                    label: {
                        normal: {
                            show: true,  //省份名称
                            fontSize:10,
                        },
                        emphasis: {
                            show: true,
                            fontSize:10,
                        }
                    },
                    data:mydata  //数据
                }]
            };
        //初始化echarts实例
        var myChart = echarts.init(document.getElementById('center2'), 'dark');

        //使用制定的配置项和数据显示图表
        myChart.setOption(optionMap);
