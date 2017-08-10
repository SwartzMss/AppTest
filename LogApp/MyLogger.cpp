#include "MyLogger.h"

MyLogger* MyLogger::my_logger = NULL;



MyLogger::MyLogger(char* pLogName)
{
	log4cplus::initialize();
	PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(MY_LOG_FILE));
	logger = Logger::getInstance(pLogName);
}


MyLogger::~MyLogger()
{
	if (my_logger)
	{
		delete my_logger;
		my_logger = NULL;
	}

}

MyLogger* MyLogger::getInstance(char* pLogName)
{
	if (my_logger == NULL)
	{
		my_logger = new MyLogger(pLogName);
	}
	return my_logger;
}

void MyLogger::release()
{
	delete my_logger;
	my_logger = NULL;
}

