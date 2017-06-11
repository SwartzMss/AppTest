#pragma once
#include<iostream>
#include<string>
#include <log4Cplus/logger.h>
#include <log4Cplus/configurator.h>
#include <log4Cplus/layout.h>
#include <log4Cplus/loggingmacros.h>
#include <log4Cplus/helpers/stringhelper.h>

#define MY_LOG_FILE "./logconfig.properities"

#define DEBUG_LOG(logEvent) LOG4CPLUS_DEBUG(pMyLogger->logger,logEvent)
#define INFO_LOG(logEvent) LOG4CPLUS_INFO(pMyLogger->logger,logEvent)
#define ERROR_LOG(logEvent) LOG4CPLUS_ERROR(pMyLogger->logger,logEvent)
using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

class MyLogger
{
public:
	static MyLogger* getInstance();
	static void release();
	Logger logger;
private:
	MyLogger();
	~MyLogger();
	static MyLogger* my_logger;
};
extern MyLogger * pMyLogger;
