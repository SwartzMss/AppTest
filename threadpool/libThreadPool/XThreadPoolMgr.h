#ifndef XTHREADPOOLMGR_H_
#define XTHREADPOOLMGR_H_
#include <vector>

class IXThread
{
	
	
};


class XThreadPoolMgr
{
public:
    XThreadPoolMgr(void);
    ~XThreadPoolMgr(void);
	
    int Init(int nMinWorkThreadNum, int nMaxWorkThreadNum);
    int Fini();
	
private:
    int CalcWorkThreadNum(); //计算空闲的线程数	
private:
    int                                 m_nMinWorkThreadNum;        ///< 最小线程数;
    int                                 m_nMaxWorkThreadNum;        ///< 最大线程数;
    std::vector<IXThread*>           	m_vecBusyWorkThread;       ///< 忙碌工作线程队列;
    std::vector<IXThread*>            	m_vecFreeWorkThread;       ///< 空闲工作线程队列;
};


#endif