#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

const int BUFFER_SIZE = 1024;

void usage(char* buf)
{
	cout<<"your program"<<buf<<"must input ip address anf port number "<<endl;
}
void get_message(int clientfd)
{
	char *buf;
	char recvm[BUFFER_SIZE];
	int ret = 0;
	while(1)
	{
		scanf("%s",buf);
		int t = strlen(buf);
		send(clientfd,buf,t,0);
	    do{
			ret = recv(clientfd,recvm,BUFFER_SIZE,0);
			cout<<recvm;
			memset(recvm,'\0',sizeof(recvm));
		}while(ret > 0);
	}
}

int main(int argc,char *argv[])
{
	if (argc <= 2)
	{
		usage(argv[0]);
		exit(1);
	}
	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd >0);

	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(atoi(argv[2]));
	client.sin_addr.s_addr = inet_addr(argv[1]);
	socklen_t client_len = sizeof(client);

	int ret = connect(listenfd,(struct sockaddr*)&client,client_len);
	assert(ret == 0);
	get_message(listenfd);

	return 0;
}
