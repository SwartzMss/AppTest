#include "StaticFun.h"
#include "share.h"
#include <dlfcn.h>

typedef void* (*Func)();

int main()
{
	staticFunc();
	shareFunc();
	void* handle = dlopen("./libdlshare.so",RTLD_LAZY);
	Func FuncHandle = (Func)dlsym(handle,"dlshareFunc");
	FuncHandle();
	return 0;
}