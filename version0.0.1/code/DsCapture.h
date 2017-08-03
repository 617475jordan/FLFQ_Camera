#pragma once
#include <Windows.h>
#include <tchar.h>
#include "DsCaptureImpExp.h"
#include "ICamera.h"
//// 此类是从 DsCapture.dll 导出的
//class DSCAPTURE_API CDsCapture {
//public:
//	CDsCapture(void);
//	// TODO: 在此添加您的方法。
//};
//
//extern DSCAPTURE_API int nDsCapture;
//
//DSCAPTURE_API int fnDsCapture(void);

class ARFrameGrabber;

class DSCAPTURE_API CDsCapture: public ICamera
{
public:
  CDsCapture()
  {
  }
  virtual ~CDsCapture()
  {
  }
  virtual bool Initialize(const char* cFileLoad);
  virtual bool GetCurrentImg(Mat& img, vector<cv::Point3f>& vecPoint);
  virtual IplImage* GetImage();
  virtual void Clear();

private:
  ARFrameGrabber* m_pgrabber;
};