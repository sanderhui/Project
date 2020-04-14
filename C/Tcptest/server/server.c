#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT            4321
#define BUFFER_SIZE        15
#define MAX_QUE_CONN_NM   5
#define OFFSET	100

void *thrd_func(void *arg)
{
 	 int recvbytes,sockfd,sendbytes,a;
 	 FILE *cxr_txt,*down_txt;
     int client_fd = (int)arg,real_read_len;
     char buf[BUFFER_SIZE],down[10240],gvd[10]; 
     pthread_t qid1;
	/*调用recv()函数接收客户端的请求*/
	do
	{
		memset(buf, 0, sizeof(buf));
		memset(gvd, 0, sizeof(gvd));
		if ((recvbytes = recv(client_fd, buf, BUFFER_SIZE, 0)) == -1)
		{
			perror("recv");
			exit(1);
		}
		sleep(1);
		/*else 
		{
			res = pthread_create(&qid1,NULL,thrd_down,(void *)client_fd);
			if(res<0)
			{
				printf("Create thread failed!\n");
				exit(res);
			}
		}*/
		

		if ((a = recv(client_fd,gvd,100,0)) == -1)
		{
			perror("recv");
			exit(1);
		}sleep(1);
		printf("Received the message from client%d: %s\n",client_fd,buf);
		memset(down, 0, sizeof(down));
		
		if(strncmp(buf,"down",4)==0)
		{
			cxr_txt = fopen(gvd,"r");
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
				 if (sendbytes = send(client_fd, down, strlen(down), 0) == -1)
				 {
					  perror("send");
					  exit(1);
				 }
			}
			fclose(cxr_txt);
			printf("%s\n",down);
			printf("download success!\n");
		}
		if(strncmp(buf,"up",2)==0)
		{
			memset(down, 0, sizeof(down));
			down_txt = fopen(gvd,"w");
			
			if ((recvbytes = recv(client_fd, down, 100, 0)) == -1)
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
			printf("upload success!\n");
		}
		 
	}while(strncmp(buf,"exit",4));
	printf("Client %d has left\n",client_fd);
	close(client_fd);
	pthread_exit(0);
} 

int main()
{
	 struct sockaddr_in server_sockaddr,client_sockaddr;
     int sin_size,recvbytes;
     int sockfd, client_fd,qid,res;
     char buf[BUFFER_SIZE]; 
     while(1)
     {   
     /*建立socket连接*/
     if ((sockfd = socket(AF_INET,SOCK_STREAM,0))== -1)
     {
          perror("socket");
          exit(1);
     }

     /*设置sockaddr_in 结构体中相关参数*/
     server_sockaddr.sin_family = AF_INET;
     server_sockaddr.sin_port = htons(PORT);
     server_sockaddr.sin_addr.s_addr = INADDR_ANY;
     bzero(&(server_sockaddr.sin_zero), 8);
     
     int i = 1;/* 允许重复使用本地地址与套接字进行绑定 */
     setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
     
     /*绑定函数bind()*/
     if (bind(sockfd, (struct sockaddr *)&server_sockaddr,sizeof(struct sockaddr)) == -1)
     {
          perror("bind");
          exit(1);
     }
     
     /*调用listen()函数，创建未处理请求的队列*/
     if (listen(sockfd, MAX_QUE_CONN_NM) == -1)
     {
          perror("listen");
          exit(1);
     }
     printf("Listening....\n");
     
     /*调用accept()函数，等待客户端的连接*/
	while(1)
	{
	 sin_size=sizeof(struct sockaddr);
	 pthread_t qid;
	 if ((client_fd = accept(sockfd,(struct sockaddr *)&client_sockaddr, &sin_size)) == -1)
		{
			perror("accept");
			exit(1);
		}
		else
		{
			res = pthread_create(&qid,NULL,thrd_func,(void *)client_fd);
			if(res<0)
			{
				printf("Create thread failed!\n");
				exit(res);
			}
			printf("Connection from %d client\n",client_fd);
		}
	}
  }
}
         

