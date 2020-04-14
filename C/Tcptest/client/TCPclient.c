#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM		10
#define PORT   4321
#define BUFFER_SIZE 1024


int main(int argc, char *argv[])
{
     int a,b,sockfd,sendbytes,recvbytes,real_read_len;
     char buf[BUFFER_SIZE],but[BUFFER_SIZE],down[10240];
     char gvc[]={'.','/'},gvd[NUM],gve[NUM];
     FILE *down_txt;
     FILE *cxr_txt;
     struct hostent *host;
     struct sockaddr_in serv_addr;
     if(argc < 2)
     {
          fprintf(stderr,"USAGE: ./client Hostname(or ip address) \n");
          exit(1);
     }
     /*地址解析函数*/
     if ((host = gethostbyname(argv[1])) == NULL)
     {
          perror("gethostbyname");  
          exit(1);
     }
     memset(buf, 0, sizeof(buf));
     //sprintf(buf, "%s", argv[2]);
     /*创建socket*/
     if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
     {
          perror("socket");
          exit(1);
     }    
     /*设置sockaddr_in 结构体中相关参数*/
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_port = htons(PORT);
   	 serv_addr.sin_addr=*((struct in_addr *)host->h_addr);
     bzero(&(serv_addr.sin_zero), 8);
     /*调用connect函数主动发起对服务器端的连接*/
     if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))== -1)
     {
          perror("connect");
          exit(1);
     }
     /*发送消息给服务器端*/	
	do
	{
		 memset(gvd, 0, sizeof(gvd));
		 printf("please input some message(input 'exit' to close the client!)\n");
		 scanf("%s %s",buf,gvd);
		 
    	 /*fgets(but,sizeof(but),stdin);
    	 int b=0,e=0;
			while(but[b]!=' ')
			{
				buf[b]=but[b];
				b++;
			}
			b++;
			for(e;e<20;e++)
			{
				gvd[e]=but[b+e];
			}*/
		    memset(gvc, 0, sizeof(gvc));
		    char gvc[]={'.','/'};
			strcat(gvc,gvd);
			memset(gvd, 0, sizeof(gvd));
			printf("gvc:%s\n",gvc);
			if ((sendbytes = send(sockfd,buf,strlen(buf), 0)) == -1)
			 {
				  perror("send");
				  exit(1);
			 } 
			 sleep(1);
			 if((a = send(sockfd, gvc, strlen(gvc), 0)) == -1)
				{
				  perror("send");
				  exit(1);
			 	}
			 sleep(1);
			if(strncmp(buf,"down",4)==0)
			{
				memset(down, 0, sizeof(down));
				down_txt = fopen(gvc,"w");
				
			if ((recvbytes = recv(sockfd, down, 1024, 0)) == -1)
			{
				perror("recv");
				exit(1);
			}
			
			int a=0;
			while(down[a]!='\0')
			{
				a++;
			}
			fwrite(down,1,a,down_txt);
			fclose(down_txt);
			printf("%s\n",down);
			printf("download success!\n");
		}
		if(strncmp(buf,"up",2)==0)
		{
			memset(down, 0, sizeof(down));
			cxr_txt = fopen(gvc,"r");
			if(cxr_txt==NULL)
			{
				printf("file is not exit\n");
				exit(0);
			}
			if(fseek(cxr_txt,0,SEEK_SET)!=0)
			{
				perror("fseek error");
				exit(0);
			}
			while((real_read_len = fread(down,1,sizeof(down),cxr_txt))>0)
			{
			    if(real_read_len<0)
			    {
			      perror("fread error");
			    }
				 if ( b = send(sockfd, down, strlen(down), 0) == -1)
				 {
					  perror("send");
					  exit(1);
				 }
			}
			fclose(cxr_txt);
			printf("upload success!\n");
		}
		if(strncmp(buf,"quit",4)==0)
			{
				close(sockfd);
				exit(0);
			}
		
     }while(strncmp(buf,"exit",4));
     close(sockfd);
     exit(0);
}
