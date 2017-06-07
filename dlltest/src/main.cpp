#include <iostream>
#include "Idlltest.h"
#include <dlfcn.h>

using namespace std;
typedef ITest* (*CreateObj)();
typedef void (*DestroyObj)(ITest*);

int main()
{
	//ITest* test = CreateTest();
	//test->init();
	//test->uninit();
	//DestroyTest(test);
	void* handle = dlopen("./libdlltest.so",RTLD_LAZY);
	CreateObj CreateHandle = (CreateObj)dlsym(handle,"CreateTest");
	DestroyObj DestroyHandle = (DestroyObj)dlsym(handle,"DestroyTest");
	ITest* test1 = CreateHandle();
	test1->init();
	test1->uninit();
	DestroyHandle(test1);
	return 0;

}
