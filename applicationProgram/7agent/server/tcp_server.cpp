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
	}
	return i;
}
void* _accept(void* sock)
{	
	int clientfd = (int)sock;
	char buf[BUFFER_SIZE];
	char line;
	while(1)
	{
		int size = get_line(clientfd,buf,sizeof(buf));
		if (strcasecmp("quit",buf) == 0)
			break;
		if(size == 0)
			continue;
		FILE* fp = popen(buf,"r");
		while(1)
		{
			line = fgetc(fp);
			if (line == EOF)
				break;
			send(clientfd,&line,1,0);
		}
		fclose(fp);

	}
	close(clientfd);
	
}

int main()
{
	daemon(0,0);
	int port = 8888;
	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd > 0);

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
