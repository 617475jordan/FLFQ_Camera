#pragma once
/**************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2013, 上海飞来飞去新媒体展示设计有限公司
* All rights reserved.
* 
* @file		PM_Hub.h
*
* @version	7.0.0.3
* @author	
* @date		2013/10/16


* @brief	PM_Hub类作为PlayClient与用户端的接口，用来管理PlayClient播放及参数设置。
queue:

void NewQueue(int startTime, int loopTimes, int soloClientID, int isEraseAtEnd);
void AppendQueue(string mediaPath, string mediaType, int frameRate, int startFrame, int endFrame, int loopTimes);
void AppendQueueEx(string mediaPath, string mediaType, int mediaSectionID,int frameRate, int startFrame, int endFrame, int loopTimes);
void Count_Synch(int count_synch);
void EraseQueue();
void JumpToItem(int itemIndex, int isFreeze);
void MediaSeek(int time, int isFreeze);
void RequestVersion();
void SetBlend(float blend);
void SetCoords(float x,float y,int z,float width,float heigth);
void SetFade(int fadeStartTime, int fadeDuration, float start, float target, int isEraseAfterFade);
void SetStartTime(int startTime);
void SetVolume(float volume);
void SetRotation(float fRotateX, float fRotateY, float fRotateZ);
void SetWindow(float fWindowX, float fWindowY, float fWindowWidth, float fWindowHeight);
void Send();


playclient:
void SetUpClient(int clientID, int Rectx, int Recty, int Rectwidth, int Rectheight);

void ChangeDistortion(int clientID, string distortionName, int duration, string str,float reserve);

void Gotosleep(int clientID, int isSleep);

void RefreshParameter(int clientID, string reserve);
void Send();
**************************************************************************/
#ifdef PMHUBDLL_P
#define PMHUBDLL __declspec(dllexport)
#else
#define PMHUBDLL __declspec(dllimport)
#endif

#ifndef XTRA
#ifndef BOOST_ALL_DYN_LINK
#define BOOST_ALL_DYN_LINK
#endif
#endif

//#include <winsock2.h>
#include <windows.h>
#include <vector>
#include <string>
#include <list>
#include <vector>
#include <boost/thread.hpp>
typedef void* (*fCreateMoudle)(const GUID &IID);
typedef void(*fDeleteMoudle)(void**pInterface);

class BaseItem;
class IMGlobalSyncTimeService;
class IMNetworkTrans;
using namespace std;

class PMHUBDLL PM_Hub
{
public:
  PM_Hub(const char* pszSectionName = "PlayerManager");
public:
	~PM_Hub(void);
public:

  void SetUpClient(int clientID, int Rectx, int Recty, int Rectwidth, int Rectheight, int isCritical);
  void ChangeDistortion(int clientID, string distortionName, int duration, string str, float reserve, int isCritical);
  void Gotosleep(int clientID, int isSleep, int isCritical);
  void RefreshParameter(int clientID, string reserve, int isCritical);
  void SendLoaded();
  vector<BaseItem*> m_baseItem;
  boost::mutex m_lock;
  bool GetItemEndFeedback(int& nQueueID, string& strMediaPath);
  
  bool IsPlayerReturnedFeedback(const string& szmediaPath);
  LONGLONG getUniqueZ(int id);
  void AddEraseQID(int id);
  int GetQID();
private:
  vector<int> m_vecQIDerase;
  void Init(const char* pszsectionName = "PlayerManager");
  void Run();
  void Erase();
  void SendMsg(vector<BaseItem*> qlist, bool isPrint);
  void Send();
  void releaseUniqueZ(int id);
  bool  GetFeedback();
  
  bool HasFeedback();
  bool GetItemEndFeedback();
  // return the feedback information
  void RequestVersion();
private:
  int m_iQID;
  map<string, int> m_mapFeedback;
  int m_feedbackTempID;
  string m_feedbackTempMedia;
  boost::thread* m_pthread;
  bool m_bStop;
  int internal_Val;
  map<int, LONGLONG>  uniqueIdZ;
  list<int> m_ListID;
  string m_szSendID;
  string m_szReceiveID;
  string m_szSUMSHeader;
  /// <summary>	Zero-based index of the port. </summary>
  int iPort=1933;//修改此端口即可更换PC上的Screen
  int fps;
  IMNetworkTrans* m_pNetwork;
  bool m_bSend;
  HMODULE hModule;
  fCreateMoudle pCreateObjectFunc;
  fDeleteMoudle pDeleteObjectFunc;
  IMGlobalSyncTimeService		*m_pSyncTimeManager;
};


class PMHUBDLL CQueue
{
public:
	CQueue(PM_Hub* pm, int qID = -1);
public:
	~CQueue(void);

public:
	void NewQueue(int startTime, int loopTimes, int soloClientID, int isEraseAtEnd, int isCritical);
	void AppendQueue(string mediaPath, string mediaType, int frameRate, int startFrame, int endFrame, int loopTimes, int isCritical);
	void AppendQueueEx(string mediaPath, string mediaType, int mediaSectionID, int frameRate, int startFrame, int endFrame, int loopTimes, int isCritical);
	void Count_Synch(int count_synch);
	void EraseQueue(int isCritical);
	void JumpToItem(int itemIndex, int isFreeze, int isCritical);
	void MediaSeek(int time, int isFreeze, int isCritical);
	void SetBlend(float blend, int isCritical);
	void SetCoords(float x, float y, int z, float width, float heigth, int isCritical);
	void SetFade(int fadeStartTime, int fadeDuration, float start, float target, int isCritical);
	void SetStartTime(int startTime, int isCritical);
	void SetVolume(float volume, int isCritical);
	void SetRotation(float fRotateX, float fRotateY, float fRotateZ, int isCritical);
	void SetWindow(float fWindowX, float fWindowY, float fWindowWidth, float fWindowHeight, int isCritical);
	void SetUseFeedback(bool isFeedback);
	bool GetItemEndFeedback(string& szmediaPath);
	int GetQueueID();

private:
	PM_Hub* m_PlayerManager;
	bool m_bIsFeedback;
	int m_iQueueID;

};
