#ifndef __DLLTEST_H
#define __DLLTEST_H

#include <iostream>
using namespace std;

class ITest
{
public:
	virtual void init()=0;
	virtual void uninit()=0;
	

};

extern "C"
{
	__attribute__ ((visibility("default"))) ITest* CreateTest();
	__attribute__ ((visibility("default"))) void  DestroyTest(ITest*);


}



#endif
