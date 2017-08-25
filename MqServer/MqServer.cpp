#include "AMQPcpp.h"

using namespace std;

int i = 0;

int onCancel(AMQPMessage * message) 
{
	cout << "cancel tag=" << message->getDeliveryTag() << endl;
	return 0;
}

int  onMessage(AMQPMessage * message)
{
	cout << "onMessage" << endl;
	uint32_t j = 0;
	char * data = message->getMessage(&j);
	if (data)
		cout << data << endl;

	i++;

	cout << "#" << i << " tag=" << message->getDeliveryTag() << " content-type:" << message->getHeader("Content-type");
	cout << " encoding:" << message->getHeader("Content-encoding") << " mode=" << message->getHeader("Delivery-mode") << endl;

	//if (i > 10) 
	//{
	//	AMQPQueue * q = message->getQueue();
	//	q->Cancel(message->getConsumerTag());
	//}
	return 0;
};


int main() {

	int reconnects = 10;
	/*while (reconnects++)*/
	{
		try {
			//		AMQP amqp("123123:akalend@localhost/private");
			reconnects++;
			AMQP amqp("swartz:123456@192.168.1.107/swartz_host");

			AMQPExchange * ex = amqp.createExchange("swartz.test");
			ex->Declare("swartz.test", "topic", AMQP_DURABLE);

			AMQPQueue * qu2 = amqp.createQueue("test.que");
			qu2->Declare("test.que", AMQP_DURABLE);
			qu2->Bind("swartz.test", "test.*");

			std::cout << "Connected." << std::endl;

			//qu2->setConsumerTag("hello-consumer");
			qu2->addEvent(AMQP_MESSAGE, onMessage);
			qu2->addEvent(AMQP_CANCEL, onCancel);

			qu2->Consume(AMQP_NOACK);//


		}
		catch (AMQPException e)
		{
			std::cout << e.getMessage() << std::endl;
		}
	}
	
	return 0;

}


