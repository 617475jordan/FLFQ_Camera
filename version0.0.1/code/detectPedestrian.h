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
	double thresholdArea = 0.12;//�ж��˽���������ռ��������Ա�������
	int someBody, noBody;
};