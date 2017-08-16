#ifndef _XTIMER_H_
#define _XTIMER_H_

#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> 
#include <string.h>
#include <pthread.h>
/**
* 定时器回调函数类型定义
* @param [IN] ulUser 定时器回调函数携带的参数信息，该参数由OstimeSetEvent函数的ulUser参数传入
* @return 无
*/
typedef void (* XTIMERCALLBACK)(void* ulUser);

class XTimer
{
public:
	XTimer(void);
	~XTimer(void);
public:
	unsigned int XTimerStart(void);
	void XTimerStop(void);
	
/**
* 定时器设置函数
* @param [IN] ulDelay 	时间 ms为单位
* @param [IN] lpFunc  	定时器回调函数
* @param [IN] arg     	定时器回调函数携带的参数信息
* @param [IN] ulFlags   1代表是循环定时器，0代表是一次性定时器
* @return -1表示失败
*/
	unsigned int XTimerSetEvent( unsigned int ulDelay, XTIMERCALLBACK lpFunc, void* arg,unsigned int ulFlags);

public:
	int 			m_nTimerId;//定时器ID
	pthread_t 		m_ThreadId;//定时器内部的线程
	XTIMERCALLBACK  m_lpFunc;  //设置的回调函数
	void*           m_pUserData;
	volatile bool   m_bStop;
	int             m_epfd;

};
#endif