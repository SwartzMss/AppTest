#include "XTimer.h"

#define EPOLL_LISTEN_CNT        256
#define EPOLL_LISTEN_TIMEOUT    500

XTimer::XTimer(void)
{
	m_nTimerId = -1;
	
}

XTimer::~XTimer(void)
{
	
	
}

unsigned int XTimer::XTimerStart( void )
{
	 m_nTimerId = timerfd_create(CLOCK_REALTIME, 0);
	 if(-1 == m_nTimerId)
	 {
		 return -1;
	 }
	
}

void XTimer::XTimerStop(void)
{
	m_bStop = true;
	pthread_join(m_ThreadId, NULL);
	close(m_nTimerId);
}

static void *XWorkThread(void *arg) 
{
	XTimer * pXtimer = reinterpret_cast<XTimer*>(arg);
	  
	int i = 0;
    int fd_cnt = 0;
    int sfd;
    struct epoll_event events[EPOLL_LISTEN_CNT];    

    memset(events, 0, sizeof(events));  
	while(!pXtimer->m_bStop)
	{
		
		fd_cnt = epoll_wait(pXtimer->m_epfd, events, EPOLL_LISTEN_CNT, -1); 
        for(i = 0; i < fd_cnt; i++) 
        {   
            sfd = events[i].data.fd;
            if(events[i].events & EPOLLIN) 
            {   
                if (sfd == pXtimer->m_nTimerId) 
                {
					uint64_t exp = 0;
					read(sfd, &exp, sizeof(uint64_t));
                    pXtimer->m_lpFunc(pXtimer->m_pUserData);
                }   
            }   
        } 	
	}
}


unsigned int XTimer::XTimerSetEvent( unsigned int ulDelay, XTIMERCALLBACK lpFunc, void* arg,unsigned int ulFlags)
{
	if(m_nTimerId ==-1)
	{
		return -1;
	}
	struct itimerspec stTimeSpec;
	struct timespec stTimernow;
	if (clock_gettime(CLOCK_REALTIME, &stTimernow) == -1)
	{
	 return -1;
	}
	time_t tv_sec;
	long   tv_nsec;
	
	m_lpFunc = lpFunc;
	//计算时间
	tv_sec = (ulDelay * 1000000) / 1000000000;
	tv_nsec = (ulDelay * 1000000) % 1000000000;
	stTimeSpec.it_value.tv_sec = stTimernow.tv_sec + tv_sec;
	stTimeSpec.it_value.tv_nsec = stTimernow.tv_nsec + tv_nsec;
	//如果使用循环模式，设置循环间隔
	stTimeSpec.it_interval.tv_sec = ulFlags ? tv_sec : 0;
	stTimeSpec.it_interval.tv_nsec = ulFlags ? tv_nsec : 0;
	if (timerfd_settime(m_nTimerId, TFD_TIMER_ABSTIME, &stTimeSpec, NULL) == -1)
		return -1;
	m_epfd = epoll_create(EPOLL_LISTEN_CNT); 
	if(m_epfd < 0)
	{
		return -1;
	}
	
	struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.data.fd = m_nTimerId;
    event.events = EPOLLIN | EPOLLET;

    int  nret = epoll_ctl(m_epfd, EPOLL_CTL_ADD, m_nTimerId, &event);
	if(nret < 0)
	{
		return -1;
	}
	m_pUserData = arg;
	m_bStop = false;
	
	nret = pthread_create(&m_ThreadId, NULL, XWorkThread, (void*)(this));
	if(nret != 0)
	{
		return -1;
	}
	return 0;
}