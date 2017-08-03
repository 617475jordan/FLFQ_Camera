#ifndef   _MAIN_HEAD_H
#define   _MAIN_HEAD_H

#if _DEBUG 
#pragma comment(lib, "..\\lib\\detectd.lib")
#pragma comment(lib, "..\\lib\\DShowCaptureD.lib")
//#pragma comment(lib, "..\\lib\\myKinectd.lib")


#else
#pragma comment(lib, "..\\lib\\detect.lib")
#pragma comment(lib, "..\\lib\\DShowCapture.lib")
//#pragma comment(lib, "..\\lib\\myKinect.lib")

#endif
#endif