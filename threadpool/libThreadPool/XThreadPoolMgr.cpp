#include <XThreadPoolMgr.h>

XThreadPoolMgr::XThreadPoolMgr(void):m_nMinWorkThreadNum(0),m_nMaxWorkThreadNum(0),
{
	
}


XThreadPoolMgr::~XThreadPoolMgr(void)
{
	
}

int XThreadPoolMgr::Init(int nMinWorkThreadNum, int nMaxWorkThreadNum)
{
    m_nMinWorkThreadNum = nMinWorkThreadNum;
    m_nMaxWorkThreadNum = nMaxWorkThreadNum;
	
	 //创建初始工作线程数;
    for (int i=0; i< nMinWorkThreadNum; i++)
    {
        IHikThread* pThread = NULL;
        IHikThreadManager::Instance()->CreateThread(FALSE, IHikThreadManager::HIK_THREAD_EVENT_QUEUE_REACTOR, NULL, pThread);
        //创建失败，销毁之前成功的所有线程;
        if (pThread==NULL)
        {
            DAG_ERROR("CreateThread failed");

            std::vector<IHikThread*>::iterator itr = m_vec4FreeWorkThread.begin();
            for (; itr!=m_vec4FreeWorkThread.end(); itr++)
            {
                IHikThread* pThread = *itr;
                IHikThreadManager::Instance()->Join(pThread);
                IHikThreadManager::Instance()->DestroyThread(pThread);
            }
            m_vec4FreeWorkThread.clear();

            return DAG_ERR;
        }

        DAG_INFO("Thread[%d] create succeed", pThread->GetThreadID());
        m_vec4FreeWorkThread.push_back(pThread);
    }

    return DAG_OK;
}