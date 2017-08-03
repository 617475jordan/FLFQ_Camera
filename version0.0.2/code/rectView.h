#pragma once
#include <opencv_all.h>
#include "detect.h"
#include "main.h"
#include <ctime>

class rectView
{
public:
	rectView();
	~rectView();
	Mat  drawKinectImage(Mat src, int m_num, vector<Point> coordinate);
	Mat  drawAspImage(Mat src, int m_num, vector<Point> coordinate, bool flag);
	Mat  drawPolygon(Mat src, Point randPoint[1][1024], int m_num, int flag);
	Mat  help(Mat src, int flag);
	void getTime();
	int someBodyNum();
	int noBodyNum();
	void initial();
private:
	Scalar m_color = Scalar(0, 0, 255);	  //点和线的颜色
	Scalar textColor = Scalar(0, 0, 255);  //文字的颜色
	int fontFace = 1;
	int textthickness = 1;				  //文字的厚度
	int textRaduis = 2;					  //文字半径
	int lineType = 10;					  //线的类型
	int raduis = 2;		  //点的半径
	int thickness = 2;	  //直线厚度
	double totalArea;	  //截图区域总面积
	double singleArea;	  //人影面积
	double fontScale = 0.6;				  //字体格式
	double kinectThreshold = 0.1;
	Point textPoint = Point(10, 10);
	Point clearPoint = Point(10, 20);
	Point goOutPoint = Point(10, 30);
	Point currentTimePoint = Point(10, 40);
	Mat elemet = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	static const int nY20_thresh = 50;
	char currentTime[64];

	int someBody;
	int noBody;
	
private:
#define initialName "Initial"
#define coordinateHint "Choose c or C to clear all "
#define personOut 	  "No Person"
#define personIn	  "People in"
#define goOut          "Choose o or O to exit"
};

