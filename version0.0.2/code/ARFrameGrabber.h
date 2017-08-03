// ARFrameGrabber.h: interface for the ARFrameGrabber class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARFRAMEGRABBER_H__C5553937_4BAB_4FEF_B4A6_1693AB0C99E3__INCLUDED_)
#define AFX_ARFRAMEGRABBER_H__C5553937_4BAB_4FEF_B4A6_1693AB0C99E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <AR/config.h>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <tchar.h>
#include "DsCaptureImpExp.h"

#include "opencv_all.h"
////#include "cv.h"
////#include "cxcore.h"
////#pragma comment(lib, "cxcore.lib")
////#pragma comment(lib, "cv.lib")

//class  SmartString
//{
//public:
//	SmartString():str(NULL) {}
//
//	SmartString(char* pStr):str(NULL)
//	{
//		if (pStr)
//		{
//			int size = int(strlen(pStr));
//			str = new char[size+1];
//			strcpy(str, pStr);
//		}
//	}
//
//	SmartString(SmartString& sStr)
//	{
//		SetString(sStr.GetBuffer());
//	}
//
//	~SmartString()
//	{
//		if (str)
//			delete[] str;
//	}
//
//	SmartString& operator =(char* pStr)
//	{
//		SetString(pStr);
//		return *this;
//	}
//
//	SmartString& operator =(SmartString& sStr)
//	{
//		SetString(sStr.GetBuffer());
//		return *this;
//	}
//
//	char* GetBuffer() {return str;}
//
//protected:
//	void SetString(char *pStr)
//	{
//		if (str)
//			delete[] str;
//
//		if (!pStr)
//		{
//			str = NULL;
//		}
//		else
//		{
//			int size = int(strlen(pStr));
//			str = new char[size + 1];
//			strcpy(str, pStr);
//		}
//
//	}
//
//
//	char* str;
//};
//
//class DeviceInfo
//{
//public:
//	DeviceInfo():next(NULL), deviceId(-1)
//	{
//	} 
//	~DeviceInfo()
//	{
//		if (next)
//			delete next;
//	}
//
//
//	SmartString friendlyName;
//	int			deviceId;	
//	DeviceInfo* next;
//};
///////////////////////////////////////////////////////
//video camera
//logitech revelotion
//160 * 120; 176 * 144; 352 * 288; 320 * 240; 640 * 480
//////////////////////////////////////////////////////
class DeviceInfo;
class  DSCAPTURE_API ARFrameGrabber  
{
public:
	ARFrameGrabber();
	virtual ~ARFrameGrabber();

	//initial and set properties
	int EnumDevices(DeviceInfo *head);
	bool Init(int deviceId, bool displayProperties = true,int iwidth = 320, int iheight = 240, int ichannels = 1, float fps = 30, bool IsPalVideo = false);
    int GetWidth();
    int GetHeight();
	//digital video get interface
	BYTE* GetByteBuffer();

	IplImage* GetImage();
	//pal video get Interface
	IplImage* GetImageOdd();
	IplImage* GetImageEven();
	//Get row data
	long  GetBufferSize() ;
	long* GetBuffer() ;
	void GrabFrame(long* size, long** pBuffer);
	void Destory();
protected:
	void *m_pInernal;
};

#endif // !defined(AFX_ARFRAMEGRABBER_H__C5553937_4BAB_4FEF_B4A6_1693AB0C99E3__INCLUDED_)
