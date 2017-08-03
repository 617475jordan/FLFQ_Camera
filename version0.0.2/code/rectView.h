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
	Scalar m_color = Scalar(0, 0, 255);	  //����ߵ���ɫ
	Scalar textColor = Scalar(0, 0, 255);  //���ֵ���ɫ
	int fontFace = 1;
	int textthickness = 1;				  //���ֵĺ��
	int textRaduis = 2;					  //���ְ뾶
	int lineType = 10;					  //�ߵ�����
	int raduis = 2;		  //��İ뾶
	int thickness = 2;	  //ֱ�ߺ��
	double totalArea;	  //��ͼ���������
	double singleArea;	  //��Ӱ���
	double fontScale = 0.6;				  //�����ʽ
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

