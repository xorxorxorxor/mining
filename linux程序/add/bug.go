package add

import (
	"log"
	"cpack"
)
var DebugLog *log.Logger
func Buglog(a string){
	if cpack.Log ==true {
		switch a {
			case "CsExistProcess":
				DebugLog.Println("程序已被杀死，复活中.")
		}
	}
}
