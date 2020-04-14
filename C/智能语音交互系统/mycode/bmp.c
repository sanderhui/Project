#include "bmp.h"

//显示全屏bmp图片
int show_fullbmp(char *bmpname)   //printf
{
	int i;
	int x,y;
	int lcdfd;
	int bmpfd;
	// 定义一个数组用于存放bmp的颜色值
	char bmpbuf[800*480*3];  // char占一个字节    bmpbuf[0] bmpbuf[1] bmpbuf[2]一组
	int lcdbuf[800*480]; // int占4字节
	
	// 定义一个临时变量保存颜色值
	int tempbuf[800*480];
	// 打开lcd的驱动
	lcdfd = open("/dev/fb0",O_RDWR);
	// 出错处理
	if(lcdfd == -1)
	{
		printf("open lcd error!\n");
		return -1;
	}
	// 打开你要显示的bmp图片
	bmpfd = open(bmpname,O_RDONLY);
	if(bmpfd == -1)
	{
		printf("open bmp error!\n");
		return -1;
	}
	// 在读之前，先跳过前面54字节
	lseek(bmpfd,54,SEEK_SET);
	// 读取bmp图片的颜色值,从55字节位置开始读取了
	read(bmpfd,bmpbuf,800*480*3);
	
	// 将读取的颜色值3字节---》转换成4字节
	for(i=0; i<800*480; i++)
		lcdbuf[i]=bmpbuf[3*i]|bmpbuf[3*i+1]<<8|bmpbuf[3*i+2]<<16|0x00<<24;

	// 将颠倒的图片翻转过来(x,y)--->(x,479-y)
	for(x=0; x<800; x++)  //列
		for(y=0; y<480; y++)   //行
			//lcdbuf[(479-y)*800+x] = lcdbuf[y*800+x];
			tempbuf[(479-y)*800+x] = lcdbuf[y*800+x];
			
	
	//将转换之后的颜色值写入到lcd的驱动中
	write(lcdfd,tempbuf,800*480*4);
	
	// 关闭lcd和bmp
	close(bmpfd);
	close(lcdfd);
	
	return 0;
}

/* int a = 5;
int *p = &a;
*p = 6;
*(&a) = 6; */


/*自定义函数，任意位置显示任意大小的bmp
	参数介绍：x ，y --》左上角x,y坐标
	          w ---》图片的实际宽
			  h ---》图片的实际高
			  bmpname---》图片的路径
*/ 
int show_shapebmp(int x,int y,int w,int h,char *bmpname)   //printf
{
	int i,j;
	int lcdfd;
	int bmpfd;
	int *lcdmem;
	// 定义一个数组用于存放bmp的颜色值
	char bmpbuf[w*h*3];  // char占一个字节    bmpbuf[0] bmpbuf[1] bmpbuf[2]一组
	int lcdbuf[w*h]; // int占4字节
	
	// 打开lcd的驱动
	lcdfd = open("/dev/fb0",O_RDWR);
	// 出错处理
	if(lcdfd == -1)
	{
		printf("open lcd error!\n");
		return -1;
	}

	// 将lcd的地址映射到用户空间  lcdmem看成lcd的第一个像素点的地址
	lcdmem = (int *)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdfd,0);
	if(lcdmem==NULL)
	{
		printf("map lcd error!\n");
		return -1;
	}
	// 打开你要显示的bmp图片
	bmpfd = open(bmpname,O_RDONLY);
	if(bmpfd == -1)
	{
		printf("open bmp error!\n");
		return -1;
	}
	// 在读之前，先跳过前面54字节
	lseek(bmpfd,54,SEEK_SET);
	// 读取bmp图片的颜色值,从55字节位置开始读取了
	read(bmpfd,bmpbuf,w*h*3);
	
	// 将读取的颜色值3字节---》转换成4字节
	for(i=0; i<w*h; i++)
		lcdbuf[i]=bmpbuf[3*i]|bmpbuf[3*i+1]<<8|bmpbuf[3*i+2]<<16|0x00<<24;

	// 将（i,j）---》存放在屏幕（i+x,j+y）的位置
	for(i=0; i<w; i++)
		for(j=0; j<h; j++)
			*(lcdmem+(j+y)*800+i+x) = lcdbuf[(h-1-j)*w+i];
	// 关闭lcd和bmp
	close(bmpfd);
	close(lcdfd);
	// 解除内存映射
	munmap(lcdmem,800*480*4);
	return 0;
}          