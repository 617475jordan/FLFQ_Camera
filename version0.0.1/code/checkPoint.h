#pragma once

#include "detect.h"
#include <opencv_all.h>
#include "main.h"
class Check
{
public:
	Check();
	~Check();
	//检查点是否在线段附近
	int checkPoint(Point a, Point randPoint[1][1024], int m_num);
	//计算两点之间的距离
	int computeDistance(Point a, Point randPoint[1][1024], int m_num);
	double compare(double x0, double y0, double x1, double y1);
	double distance(double x0, double x1, double y0, double y1);
	double coordinateDistance[1][2];
	double coordinateFlag[1][2];
private:
	double threshold = -0.85;  //cos阈值
};