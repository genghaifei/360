#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
using namespace std;

const int BUFFER_SIZE = 1024;

void print_log(int err)
{
	cerr<<err<<" "<<strerror(errno)<<endl;
}

int get_line(int clientfd,char *buf,int len)
{
	int i = 0;
	for (;i<len;i++)
	{
		recv(clientfd,&buf[i],1,0);
		if (buf[i] == '\n')
			break;
		if (buf[i] == '\0')
			break;
	}
	return i;
}

int  get_line2(char *line,int len,FILE *fp)
{
	int i = 0;
	char buf;
	while(i < len-1)
	{
		line[i] = fgetc(fp);
		if (line[i] == EOF)
		{
			break;
		}
		if (line[i] == NULL)
		{
			break;
		}
		if (line[i] == '\n')
		{
			line[i+1] = '\0';
			return i+2;
		}
		i++;
	}
	if (i == 0)
		return 0;
	if (i == len-1)
		line[i] = '\0';
	return len;
}

int set_sock_noblock(int sock)
{
	int length = 0;
	setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&length,sizeof(length));
	return sock;
}

void* _accept(void* sock)
{
	printf("get new client\n");
	pthread_detach(pthread_self());
	int clientfd = (int)sock;
	clientfd = set_sock_noblock(clientfd);
	char buf[BUFFER_SIZE];
	char line[BUFFER_SIZE];
	while(1)
	{
		printf("enter while loop\n");
		
		int size = get_line(clientfd,buf,sizeof(buf));
		printf("get line success\n");
		if (strncasecmp("quit",buf,4) == 0)
			break;
		if(size == 0)
			continue;
		FILE* fp = popen(buf,"r");
		if (fp == NULL)
			exit(1);
		printf("popen success\n");
		int num = 0;
		while(1)
		{
			num = get_line2(line,BUFFER_SIZE,fp);
			printf("get_line2 success buf is %s\n",line);
			if (num == 0)
			{
				line[0] = (char)62;
				send(clientfd,line,1,0);
				break;
			}
			send(clientfd,line,num,0);
		}
		printf("one command success\n");
		fclose(fp);

	}
	close(clientfd);
	
}


void  set_sock_reuse_port(int listenfd)
{
	int flag = 1;
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));
}



int main()
{
	//daemon(0,0);
	int port = 8888;
	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd > 0);
	
	set_sock_reuse_port(listenfd);
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(port);

	socklen_t address_len = sizeof(address);
	int ret = bind(listenfd,(struct sockaddr*)&address,address_len);
	assert(ret != -1);
	
	ret = listen(listenfd,5);
	assert(ret != -1);
	
	pthread_t new_thread;
	int clientfd = -1;
	struct sockaddr_in client_address;
	socklen_t client_address_len = sizeof(client_address);
	while(1)
	{
		clientfd = accept(listenfd,(struct sockaddr*)&client_address,&client_address_len);
		if (clientfd == -1)
		{
			print_log(errno);
			continue;
		}
		ret = pthread_create(&new_thread,NULL,&_accept,(void *)clientfd);
		if (ret != 0)
		{
			print_log(errno);
			exit(1);
		}
	}
	return 0;
}
