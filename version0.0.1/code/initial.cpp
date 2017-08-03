#include "initial.h"

initialDevice::initialDevice()
{
	m_KinectDevice = false;
	n_KinectDevice = false;
	m_AspDevice = true;
}

initialDevice::~initialDevice()
{
	m_KinectDevice = false;
	m_AspDevice = false;
}
void initialDevice::initialDeepKinectDevice()
{
	m_KinectDevice = true;
	n_KinectDevice = false;
	m_AspDevice = false;
}

void initialDevice::initialColorKinectDevice()
{
	m_KinectDevice = false;
	n_KinectDevice = true;
	m_AspDevice = false;
}
void initialDevice::initialAspDevice()
{
	m_KinectDevice = false;
	n_KinectDevice = false;
	m_AspDevice = true;
}

int initialDevice::initialResult()
{
	if (m_KinectDevice == true && m_AspDevice == false&&n_KinectDevice==false)
	{
		return 1;
	}
	else if (m_KinectDevice == false && m_AspDevice == true&&n_KinectDevice == false)
	{
		return 2;
	}
	else if (m_KinectDevice == false && m_AspDevice == false && n_KinectDevice == true)
	{
		return 3;
	}
	else
	{
		return 0;
	}
}