#include "HelloService.h"
#include <iostream>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace ::test;

int main()
{

	shared_ptr<TTransport> socket(new TSocket("127.0.0.1", 9090));
	shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	HelloServiceClient client(protocol);

	try {
		transport->open();
		std::string res;
		client.hello(res, "lilei");
		std::cout << res << std::endl;
	}
	catch (TException &e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}