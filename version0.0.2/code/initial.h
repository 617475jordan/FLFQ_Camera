#pragma once 
#include <opencv_all.h>
class initialDevice
{
public:
	initialDevice();
	~initialDevice();
	void initialColorKinectDevice();
	void initialDeepKinectDevice();
	void initialAspDevice();
	int initialResult();
private:
	bool deepKinectDevice;
	bool colorKinectDevice;
	bool m_AspDevice;
};