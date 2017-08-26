#include "log4cxx/logger.h"
#include "log4cxx/propertyconfigurator.h"

static log4cxx::LoggerPtr logger1(log4cxx::Logger::getLogger("swartz"));
static log4cxx::LoggerPtr logger2(log4cxx::Logger::getLogger("Mss"));
int main(int argc, char *argv[])
{
log4cxx::PropertyConfigurator::configure("./log4cxx.properties");
LOG4CXX_INFO(logger1, "use swartz properities file");
LOG4CXX_INFO(logger2, "use  Mss properities file");
return 0;
}