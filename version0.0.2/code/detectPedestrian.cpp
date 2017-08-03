#include "detectPedestrian.h"

detectPedestrian::detectPedestrian()
{
	foundRect.clear();
	foundRect.clear();
	someBody = 0;
	someBody = 0;

}
detectPedestrian::~detectPedestrian()
{
	foundRect.clear();
	foundRect.clear();
	someBody = 0;
	someBody = 0;
}

Mat detectPedestrian::Pedestrian(Mat img, int m_num)
{
	foundRect.clear();
	foundRect.clear();
	HOGDescriptor defaultHog;
	defaultHog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	//进行检测
	defaultHog.detectMultiScale(img, found);
	int maxflag = -1;
	int maxarea;
	if (found.size() >= 1)
	{
		maxflag = 0;
		maxarea = found[0].width*found[0].height;
	}
	//遍历found寻找没有被嵌套的长方形
	for (int i = 1; i < found.size(); i++)
	{
		Rect r = found[i];

		for (int j = 0; j < found.size(); j++)
		{
			//如果时嵌套的就推出循环
			if (j != i && (r & found[j]) == r)
				break;
		}
		int area = r.width*r.height;
		if (area>maxarea)
		{
			maxarea = area;
			maxflag = i;
		}
	}
	rectView rectView;
	double srcArea = img.cols*img.rows;
	srcArea = thresholdArea*srcArea;
	if (maxflag >= 0 && m_num >= 4)
	{
		double currentArea = found[maxflag].height*found[maxflag].width;
		if (currentArea >= srcArea)
		{
			foundRect.push_back(found[maxflag]);
			//画长方形，圈出行人
			rectangle(img, foundRect[0].tl(), foundRect[0].br(), Scalar(0, 0, 255), 3);
			//	img = rectView.help(img, 2);
			someBody++;
		}
		else
		{
			//	img = rectView.help(img, 3);
			noBody++;
		}

	}
	else if (maxflag<0 && m_num >= 4)
	{
		//	img = rectView.help(img, 3);
		noBody++;
	}
	else
	{
		noBody++;
		img = rectView.help(img, 1);
	}
	return img;
}
void detectPedestrian::initial()
{
	someBody = 0;
	noBody = 0;
}
int detectPedestrian::someBodyNum()
{
	return someBody;
}
int detectPedestrian::noBodyNum()
{
	return noBody;
}
