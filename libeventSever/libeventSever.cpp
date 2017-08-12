#include "EventSocket.h"


int main(int argc, char* argv[])
{
	EventSocket* pEventSocket = new EventSocket;
	pEventSocket->StartServer(5000,20000,5, 5);
	getchar();
	return 0;
}

