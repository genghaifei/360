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


void solve(map<char*,char*> &ma)
{
//	char name[LENGTH];
//	char ip[LENGTH/4];
	char line[LENGTH];
	char tmp[11];

	pair<map<char*,char*>::iterator,bool> insert_pair;

	FILE *file = popen("ifconfig","r");
	if (!file)
		return;
	int i = 0,j = 0;
	
	while(line[i] != EOF)
	{
		char name[LENGTH];
		char ip[LENGTH/4];
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

		insert_pair = ma.insert(pair<char*,char*>(name,ip));
		if(insert_pair.second == true)
			cout<<"insert successfully"<<endl;
		else
			cout<<"insert failed"<<endl;
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
	map<char*,char*> ma;
	solve(ma);
	map<char*,char*>::iterator lt;
	cout<<ma.size()<<endl;
	for (lt = ma.begin();lt != ma.end();lt++)
	{
		cout<<(*lt).first<<" "<<(*lt).second<<endl;
	}
	return 0;
}
