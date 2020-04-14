#ifndef _TS_H_
#define _TS_H_

//头文件
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <math.h>

//宏定义


int key_fd;
struct xy{
	int x;
	int y;
};

int key_fd;
struct xy first_pos;
struct xy end_pos;

struct xy  get_pos();
//函数声明



#endif