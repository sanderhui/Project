#include "main.h"

int g_mode = G_FUNC;
int g_func_flag = 0;
int g_record_flag = 0;
int g_ent_flag = 0;



void user()
{
	char kj_buff[10][40] = {"/mnt/udisk/pic/kj1.bmp",
							"/mnt/udisk/pic/kj2.bmp",
							"/mnt/udisk/pic/kj3.bmp",
							"/mnt/udisk/pic/kj4.bmp",
							"/mnt/udisk/pic/kj5.bmp",
							"/mnt/udisk/pic/kj6.bmp",
							"/mnt/udisk/pic/kj7.bmp",
							"/mnt/udisk/pic/kj8.bmp",
							"/mnt/udisk/pic/kj9.bmp",
							"/mnt/udisk/pic/kj10.bmp"};
	int i=0,j=0;
	system("madplay /mnt/udisk/music/log.mp3 &");
	for(j=0; j<2; j++)
	{
		for(i=0; i<10; i++)
		{
			show_shapebmp(0,0,800,480,kj_buff[i]);
			usleep(100000);  //延时0.1s
		}
	}
}

int main( )
{
	user();
	pthread_t ts_thread;
	pthread_create(&ts_thread,NULL,ts_func,NULL);

	while(1)
	{
		switch(g_mode)
		{
			case G_FUNC:   //func
				show_func();
				break;
			case G_RECORD:   //music
				show_record();
				break;
			case G_ENT:   //camera
				show_ent();
				break;
		
		}
	}



	return 0;
}


//触摸屏线程 
void *ts_func(void *arg)
{
	
	
	key_fd=open("/dev/input/event0",O_RDONLY);
	
	while(1)
	{
		get_pos();
	
		if(g_mode == G_FUNC)
		{
			//music
			if(first_pos.x>170&&first_pos.x<320 && first_pos.y>170&&first_pos.y<320)
			{
				g_func_flag = 1;
			}
			
			//CAMERA
			if(first_pos.x>520&&first_pos.x<670 && first_pos.y>170&&first_pos.y<320)
			{
				g_func_flag = 2;	
			}
		}
		
		if(g_mode == G_ENT)
		{
			//BACK
			if(first_pos.x>720&&first_pos.x<800 &&first_pos.y>390&&first_pos.y<480)
			{
				g_ent_flag = 1;
			}
			
		}
		//录音
		if(g_mode == G_RECORD)
		{
			//BACK
			if(first_pos.x>720&&first_pos.x<800 && first_pos.y>390&&first_pos.y<480)
			{
				g_record_flag = 1;
			}
			//录音
			if(first_pos.x>300&&first_pos.x<500 && first_pos.y>300&&first_pos.y<480)
			{
				g_record_flag = 2;
			}
			//播放录音
			if(first_pos.x>0&&first_pos.x<200 && first_pos.y>280&&first_pos.y<480)
			{
				g_record_flag = 3;
			}
			//交互
			if(first_pos.x>300&&first_pos.x<500 && first_pos.y>0&&first_pos.y<200)
			{
				g_record_flag = 4;
			}
		}

	}
	
}


void * gif_func(void *arg) 
{
	char kj_buff[13][40] = {"/mnt/udisk/pic/timg1.bmp",
							"/mnt/udisk/pic/timg2.bmp",
							"/mnt/udisk/pic/timg3.bmp",
							"/mnt/udisk/pic/timg4.bmp",
							"/mnt/udisk/pic/timg5.bmp",
							"/mnt/udisk/pic/timg6.bmp",
							"/mnt/udisk/pic/timg7.bmp",
							"/mnt/udisk/pic/timg8.bmp",
							"/mnt/udisk/pic/timg9.bmp",
							"/mnt/udisk/pic/timg10.bmp",
							"/mnt/udisk/pic/timg11.bmp",
							"/mnt/udisk/pic/timg12.bmp",
							"/mnt/udisk/pic/timg13.bmp"
							};
	int i=0,j=0;
	for(j=0; j<2; j++)
	{
		for(i=0; i<10; i++)
		{
			show_shapebmp(0,0,800,480,kj_buff[i]);
			usleep(100000);  //延时0.1s
		}
	}
}