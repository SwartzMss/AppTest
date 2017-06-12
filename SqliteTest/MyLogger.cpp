#include "MyLogger.h"

MyLogger* MyLogger::my_logger = NULL;



MyLogger::MyLogger()
{
	log4cplus::initialize();
	PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(MY_LOG_FILE));
	/*logger = Logger::getRoot();*/
	logger = Logger::getInstance(LOG4CPLUS_TEXT("TEST"));
}


MyLogger::~MyLogger()
{
	if (my_logger)
	{
		delete my_logger;
		my_logger = NULL;
	}

}

MyLogger* MyLogger::getInstance()
{
	if (my_logger == NULL)
	{
		my_logger = new MyLogger;
	}
	return my_logger;
}

void MyLogger::release()
{
	delete my_logger;
	my_logger = NULL;
}

