#pragma once
#undef FLFQEXP
#undef FLFQIMP
#define FLFQEXP   __declspec(dllexport)
#define FLFQIMP   __declspec(dllimport)

#ifndef XTRA
#ifndef BOOST_ALL_DYN_LINK
#define BOOST_ALL_DYN_LINK
#endif
#endif

#include <windows.h>
#include <stdio.h>
#include <string>
#include "opencv_all.h"
#include "CommonUtil.h"
#define imgW 640
#define imgH 480
class ICamera
{
public:
	ICamera()
	{
	}
	virtual ~ICamera()
	{
	}
     virtual bool Initialize(const char* cFileLoad) = 0;
    virtual bool GetCurrentImg(Mat& img, vector<cv::Point3f>& vecPoint) = 0;//////
	virtual IplImage* GetImage() = 0;
	virtual void Clear() = 0;
};

extern "C" FLFQEXP ICamera* CreateCamera();

extern "C" FLFQEXP void  FreeCamera(ICamera*& pcamera);

#define CreateCameraFName "CreateCamera"
#define FreeCameraFName "FreeCamera"

