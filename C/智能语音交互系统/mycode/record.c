#include "record.h"

extern int g_mode;
extern int g_record_flag;

void show_record(void)
{
	show_shapebmp(0,0,800,480,"/mnt/udisk/pic/record.bmp");
	pthread_t gif_tid;
	while(1)
	{
		//back
		if(g_record_flag == 1)
		{
			g_record_flag = 0;
			g_mode = G_FUNC;
			break;
		}
		//录音
		if(g_record_flag == 2)
		{
			g_record_flag = 0;
			pthread_create(&gif_tid, NULL,gif_func,NULL);
			system("arecord -d4 -c1 -r16000 -twav -fS16_LE example.wav");
			pthread_join(gif_tid,NULL);			
			break;
		}
		
		
		if(g_record_flag == 3)
		{
			g_record_flag = 0;
			show_shapebmp(0,0,800,480,"/mnt/udisk/pic/bofang.bmp");
			system("aplay example.wav &");	
			sleep(5);
			show_shapebmp(0,0,800,480,"/mnt/udisk/pic/record.bmp");
			break;
		}
		
		//
		if(g_record_flag ==4)
		{
			g_record_flag = 0;
			client();
			break;
		}
	}


}