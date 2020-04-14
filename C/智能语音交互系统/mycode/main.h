#ifndef _MAIN_H_
#define _MAIN_H_

//头文件
#include <stdio.h>
#include <pthread.h>
#include "bmp.h"
#include "ts.h"
#include "func.h"
#include "ent.h"
#include "record.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "client.h"

//宏定义
#define  G_FUNC			1
#define  G_RECORD		2
#define  G_ENT			3

//函数声明
void *ts_func(void *arg);
void * gif_func(void *arg);


#endif