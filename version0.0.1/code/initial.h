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
	bool m_KinectDevice;
	bool n_KinectDevice;
	bool m_AspDevice;
};