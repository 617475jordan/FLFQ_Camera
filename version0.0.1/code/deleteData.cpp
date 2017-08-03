#include "deleteData.h"

deleteData::deleteData()
{

}
deleteData::~deleteData()
{

}

void deleteData::DeleteQueue()
{
	CQueue* q;
	for (unsigned int i = 0; i < g_vecQueue.size(); i++)
	{
		q = g_vecQueue[i];
		if (q != NULL)
		{
			delete q;
			q = NULL;
		}
	}
	g_vecQueue.clear();
	DeletePM();
}
void deleteData::DeletePM()
{
	if (!g_vecQueue.empty())
	{
		DeleteQueue();
	}
	if (g_PM_Hub != NULL)
	{
		delete g_PM_Hub;
		g_PM_Hub = NULL;
	}
}
void deleteData::DeleteQueueFromList(CQueue* queue)
{

	for (vector<CQueue*>::iterator iter = g_vecQueue.begin(); iter != g_vecQueue.end(); iter++)
	{
		if (*iter == queue)
		{
			g_vecQueue.erase(iter);
			break;
		}
	}
	if (queue != NULL)
	{
		delete queue;
		queue = NULL;
	}
}


void deleteData::run(int qid, string str)
{
	cout << "qid=" << qid << "  str = " << str.c_str() << endl;
}

 void deleteData::PMCallBackMethod(int qid, string str)
{
	run(qid, str);
}
 void deleteData::transfer(CQueue* queue, PM_Hub* PM_Hub)
 {
	 g_vecQueue.push_back(queue);
	 g_PM_Hub = PM_Hub;
 }
 PM_Hub* deleteData::pm_Hub()
 {
	 return g_PM_Hub;
 }
