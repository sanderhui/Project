#include "func.h"

extern int g_mode;
extern int g_func_flag;

void show_func(void)
{
	
	
	
	show_shapebmp(0,0,800,480,"/mnt/udisk/pic/func.bmp");
	
	while(1)
	{
		//music
		if(g_func_flag == 1)
		{
			g_func_flag = 0;
			g_mode = G_ENT;
			break;
		}
		
		
		//CAMERA
		if(g_func_flag == 2)
		{
			g_func_flag = 0;
			g_mode = G_RECORD;
			break;
		}
	
	}


}