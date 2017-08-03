#pragma  once
#include <opencv_all.h>
#include "detect.h"
#include "rectView.h"
class detectPedestrian
{
public:
	detectPedestrian();
	~detectPedestrian();
	Mat Pedestrian(Mat img, int m_num);
	void initial();
	int someBodyNum();
	int noBodyNum();
private:
	vector<Rect> found, foundRect;
	double thresholdArea = 0.12;//判断人进入区域所占总面积，以避免误判
	int someBody, noBody;
};