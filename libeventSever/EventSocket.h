#ifndef _EVENT_SOCKET_H
#define _EVENT_SOCKET_H
#include "EventSocketDefine.h"
#include <string.h>
class EventSocket
{
public:
	EventSocket(void);
	~EventSocket(void);
public:
	//�˿ںţ��߳��� ����������� ,��д��ʱ
	bool StartServer(int port, unsigned int connnum, int read_timeout, int write_timeout);
	void StopServer();

private:
	static void  DoAccept(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data);
	static void  DoRead(struct bufferevent *bev, void *ctx);
	static void  DoError(struct bufferevent *bev, short error, void *ctx);

	static void* ThreadServer(void* lPVOID);
	static void* ThreadWorkers(void* lPVOID);
private:
	//��ǰ����������
	Server m_Server;

};



#endif