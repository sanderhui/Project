#include "ent.h"

extern int g_mode;
extern int g_ent_flag;

void show_ent(void)
{
	int i=0;
	char *pic_buf[]={ "/mnt/udisk/pic/fish.bmp",
				"/mnt/udisk/pic/fish2.bmp",
				"/mnt/udisk/pic/fox.bmp",
				"/mnt/udisk/pic/lulu.bmp"};		
	show_shapebmp(0,0,800,480,pic_buf[0]);				
	while(1)
	{
			
			get_pos();
			if(end_pos.x - first_pos.x > 70)
			{
				i--;
				if(i==-1)i=3;
				show_shapebmp(0,0,800,480,pic_buf[i]);
				printf("%d",end_pos.x - first_pos.x > 70);
			}
			if(end_pos.x - first_pos.x < -70)
			{
				i++;
				if(i==4)i=0;
				show_shapebmp(0,0,800,480,pic_buf[i]);
				printf("%d",end_pos.x - first_pos.x > 70);
			}
			
			
		//back
		if(g_ent_flag == 1)
		{
			g_ent_flag = 0;
			g_mode = G_FUNC;
			break;
		}
	}


}