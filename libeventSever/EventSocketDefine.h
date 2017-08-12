#include <event2/bufferevent.h>
#include <event2/bufferevent_compat.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer_compat.h>
#include <event2/http_struct.h>
#include <event2/bufferevent.h>
#include <event2/thread.h>
#include <pthread.h>
#include <list>
#include <iostream>
#include <string>
#include <pthread.h>
using namespace std;
#define MaxBuffLen  1024*4

struct _Conn;
struct _Worker;

//服务器属性封装对象
struct _Server
{
	
	bool bStart;
	short nPort;
	unsigned int connnum;
	int read_timeout;
	int write_timeout;
	struct evconnlistener *pListener;
	struct event_base *pBase;
	pthread_t hThread;
	_Worker *pWorker;
};
//连接对象列表
struct _ConnList
{
	_ConnList()
	{
		head = NULL;
		tail = NULL;
		plistConn = NULL;
	}
	_Conn *head;
	_Conn *tail;
	_Conn *plistConn;
};
//连接对象
struct _Conn
{
	_Conn()
	{
		fd = -1;
		bufev = NULL;
		index = -1;
		in_buf_len = 0;
		out_buf_len = 0;
		owner = NULL;
		next = NULL;
		in_buf = new char[MaxBuffLen];
		out_buf = new char[MaxBuffLen];
	}
	~_Conn()
	{
		delete[]in_buf;
		delete[]out_buf;
		bufferevent_free(bufev);
	}
	struct bufferevent *bufev;
	evutil_socket_t fd;
	int index;
	char *in_buf;
	short in_buf_len;
	char *out_buf;
	short out_buf_len;
	_Worker *owner;
	_Conn *next;
};

//工作线程封装对象.
struct _Worker
{
	_Worker()
	{
		pWokerbase = NULL;
		pListConn = NULL;
		pthread_mutex_init(&mutex,NULL);
	}
	~_Worker()
	{
		pWokerbase = NULL;
		pListConn = NULL;
		pthread_mutex_destroy(&mutex); 
	}
	struct event_base *pWokerbase;
	pthread_t hThread;
	_ConnList *pListConn;
	pthread_mutex_t mutex;
	inline _Conn* GetFreeConn()
	{
		_Conn*pItem = NULL;
		if (pListConn->head != pListConn->tail)
		{
			pItem = pListConn->head;
			pListConn->head = pListConn->head->next;
		}
		return pItem;
	}
	inline void PutFreeConn(_Conn *pItem)
	{
		pListConn->tail->next = pItem;
		pListConn->tail = pItem;
	}
};

typedef struct _Server Server;
typedef struct _Worker Worker;
typedef struct _Conn Conn;
typedef struct _ConnList ConnList;
