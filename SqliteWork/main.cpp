#include <iostream>
#include "CppSQLite3DB.h"

using namespace std;

//目前只是测试，demo里面会去打开 创建两个数据库
//一个UserTable 学习基本的数据库插件和插入操作
//第二个PlansTable，里面会插入一个基本的数据类型，同时进行一些查询操作
int main(int argc, char *argv[])
{
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
		cout<<"sPlanID = "<<itor->sPlanID<<" ,bCheckFlag =  "<<itor->bCheckFlag<<"!"<<endl;
	}
	return 0;
}
