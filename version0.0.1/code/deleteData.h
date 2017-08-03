#pragma once 
#include "PM_Hub.h"

class deleteData
{
public:
	deleteData();
	~deleteData();
	void DeleteQueue();
	void DeletePM();
	void DeleteQueueFromList(CQueue* queue);
	void run(int qid, string str);
	void PMCallBackMethod(int qid, string str);
	void transfer(CQueue* queue, PM_Hub* PM_Hub);
	PM_Hub* pm_Hub();
private:
	PM_Hub* g_PM_Hub;
	vector<CQueue*> g_vecQueue;
};