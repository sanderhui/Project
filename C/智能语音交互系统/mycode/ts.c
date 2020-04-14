#include "ts.h"





//获取触摸屏坐标保存在ts_x和ts_y中
struct xy  get_pos()
{
	int flag = 1, flag1 = 1;
	struct input_event key;
	struct xy pos;

	
    while(1)
    {
		read(key_fd,&key,sizeof(key));
		if(key.type == EV_ABS)
		{
			if(key.code == ABS_X )
			{
				
				pos.x =  key.value; //获取x轴坐标
			}
			
			if(key.code == ABS_Y )
			{
				pos.y =  key.value; //获取y轴坐标
			}
			
			if(flag&&key.code == ABS_X)
			{
				first_pos.x = pos.x;
				flag = 0;
			}
			
			if(flag1&&key.code == ABS_Y)
			{
				first_pos.y = pos.y;
				flag1 = 0;
			}
			
			if(key.code == ABS_PRESSURE && key.value == 0 ) //触摸松开
			{
				end_pos.x = pos.x;
				end_pos.y = pos.y;
				break;
			} 		
		}
    }
	
	return pos;
}

//关闭触摸屏
