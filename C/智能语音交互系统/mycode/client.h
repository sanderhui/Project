#ifndef __CLIENT__
#define __CLIENT__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <math.h>   
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include "ts.h"
#include "bmp.h"
#include "ent.h"
#include "record.h"
#include "func.h"
#include "main.h"

int client();
void * gui_func(void *arg);

#endif  

