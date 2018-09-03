#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>

extern int atoi(const char *nptr);
bool IsExistProcess(char name[PATH_MAX])
{
		FILE *pstr; 
		char cmd[128],buff[512];
		pid_t pID;
		int pidnum;
		char *p = NULL;
		int ret=3;
		memset(cmd,0,sizeof(cmd));
		sprintf(cmd, "ps -ef|grep %s",name);
		pstr=popen(cmd, "r");
		if(pstr==NULL)
		{ return 1; }
		memset(buff,0,sizeof(buff));
		fgets(buff,512,pstr);
		p=strtok(buff, " ");
		p=strtok(NULL, " "); 
		pclose(pstr); //这句是否去掉，取决于当前系统中ps后，进程ID号是否是第一个字段
		if(p==NULL)
		{ 
			return 1; 
		}
		if(strlen(p)==0)
		{ 
			return 1; 
		}
		if((pidnum=atoi(p))==0)
		{
			return 1; 
		}
		pID=(pid_t)pidnum;
		ret=kill(pID,0);
		if(0==ret)
		{
			//存在
			return true;
		}
		else 
       {
			//不存在
			return false;
	
	    }
}
