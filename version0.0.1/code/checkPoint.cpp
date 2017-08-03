#include"checkPoint.h"


Check::Check()
{
}
Check::~Check()
{
}
//检查点是否在线段附近
int Check::checkPoint(Point a, Point randPoint[1][1024], int m_num)
{
	int position =-1;
	if (m_num < 2)
	{
		return position;
	}
	for (int i = 0; i < m_num; i++)
	{
		double result = 1;	 //cos最大值
		if (i < m_num - 1)
		{
			result = compare(a.x - randPoint[0][i].x, a.y - randPoint[0][i].y,
				a.x - randPoint[0][i + 1].x, a.y - randPoint[0][i + 1].y);
			if (result < threshold)
			{
				position = i;
			}
		}
		else
		{
			result = compare(a.x - randPoint[0][i].x, a.y - randPoint[0][i].y,
				a.x - randPoint[0][0].x, a.y - randPoint[0][0].y);
			if (result < threshold)
			{
				position = i;
			}
		}
	}
	return position;
}
 //计算两点之间的距离
int Check::computeDistance(Point a, Point randPoint[1][1024], int m_num)
{
	int flag = 0;
	int position = -1;
	if (m_num < 3)
	{
		return position;
	}
	else
	{
		double minLen;
		minLen = distance(a.x - randPoint[0][0].x, a.x - randPoint[0][m_num - 1].x,
			a.y - randPoint[0][0].y, a.y - randPoint[0][m_num - 1].y);
		position = m_num - 1;
		for (int i = 0; i < m_num-1; i++)
		{
			double currentLen;
			currentLen = distance(a.x - randPoint[0][i].x, a.x - randPoint[0][i+1].x,
				a.y - randPoint[0][i].y, a.y - randPoint[0][i + 1].y);
			if (currentLen < minLen)
			{
				position = i;
				minLen = currentLen;
			}
		}
	}
	return position;
}

/***************求cos值***********************/
double Check::compare(double x0, double y0, double x1, double y1)
{
	double _sum = x0*x1 + y0*y1;
	double p_sum = abs(x0*x0 + y0*y0);
	double q_sum = abs(x1*x1 + y1*y1);
	p_sum = sqrt(p_sum);
	q_sum = sqrt(q_sum);
	double sum = _sum / (p_sum*q_sum);
	return sum;
}
/***************求距离**********************/
double Check::distance(double x0, double x1, double y0, double y1)
{
	double m_sum, n_sum;
	m_sum = x0*x0 + y0*y0;
	n_sum = x1*x1 + y1*y1;
	double sum = sqrt(m_sum+n_sum);
	return sum;
}