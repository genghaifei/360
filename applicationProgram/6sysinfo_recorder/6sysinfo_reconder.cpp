#include <stdio.h>
#include <iostream>
#include <errno.h>


int get_file_size(char* filename)
{
	FILE* fp = open(filename,"r");
	fseek(fp,0L,SEEK_END);
	int size = ftell(fp);
	fclose(fp);
	return size;
}

void sig_handler()
{
	struct stat st;
	int save_errno = errno;
	char *path = "./_file";
	if (stat(path,&st) == -1)
	{
		int ret = creat("./_file",O_RDWR);
		assert(ret > 0);
	}
	int size = get_file_size();
	if (size > 1048576)//1M
	{
		popen("./mv_file","r");
	}
	errno = save_errno;
}

void addsig(int sig)
{
	struct sigaction sa;
	memset(&sa,'\0',sizeof(sa));
	sa.sa_handler = sig_handler;
	sa.sa_flags |= SA_RESTART;
	sigfillset(&sa.sa_mask);
	assert(sigaction(sig,&sa,NULL)!=-1);
}



int main()
{
	daemon(0,0);
	alarm(36000)//every ten hours clean _file.
	char *buf;
	FILE* fp = open("./_file",O_RDWR | O_CREATE);
	FILE* re;
	time_t tm;
	while(1)
	{
		sleep(5);
		
		re = popen("./statistic_cpu.sh","r");
	    buf = fgets(buf,4,re);
		if (buf == NULL)
			continue;
		tm = time(NULL);
		sprintf("%d:%d:%d %d:%d:%d cpu use:%s\n",tm_year+1990,tm_mon,tm_mday,tm_hour,tm_min,tm_sec,buf);
		fputs(buf,fp);

	}
}
