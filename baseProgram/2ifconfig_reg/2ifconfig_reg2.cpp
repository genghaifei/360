#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>
const int LENGTH = 1024;
using namespace std;

void get_line(char* line,FILE* file)
{
	int i = 0;
	while(1)
	{
		line[i] = fgetc(file);
		if (line[i] == EOF)
			break;
		if (line[i] == '\n')
			break;
		i++;
	}
}

void solve(map<string,string> &ma)
{
	char line[LENGTH];
	char tmp[LENGTH];
	map<string,string>::iterator lt;

	FILE *file = popen("ifconfig","r");
	if (!file)
		return;
	int i = 0,j = 0;
	
	while(line[i] != EOF)
	{
		string name;
		string ip;
		get_line(line,file);
		if (line[0] == EOF)
			break;
		while(line[i] != ' ')
		{
			name[j] = line[i];
			i++;
			j++;
		}
		name[j] = '\0';
		j = 0;
		i = 0;
		get_line(line,file);
		if (line[0] == EOF)
			break;
		while(line[i] == ' ')
		{
			i++;
		}

		int t = 0;
		for (;t<10;t++)
		{
			tmp[t] = line[i];
			i++;
		}
		tmp[t] = '\0';

		if(strcasecmp("inet addr:",tmp) == 0)
		{
			while(line[i] != ' ')
			{
				ip[j] = line[i];
				i++;
				j++;
			}
			ip[j] = '\0';
		}
		i = 0;
		j = 0;

	    ma.insert(pair<string,string>(name,ip));
		while(1)
		{
			get_line(line,file);
			if (line[0] == EOF)
				return;
			if (line[i] == '\n')
				break;
		}
	}
}


int main()
{
	map<string,string> ma;
	solve(ma);
	
	cout<<ma.size()<<endl;
	map<string,string>::iterator lt;
	for (lt = ma.begin();lt != ma.end();lt++)
	{
		cout<<(*lt).first<<" "<<(*lt).second<<endl;
	}
	return 0;
}
