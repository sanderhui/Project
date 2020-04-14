#include "client.h" 
extern int g_mode;

	  
int client()
{
	int sock_fd, consock_fd ,len , file_fd , str_fd;
	struct sockaddr_in   server;         
	int size = 0 , str_i ;
	char cmd;
	pthread_t tid;
	int num = 0;
	key_fd= open("/dev/input/event0",O_RDONLY);
	//读取文件数据到buffer
	//选择IPV4  TCP传输
	sock_fd = socket(AF_INET,SOCK_STREAM,0);
	if(sock_fd == -1)
	{
		printf("sock failure \n");
		return -1;
	}
	
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;         /* IPV4*/  
	server.sin_port   = htons(8888);     /* Port number to use */ 
	server.sin_addr.s_addr = inet_addr("192.168.1.33");       /* My IP address */
	
	//连接服务器 连接信息封装在server结构体当中
	int status = connect(sock_fd, (struct sockaddr *) &server, sizeof(struct sockaddr_in));
	if(status == -1)
	{
		printf("connect failure\n");
		return -1;
	}
	
	printf("connect success\n");
	
	char buffer[1024] = {0};
	
	str_fd = open("str.txt",O_RDWR|O_CREAT|O_TRUNC,0777);	
	
	while(1)
	{    
			if(pthread_create(&tid, NULL, gif_func, NULL)<0)   //创建client子线程
			   {
				  printf("Create thread_cf failed!\n");
				  exit(0);
			   }
			system("arecord -d2 -c1 -r16000 -twav -fS16_LE voice.pcm");
			pthread_join(tid, NULL);
			//打开文件
			file_fd = open("voice.pcm",O_RDWR);
			while(1)
			{			
				size = read(file_fd,buffer,sizeof(buffer));
				{
					if(size == 0)
					{
						printf("read finish !\n");
						break;
					}
					//将读取的数据传输给server
					send(sock_fd, buffer, size, 0);
					//printf("size = %d\n",size);
					memset(buffer,0,sizeof(buffer));
				}
			}
			while(1)
			{		
				size = recv(sock_fd, buffer, sizeof(buffer), 0);
				//printf("%d\n",size);
				//将收到的数据写入文件
				write(str_fd,buffer,size);		
				if(size < 1024)
				{
					printf("recv data finish \n");
					break;
				}		
			}
			while(1)
			{		
				str_i=0;
				printf("%s",buffer);
				while(buffer[str_i++] != '\0')
				{
				  //printf("%c",buffer[str_i]);
				   if(buffer[str_i] == 'i' && buffer[str_i + 1] == 'd')
					   cmd = buffer[str_i + 4];
				}				
				memset(buffer,0,sizeof(buffer));	
				if(cmd == '1'){
					system("madplay /mnt/udisk/music/gnzw.mp3 &");
					break;
				}
				else if(cmd == '2'){
					system("killall -9 madplay &");
					break;
				}
				else if(cmd == '3'){
					system("killall -STOP madplay &");
					break;
				}
				else if(cmd == '4'){
					system("killall -CONT madplay &");
					break;
				}
				else if(cmd == '5'){
					
					break;
				}
				else if(cmd == '6'){
					g_mode = G_ENT;
					break;
				}
				else if(cmd == '7'){
					
					break;
				}
				else if(cmd == '8'){
					system("madplay /mnt/udisk/music/zwjs.mp3 &"); //自我介绍
					break;
				}
				else if(cmd == '9'){
					system("madplay /mnt/udisk/music/nh.mp3 &");//你好
					break;
				}
				else
				{
					printf("voice error , please speak :\n");
					g_mode = G_FUNC;
					break;
				}
			}
	break;				
   }
//关闭描述符
close(file_fd);
close(str_fd);
close(consock_fd);
close(sock_fd);
	
 
}