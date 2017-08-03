#pragma once
#include <opencv_all.h>
#include "checkPoint.h"
#include "main.h"

class rectModel
{
public:
	rectModel();
	~rectModel();
	bool	onMouseLeftDown(float x, float y,float width, float height);
	bool    onMouseRightDown(float x, float y, float width, float height);
	bool	onMouseLeftUp(float x, float y, float width, float height);
	bool    onMouseRightUp(float x, float y, float width, float height);
	bool    judgeThreshold(double x, double y);
	bool    judgeRange(float x, float y, float width, float height);

public:
	vector<Point> deleteCoordinate(Point randPoint[1][1024], int m_num, int x, int y);
	vector<Point> moveCoordinate(Point randPoint[1][1024], int m_num, int x, int y, float width, float height);
	vector<Point> addCoordinate(Point randPoint[1][1024], int m_num, int x, int y, float width, float height);
	vector<Point> pointConvertVector(Point randPoint[1][1024], int m_num);
	int judgeXAndY(int a, int b);
	bool judgeLine(double x0, double x1, double y0, double y1);
protected:
	int 		getClickedPoint(Point randPoint[1][1024], int m_num, int x, int y);
protected:
	int m_thresold = 10;  //Êó±êµã»÷×ø±êÔÊÐíÎó²î·¶Î§
};