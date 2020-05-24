package main

//typedef int (*intFunc) ();
//extern int bridge_int_func(intFunc f);
import "C"
import (
	"unsafe"
	"fmt"
	"usertweet"
)

//export InitEncrypt
func InitEncrypt(cEncryptFn unsafe.Pointer) int {
	f := C.intFunc(cEncryptFn)
	fmt.Println(int(C.bridge_int_func(f)))
	return 5
}

var handles []*usertweet.UserTweet

// NewHandleID is a C API for a new handle
//export NewHandleID
func NewHandleID() (rc int) {
	u := usertweet.New()
	handles = append(handles, u)
	return len(handles) - 1
}

// GetLastTweetByHandle is a C API for GetLastTweet
//export GetLastTweetByHandle
func GetLastTweetByHandle(i int, user *C.char) (rc int, tweet *C.char, errstr *C.char) {
	u := handles[i]
	twt, err := u.GetLastTweet(C.GoString(user))
	if err != nil {
		return -1, nil, C.CString(fmt.Sprintf("%v", err))
	}
	return 0, C.CString(fmt.Sprintf("%v", twt)), nil
}

// Close is a C API to cleanup handle
//export Close
func Close(i int) {
	handles[i] = nil
}

func main() {}
