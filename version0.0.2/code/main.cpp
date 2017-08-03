#include <opencv_all.h>
#include "DsCapture.h"
#include "ICamera.h"
#include "rectModel.h"
#include "rectView.h"
#include "initial.h"
#include "myKinect.h"
#include "detectPedestrian.h"
#include "PM_Hub.h"
#include "deleteData.h"
#include "remapImage.h"
#ifdef _DEBUG
#pragma comment(lib, "CommuDll30D.lib")
#pragma comment(lib, "CommonUtil31D.lib")
#pragma comment(lib, "PlayerManager31D.lib")
#pragma comment(lib, "GlobalSyncTimeManager31D.lib")
#else

#pragma comment(lib, "CommuDll30.lib")
#pragma comment(lib, "CommonUtil31.lib")
#pragma comment(lib, "PlayerManager31.lib")
#pragma comment(lib, "GlobalSyncTimeManager31.lib")
#endif

IplImage* pImage;
Mat src;//ԭʼͼ�� 
Mat m_src;

int m_num;    //�������
int failNum;   //Kinect����ʧ�ܴ���
int width, height;       //��Ƶ���
int  initialDeviceflag;  //�豸��־��
int seeYouFlag;       //�ټ�video��־λ
int playInitial;      //���ű��
int personNum;              //��ǰ��������Ƶ�е�Ƶ��
int aspPersonNumThreshold;//����֡������ֵ
int kinectPersonNumThreshold;
int clientID,RectWidth,RectHeight;

/// <summary>	�ڹ涨֡���ڣ����ֵ�ռ��. </summary>
double inThresholdReference;
double outThresholdReference;//�ڹ涨֡���ڣ���ʧ��ռ��
Point randPoint[1][1024];
vector<Point> coordinate;

bool leftButtonDownFlag; //�����������Ƶ��ͣ���ŵı�־λ  
bool rightButtonDownFlag; //�Ҽ���������Ƶ��ͣ���ŵı�־λ
bool noBodyFlag, someBodyFlag;//�����Ƿ����˱�־λ
bool welcomeFlag;     //��ӭvideo�ı�־λ

CQueue *queue1, *queue2;
PM_Hub * g_PM_Hub;

string welcomeStr;      //��ӭvideoĿ¼
string seeYouStr;       //�ټ�videoĿ¼
string windowName = "show";

void playMedia(string str, int flag); //������Ƶ
void transferToPC();                  //�����ݴ��䵽��һ̨PC
void seeYouPlayMedia();
void readData();                      //��ȡ�����ڱ��ص�����
void initial();                       //��ʼ��
void keyOperation();                  //���̲���
void aspCapture();
void deepkinectCapture();
void colorkinectCapture();
void onMouse(int event, int x, int y, int flags, void *ustc);//���ص����� 
Mat drawImage(Mat src, double someBody, double noBody, double inPerosonNumReference, double outPerosonNumReference);
/******************
detectPedestrian����㷨��release�´����Ҫ160ms
*******************/

int main()
{
	initial();
	switch (initialDeviceflag)
	{
	case 1:
		deepkinectCapture(); // ����Kinect����ͷ��ʹ�����ͼ
		break;
	case 2:
		colorkinectCapture();	
		break;
	case 3:
		aspCapture();//����asp����ͷ
		break;
	default:
		break;
	}
}

void initial()
{
	readData();
	src.release();
	m_src.release();
	initialDevice initialDevice;
	initialDeviceflag = initialDevice.initialResult();
	initialDeviceflag = 3;
	seeYouFlag = 0;
	m_num = 0;
	failNum = 0;
	playInitial = 0;
	welcomeFlag = false;
	coordinate.clear();
}

void deepkinectCapture()
{
	CBodyBasics myKinect;
	rectModel rectModel;
	rectView rectView;
	remapImage remapImage;
	//��������ʼ��
	/// <summary>	The hr. </summary>
	HRESULT hr = myKinect.deepInitializeDefaultSensor();

	while (FAILED(hr))
	{
		cout << "����ʧ�ܣ����ڳ���,��ǰʧ�ܴ���Ϊ:" << failNum << endl;
		hr = myKinect.deepInitializeDefaultSensor();
		failNum++;
	}
	if (SUCCEEDED(hr))
	{
		namedWindow(windowName);
		setMouseCallback(windowName, onMouse);
		while (1)
		{
			
			src = myKinect.deepUpdate();
			if (src.empty())
			{
				src = myKinect.deepUpdate();
			}

			else
			{
				personNum++;
				src = remapImage.Photo_Remap(src);
				width = src.cols;
				height = src.rows;
				src = rectView.drawKinectImage(src, m_num, coordinate);
				if (personNum == kinectPersonNumThreshold)
				{
					personNum = 0;
					rectView.initial();
				}
				src = drawImage(src, rectView.someBodyNum(),
					rectView.noBodyNum(), kinectPersonNumThreshold*inThresholdReference,
					kinectPersonNumThreshold*outThresholdReference);
				imshow(windowName, src);
				waitKey(25);//ˢ��Ƶ��̫�죿50msһ�㶼��1ms

				transferToPC();
			}
			
			keyOperation();
		}
	}
	else
	{
		cout << "kinect initialization failed!" << endl;
	}

}
void colorkinectCapture()
{
		rectView rectView;
		detectPedestrian detectPedestrian;
		remapImage remapImage;
		CBodyBasics myKinect;
		HRESULT hr = myKinect.colorInitializeDefaultSensor();
		while (FAILED(hr))
		{
			cout << "����ʧ�ܣ����ڳ���,��ǰʧ�ܴ���Ϊ:" << failNum << endl;
			hr = myKinect.colorInitializeDefaultSensor();
			failNum++;
		}
		if (SUCCEEDED(hr))
		{
			namedWindow(windowName);
			setMouseCallback(windowName, onMouse);
			while (1)
			{
				m_src = myKinect.colorUpdate();
				if (m_src.empty())
				{
					m_src = myKinect.colorUpdate();
				}
				else
				{
					personNum++;
					width = m_src.cols;
					height = m_src.rows;
					m_src = remapImage.Photo_Remap(m_src);
					if (m_num >= 4)
					{
						src = rectView.drawAspImage(m_src, m_num, coordinate, true);
					}
					else
					{
						src = rectView.drawAspImage(m_src, m_num, coordinate, false);
					}
					src = detectPedestrian.Pedestrian(src, m_num);
					if (personNum == kinectPersonNumThreshold)
					{
						personNum = 0;
						detectPedestrian.initial();
					}
					
					src = drawImage(src, detectPedestrian.someBodyNum(),
						detectPedestrian.noBodyNum(), kinectPersonNumThreshold*inThresholdReference, 
						kinectPersonNumThreshold*outThresholdReference);

					imshow(windowName, src);
					waitKey(1);

					transferToPC();
				}
				keyOperation();
			}
		}
}
void aspCapture()
{
	CDsCapture dsCapture;
	rectModel rectModel;
	rectView rectView;
	detectPedestrian detectPedestrian;
	
	dsCapture.Initialize(0);
	namedWindow(windowName);
	setMouseCallback(windowName, onMouse);

	while (1)
	{
		double t = clock();
		pImage = dsCapture.GetImage();
		if (pImage)
		{
			personNum++;
			src = pImage;
			width = src.cols;
			height = src.rows;
			flip(src, src, -1);
			cvtColor(src, m_src, CV_GRAY2RGB);
			//������˹����ͼ����ǿЧ��
			Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
			filter2D(m_src, m_src, CV_8UC3, kernel);
			
			if (m_num >= 4)
			{
				src = rectView.drawAspImage(m_src, m_num, coordinate, true);
			}
			else
			{
				src = rectView.drawAspImage(m_src, m_num, coordinate, false);
			}
			
			src = detectPedestrian.Pedestrian(src, m_num);
			if (personNum == aspPersonNumThreshold)
			{
				personNum = 0;
				detectPedestrian.initial();
			}
			
			src = drawImage(src, detectPedestrian.someBodyNum(),
				detectPedestrian.noBodyNum(), aspPersonNumThreshold*inThresholdReference,
				aspPersonNumThreshold*outThresholdReference);
			
			imshow(windowName, src);
			waitKey(1);

			transferToPC();
		}
		keyOperation();
	}
}
void transferToPC()
{
	if (playInitial == 1)
	{
		playMedia(welcomeStr, 1);
		playInitial++;
		welcomeFlag = true;
	}
	if (someBodyFlag == true && playInitial >= 1 && welcomeFlag == true)
	{
		int id = queue1->GetQueueID();
		bool b = g_PM_Hub->GetItemEndFeedback(id, welcomeStr);
		if (b)
		{
			cout << "Film is over " << endl;
			queue1->EraseQueue(1);
			g_PM_Hub->SendLoaded();//����ʹ��
			welcomeFlag = false;
			seeYouFlag++;;
		}
		Sleep(10);
	}
	else if (noBodyFlag == true && playInitial >= 1)
	{
		welcomeFlag = false;
		queue1->EraseQueue(1);
		g_PM_Hub->SendLoaded();//����ʹ��
		seeYouFlag++;
	}
	if (seeYouFlag == 1)
	{
		deleteData deleteData;
		deleteData.DeletePM();
		deleteData.DeleteQueue();
		g_PM_Hub = deleteData.pm_Hub();
		playMedia(seeYouStr, 2);
	}
	if (seeYouFlag >= 1)
	{
		seeYouPlayMedia();
	}
}
Mat drawImage(Mat src, double someBody, double noBody, double inPerosonNumReference, double outPerosonNumReference)
{
	rectView rectView;
	detectPedestrian detectPedestrian;
	if (m_num >= 4)
	{
		if (someBody >= inPerosonNumReference/*&&seeYouFlag==true*/)
		{
			someBodyFlag = true;
			noBodyFlag = false;
			src = rectView.help(src, 2);
			detectPedestrian.initial();
			playInitial++;
		}
		else if (noBody >= outPerosonNumReference/*&&seeYouFlag == true*/)
		{
			noBodyFlag = true;
			someBodyFlag = false;
			src = rectView.help(src, 3);
			detectPedestrian.initial();
		}
		else
		{
			noBodyFlag = false;
			someBodyFlag = false;
			src = rectView.help(src, 4);
		}
	}

	else
	{
		noBodyFlag = false;
		someBodyFlag = false;
		src = rectView.help(src, 1);
	}
	return src;
}
void onMouse(int event, int x, int y, int flags, void *ustc)
{
	rectModel rectModel;
	/***********���������꣬�������*****************/
	if (event == CV_EVENT_LBUTTONDOWN&&leftButtonDownFlag == false)
	{
		leftButtonDownFlag = rectModel.onMouseLeftDown(x, y, width, height);
	}
	/***********���������꣬�ƶ����*****************/
	if (event == CV_EVENT_MOUSEMOVE &&leftButtonDownFlag)
	{
		coordinate = rectModel.moveCoordinate(randPoint, m_num, x, y, width, height);
	}
	/***********���������̧꣬�����*****************/
	if (event == CV_EVENT_LBUTTONUP&&leftButtonDownFlag)
	{
		leftButtonDownFlag = rectModel.onMouseLeftUp(x, y, width, height);
		coordinate = rectModel.addCoordinate(randPoint, m_num, x, y, width, height);
	}
	/*********�һ�ɾ������,�����Ҽ�**************/
	if (event == CV_EVENT_RBUTTONDOWN&&rightButtonDownFlag == false)
	{
		rightButtonDownFlag = rectModel.onMouseRightDown(x, y, width, height);
	}
	/*********�һ�ɾ������,̧���Ҽ�**************/
	if (event == CV_EVENT_RBUTTONUP&&rightButtonDownFlag)
	{
		rightButtonDownFlag = rectModel.onMouseRightUp(x, y, width, height);
		coordinate = rectModel.deleteCoordinate(randPoint, m_num, x, y);
	}
	m_num = coordinate.size();
	for (int i = 0; i < m_num; i++)
	{
		randPoint[0][i] = coordinate[i];
	}
}

void keyOperation()
{
	char charkey;
	charkey = waitKey(10);
	deleteData deleteData;
	if (charkey == 'o' || charkey == 'O')
	{
		string sz = "�˳�";
		MessageBoxA(NULL, sz.c_str(), "��ʾ", IDOK);
		deleteData.DeletePM();
		deleteData.DeleteQueue();
		g_PM_Hub = deleteData.pm_Hub();
		exit(-1);
	}
	if (charkey == 'C' || charkey == 'c')
	{
		string sz = "�˳�";
		MessageBoxA(NULL, sz.c_str(), "��ʼ������", IDOK);
		initial();
	}
}


void playMedia(string str, int flag)
{
	deleteData deleteData;
	g_PM_Hub = new PM_Hub("testPlayer");
	g_PM_Hub->SetUpClient(clientID, 0, 0, RectWidth, RectHeight, 1);
	switch (flag)
	{
	case 1:
		queue1 = new CQueue(g_PM_Hub);
		queue1->NewQueue(-1, 1, clientID, 0, 1);
		queue1->AppendQueue(str, "cmp", 30, 0, 0, 1, 1);
		queue1->SetCoords(RectWidth/2, RectHeight / 2, 1, RectWidth, RectHeight, 1);
		queue1->SetStartTime(-1, 1);
		g_PM_Hub->SendLoaded();
		deleteData.transfer(queue1, g_PM_Hub);	
		break;

	case 2:
		queue2 = new CQueue(g_PM_Hub);
		queue2->NewQueue(-1, 1, clientID, 0, 1);
		queue2->AppendQueue(str, "cmp", 30, 0, 0, 1, 1);
		queue2->SetCoords(RectWidth / 2, RectHeight / 2, 1, RectWidth, RectHeight, 1);
		queue2->SetStartTime(-1, 1);
		g_PM_Hub->SendLoaded();
		deleteData.transfer(queue2, g_PM_Hub);
		break;
	default:
		break;
	}

}

void seeYouPlayMedia()
{
	int id = queue2->GetQueueID();
	bool b = false;
	b = g_PM_Hub->GetItemEndFeedback(id, seeYouStr);
	seeYouFlag++;
	if (b)
	{
		cout << "All is over " << endl;
		cout << "Thank You for Watching" << endl;
		cout << "See You Again" << endl;
		queue2->EraseQueue(1);
		g_PM_Hub->SendLoaded();//����ʹ��
		playInitial = 0;
		seeYouFlag = 0;
		deleteData deleteData;
		deleteData.DeletePM();
		deleteData.DeleteQueue();
		g_PM_Hub = deleteData.pm_Hub();
	}
	Sleep(10);
}

void readData()
{
	FileStorage file;
	file.open("data.xml", FileStorage::READ);
	if (!file.isOpened())
	{
		cout << "δ��������" << endl;
		string sz = "�˳�";
		MessageBoxA(NULL, sz.c_str(), "��ʼ������", IDOK);
		exit(-1);
	}
	else
	{
		file["aspPersonNumThreshold"] >> aspPersonNumThreshold;
		file["kinectPersonNumThreshold"] >> kinectPersonNumThreshold;
		file["inThresholdReference"] >> inThresholdReference;
		file["outThresholdReference"] >> outThresholdReference;
		file["welcomeStr"] >> welcomeStr;
		file["seeYouStr"] >> seeYouStr;
		file["clientID"] >> clientID;
		file["RectWidth"] >> RectWidth;
		file["RectHeight"] >> RectHeight;
		cout << "aspPersonNumThreshold:" << aspPersonNumThreshold << endl;;
		cout << "kinectPersonNumThreshold:" << kinectPersonNumThreshold << endl;
		cout << "inThresholdReference:" << inThresholdReference << endl;
		cout << "outThresholdReference:" << outThresholdReference << endl;
		cout << "welcomeStr:" << welcomeStr << endl;
		cout << "seeYouStr:" << seeYouStr << endl;
		cout << "clientID:" << clientID << endl;
		cout << "RectWidth:" << RectWidth << endl;
		cout << "RectHeight:" << RectHeight << endl;
		
	}
}