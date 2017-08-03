#pragma once
#include <opencv_all.h>

class Detect
{
public:
	Mat ShowImage(Mat src, Point originalPoint, int width, int height);
	Detect();
	~Detect();
	double ComputeArea(Mat m_src,double width, double height);

private:
	Mat elemet = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	Mat tmp;
	/***********二值化阈值************/
	static const int nY20_thresh = 50;
	Rect rect;
	Mat m_roi,n_roi;
	double k = 0.1;
};
