#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include "MyLogger.h"

MyLogger * pMyLogger = NULL;


int main(void)
{
	pMyLogger = MyLogger::getInstance("swartz");
	DEBUG_LOG("main");

	while(1)
	{
		
		sleep(1);
	}
	return 0;
}
