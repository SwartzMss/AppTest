#include <iostream>
#include "CppSQLite3DB.h"
#include "MyLogger.h"

using namespace std;
MyLogger * pMyLogger = NULL;


int main(int argc, char *argv[])
{
	pMyLogger = MyLogger::getInstance();
	ERROR_LOG("the application started");

	IDataBase* m_pcDataBase = new(std::nothrow) CppSQLite3DB;
	m_pcDataBase->OpenDataBase("Swartz.db");
	PLANS_INFO_S* pPlansInfo = new PLANS_INFO_S;
	memset(pPlansInfo->sPlanID, 0x0, ID_LEN);
	pPlansInfo->bCheckFlag = 1;
	memcpy(pPlansInfo->sPlanID, "Swartz1", strlen("Swartz1"));
	m_pcDataBase->InsertToPlansTable(pPlansInfo);
	memset(pPlansInfo->sPlanID, 0x0, ID_LEN);
	pPlansInfo->bCheckFlag = 2;
	memcpy(pPlansInfo->sPlanID, "Swartz2", strlen("Swartz2"));
	m_pcDataBase->InsertToPlansTable(pPlansInfo);
	PlanInfoList st_planinfo;
	int nret =m_pcDataBase->GetPlansTable(st_planinfo);
	PlanInfoList::iterator itor = st_planinfo.begin();
	for (itor; itor != st_planinfo.end();itor++)
	{
		DEBUG_LOG("sPlanID = "<<itor->sPlanID<<" ,bCheckFlag =  "<<itor->bCheckFlag<<"!"<<endl);
	}
	return 0;
}
