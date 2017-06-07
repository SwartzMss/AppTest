#include "Idlltest.h"
#include "Cdlltest.h"

ITest* CreateTest()
{
	return new CTest;

}

void DestroyTest(ITest* pTest)
{
	delete pTest;
	pTest=NULL;
}
