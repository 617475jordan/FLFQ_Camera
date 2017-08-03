#include "initial.h"

initialDevice::initialDevice()
{
	deepKinectDevice = false;
	colorKinectDevice = false;
	m_AspDevice = true;
}

initialDevice::~initialDevice()
{
	deepKinectDevice = false;
	m_AspDevice = false;
}
void initialDevice::initialDeepKinectDevice()
{
	deepKinectDevice = true;
	colorKinectDevice = false;
	m_AspDevice = false;
}

void initialDevice::initialColorKinectDevice()
{
	deepKinectDevice = false;
	colorKinectDevice = true;
	m_AspDevice = false;
}
void initialDevice::initialAspDevice()
{
	deepKinectDevice = false;
	colorKinectDevice = false;
	m_AspDevice = true;
}

int initialDevice::initialResult()
{
	if (deepKinectDevice == true && m_AspDevice == false && colorKinectDevice == false)
	{
		return 1;
	}
	else if (deepKinectDevice == false && m_AspDevice == false && colorKinectDevice == true)
	{
		return 2;
	}
	else if (deepKinectDevice == false && m_AspDevice == true && colorKinectDevice == false)
	{
		return 3;
	}
	else
	{
		return 0;
	}
}