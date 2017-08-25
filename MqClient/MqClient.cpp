#include <unistd.h>
#include "AMQPcpp.h"

using namespace std;

int main(int argc, char** argv) 
{



	try {
		//		AMQP amqp;
		//		AMQP amqp(AMQPDEBUG);

		AMQP amqp("swartz:123456@192.168.1.107/swartz_host");	// all connect string

		AMQPExchange * ex = amqp.createExchange("swartz.test");
		ex->Declare("swartz.test", "topic", AMQP_DURABLE);

		AMQPQueue * qu2 = amqp.createQueue("test.que");
		qu2->Declare("test.que", AMQP_DURABLE);
		qu2->Bind("swartz.test", "test.*");

		std::cout << "Connected." << std::endl;

		/*std::string routing_key("hola");*/
		string ss = "message 1 ";

		ex->setHeader("Delivery-mode", 2);
		ex->setHeader("Content-type", "text/text");
		ex->setHeader("Content-encoding", "UTF-8");

		ex->Publish(ss, "test.*"); // publish very long message

		while (true)
		{
			ex->Publish("message 2 ", "test.*");
			ex->Publish("message 3 ", "test.*");
			sleep(1);
		}
		
		{
			AMQPQueue * qu = amqp.createQueue();
			qu->Cancel(amqp_cstring_bytes("hello-consumer"));
		}

	}
	catch (AMQPException e) {
		std::cout << e.getMessage() << std::endl;
	}

	return 0;

}

