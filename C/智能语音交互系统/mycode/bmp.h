#ifndef _BMP_H_
#define _BMP_H_

//头文件 
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "client.h"
//宏定义 


//函数声明 
int show_fullbmp(char *bmpname);
int show_shapebmp(int x,int y,int w,int h,char *bmpname);

#endif