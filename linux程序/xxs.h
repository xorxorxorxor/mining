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
		pclose(pstr); //����Ƿ�ȥ����ȡ���ڵ�ǰϵͳ��ps�󣬽���ID���Ƿ��ǵ�һ���ֶ�
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
			//����
			return true;
		}
		else 
       {
			//������
			return false;
	
	    }
}
