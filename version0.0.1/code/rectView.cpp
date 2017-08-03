#include "rectView.h"

rectView::rectView()
{
	totalArea = -1;
	singleArea = -1;
	someBody = 0;
	noBody = 0;
}
rectView::~rectView()
{
	totalArea = -1;
	singleArea = -1;
	someBody = 0;
	noBody = 0;
}

/*************绘制曲线*************/
/*
src::图片
randPoint坐标
m_num 坐标个数
flag 是否需要进行填充 1表示需要

*/
Mat  rectView::drawPolygon(Mat src, Point randPoint[1][1024], int m_num, int flag)
{
	Detect detect;
	for (int i = 0; i < m_num; i++)
	{
		if (i < m_num - 1)
		{
			line(src, randPoint[0][i], randPoint[0][i + 1], m_color, thickness);
		}
		else
		{
			line(src, randPoint[0][i], randPoint[0][0], m_color, thickness);
		}
	}
	if (flag == 1)
	{
		const Point* ppt[1] = { randPoint[0] };
		int npt[] = { m_num };
		/*智能绘制多边形**/
		//polylines(src, ppt, npt, 1, 1, m_color, 2, 8, 0); 				//	polylines()

		fillPoly(src, ppt, npt, 1, Scalar(255, 255, 255));
		totalArea = detect.ComputeArea(src,src.cols,src.rows);
	}

	for (int i = 0; i < m_num; i++)
	{
		circle(src, randPoint[0][i], raduis, m_color, thickness);
	}

	return src;
}

Mat rectView::drawKinectImage(Mat src, int m_num, vector<Point> coordinate)
{
	Point coordinatePoint[1][1024];
	m_num = coordinate.size();
	for (int i = 0; i < m_num; i++)
	{
		coordinatePoint[0][i] = coordinate[i];
	}
	Mat m_src, n_src;
	src.copyTo(m_src);
	src.copyTo(n_src);
	m_src.setTo(0);

	m_src = drawPolygon(m_src, coordinatePoint, m_num, 1);
	
	
	Mat bitM,tmp;
	src.copyTo(bitM);
	bitM.setTo(0);
	src.copyTo(tmp);
	bitwise_not(src, bitM);
	bitM.copyTo(src);
	
	bitwise_and(m_src, bitM, bitM);
	Detect detect;
	singleArea = detect.ComputeArea(bitM,bitM.cols,bitM.rows);

	bitwise_not(bitM, bitM);
	bitwise_not(src, src);
	bitM = drawPolygon(bitM, coordinatePoint, m_num, 0);//绘制线段
	src = drawPolygon(src, coordinatePoint, m_num, 0);//绘制线段
	if (totalArea <= 0&&m_num<4)
	{
	//	n_src=help(src, 1);
		n_src = src;
	}
	else if (totalArea <= 0 && m_num >= 4)
	{
	//	n_src = help(bitM, 3);
		n_src = bitM;
		noBody++;
	}
	else  if (totalArea )
	{
		if (singleArea >= kinectThreshold*totalArea)
		{
			someBody++;
		//	n_src=help(bitM, 2);
		}
		else
		{
			noBody++;
		//	n_src=help(bitM, 3);
		}
		n_src = bitM;
	}
	return n_src;
}

Mat rectView::drawAspImage(Mat src, int m_num, vector<Point> coordinate, bool flag)
{
	Mat n_src, m_src;
	Point coordinatePoint[1][1024];
	src.copyTo(n_src);
	src.copyTo(m_src);
//	m_num = coordinate.size();

	for (int i = 0; i < m_num; i++)
	{
		coordinatePoint[0][i] = coordinate[i];
	}
	if (flag == true) //如果大于等于四个点既可以围成封闭曲线
	{
		n_src = drawPolygon(n_src, coordinatePoint, m_num, 1);
		for (int k = 0; k < n_src.rows; k++)
		{
			for (int j = 0; j < n_src.cols; j++)
			{
				if (n_src.at<Vec3b>(k, j)[0] == 255 && n_src.at<Vec3b>(k, j)[1] == 255 && n_src.at<Vec3b>(k, j)[2] == 255)
				{
					src.at<Vec3b>(k, j) = src.at<Vec3b>(k, j);

				}
				else
				{
					src.at<Vec3b>(k, j) = Vec3b(255, 255, 255);
				}
			}
		}
		src = drawPolygon(src, coordinatePoint, m_num, 0);
		return   src;
	}
	else
	{
		src = drawPolygon(src, coordinatePoint, m_num, 0);
		return src;
	}

}
void rectView::getTime()
{
	time_t t = time(0);
	strftime(currentTime, sizeof(currentTime), "%Y/%m/%d %X %A ", localtime(&t));
	
}
Mat rectView::help(Mat src, int flag)
{
	getTime();
	switch (flag)
	{
	case 1:
		putText(src, initialName, textPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, coordinateHint, clearPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, goOut, goOutPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, currentTime, currentTimePoint, fontFace, fontScale, textColor, textthickness, lineType);
		break;
	case 2:
		putText(src, personIn, textPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, coordinateHint, clearPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, goOut, goOutPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, currentTime, currentTimePoint, fontFace, fontScale, textColor, textthickness, lineType);
		break;
	case 3:
		putText(src, personOut, textPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, coordinateHint, clearPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, goOut, goOutPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, currentTime, currentTimePoint, fontFace, fontScale, textColor, textthickness, lineType);
	case 4:
		putText(src, coordinateHint, clearPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, goOut, goOutPoint, fontFace, fontScale, textColor, textthickness, lineType);
		putText(src, currentTime, currentTimePoint, fontFace, fontScale, textColor, textthickness, lineType);
		break;
	default:
		break;
	}
	return src;
}

int rectView::noBodyNum()
{
	return noBody;
}
int rectView::someBodyNum()
{
	return someBody;
}
void rectView::initial()
{
	someBody = 0;
	noBody = 0;
}