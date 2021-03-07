#include<iostream>
#include<string>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2\imgproc\types_c.h>

using namespace cv;
using namespace std;


Mat src_gray;
Mat src_gray1;
Mat threshold_output;

int main()
{
	Mat src = imread("��ά��1.jpg");
	//namedWindow("ԭͼ", WINDOW_NORMAL);
    //imshow("ԭͼ", src);

	cvtColor(src, src_gray1, COLOR_BGR2GRAY);

	vector<vector<Point>> contours, twoContours;
	vector<Vec4i> hierarchy;

	//����Ӧ��ֵ��
	adaptiveThreshold(src_gray1, threshold_output, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 145, 15);
	//namedWindow("threshold_output", WINDOW_NORMAL);
	//imshow("threshold_output", threshold_output);

	//Ѱ������
	findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_TC89_KCOS, Point(0, 0));



	//////////////////////////////////////////��һ�ַ���////////////////////////////////////////
	//int ic = 0;//��ʼ�����������ڵĸ���
	//ͨ����ɫ��λ�����������������ص㣬ɸѡ��������λ��
	//int parentIdx = -1;
	//��ʼ����һ�δ�����������iֵ
	//for (int i = 0; i < contours.size(); i++)
	//{
	//	//��������ͼ
	//	//drawContours(drawingAllContours, contours, parentIdx, CV_RGB(255, 255, 255), 1, 8);
	//	if (hierarchy[i][2] != -1 && ic == 0)
	//	{
	//		parentIdx = i;
	//		ic++;
	//	}
	//	else if (hierarchy[i][2] != -1)
	//	{
	//		ic++;
	//	}
	//	else if (hierarchy[i][2] == -1)
	//	{
	//		ic = 0;
	//		parentIdx = -1;
	//	}

	//	//������������
	//	if (ic == 3)
	//	{
	//		//�����ҵ���������ɫ��λ��
	//		twoContours.push_back(contours[parentIdx]);
	//		//����������ɫ��λ�ǵ�����
	//		ic = 0;
	//		parentIdx = -1;
	//	}
	//}
	//////////////////////////////////////////////////////////////////////////////////////////





	/////////////////////////////////////ɸѡ��λ�ǵĵڶ��ַ���/////////////////////////////////////////////
	//����������������
	//vector<int>v1;//��ŷ���Ҫ����������
	for (int i = 0; i < contours.size(); i++)
	{
		if (hierarchy[i][2] != -1 && hierarchy[hierarchy[i][2]][2] != -1)
		{
			twoContours.push_back(contours[i]);//����һ��������һ���������㼯
			//v1.push_back(i);
		}
	}
	//////////////////////////////////////��������벻ͨ��ʲôԭ��/////////////////////////////////////////
	////��Ҫ�����һ��ɸѡ������ͬʱ��������������ͬһ��������
	//int m = 0, i = 0, j = 0;
	//vector<int> v0;//Ԥ��װ���ܷ���Ҫ���������������
	//for (; i < v1.size(); i++)
	//{
	//	for (; j < v1.size(); j++)
	//	{
	//		if (hierarchy[v1[i]][3] == hierarchy[v1[j]][3] && i != j)
	//		//��һ����ܲ��Եĵط���ԭ����hierarchy��װ��twocontours��ı���������ܲ�һ��
	//		{
	//			m++;
	//			v0.push_back(v1[j]);
	//		}
	//	}
	//
	//	if (m = 2)
	//	{
	//		v0.push_back(v1[i]);
	//	}
	//	else
	//	{
	//		v0.clear();
	//	}
	//	m = 0;
	//}
	//
	////������Ҫ�����������װ��һ���µ�������
	//vector<Point> twoContours1;
	//for (int i = 0; i < v0.size(); i++)
	//{
	//	for (vector<Point>::iterator it = twoContours[v0[i]].begin(); it != twoContours[v0[i]].end(); it++)
	//	{
	//		twoContours1.push_back(*it);
	//	}
	//}
	//////////////////////////////////////////////////////////////////////////////////////////////////////





	//drawContours(threshold_output, contours, -1, Scalar(0), 2);

	//��ʾɸѡ��������
	Mat lunkuo(src.size(), CV_8UC3);
	drawContours(lunkuo, twoContours, -1, Scalar(0), 2);
	namedWindow("ɸѡ��������", WINDOW_NORMAL);
	imshow("ɸѡ��������", lunkuo);



	///////////////////////////////////����ĵ�һ�ַ�ʽ////////////////////////////////////////
	//vector<Point2f> points;
	//Point2f fourPoint2f[4];
	//for (int i = 0; i < twoContours.size(); i++)
	//{
	//	RotatedRect rectPoint = minAreaRect(twoContours[i]);
	//	rectPoint.points(fourPoint2f);
	//	//������ÿһ��ѭ����ʱ�򶼻��fourPoint2f����װ�Ķ��������
	//	points.push_back(fourPoint2f[i]);//�����������ĵ�ȫ��װ��һ������������С��Χ���ο�����
	//	//����һ��ʼ�������ÿһ�����εĶ���ȫ��װ��һ����������ȥ��С�򣬵�����������ʽ������ת�������ܷŵ�ͬһ��������
	//}
	//Point2f fourPoint2f0[4];
	//RotatedRect rectPoint0 = minAreaRect(points);
	//rectPoint0.points(fourPoint2f0);
	//line(src, fourPoint2f0[0], fourPoint2f0[1], Scalar(0, 0, 255), 6);
	//line(src, fourPoint2f0[1], fourPoint2f0[2], Scalar(0, 0, 255), 6);
	//line(src, fourPoint2f0[2], fourPoint2f0[3], Scalar(0, 0, 255), 6);
	//line(src, fourPoint2f0[3], fourPoint2f0[0], Scalar(0, 0, 255), 6);
	//////////////////////////////////////////////////////////////////////////////////////////




	/////////////////////////////////////�ڶ��ַ�ʽ///////////////////////////////////
    vector<Point2f> points;
	Point2f fourPoint2f[4];
	vector<Point> v;//����һ��һά�Ĵ�����
	for (vector<vector<Point>>::iterator it = twoContours.begin(); it != twoContours.end(); it++)
	{
		for (vector<Point>::iterator vit = (*it).begin(); vit != (*it).end(); vit++)
		{
			v.push_back(*vit);
		}
	}
	RotatedRect rectPoint = minAreaRect(v);//twocontours�Ƕ�ά�ģ�������ΪminAreaRect�Ķ���
	rectPoint.points(fourPoint2f);
	for (int i = 0; i < 4; i++)
	{
		line(src, fourPoint2f[i % 4], fourPoint2f[(i + 1) % 4], Scalar(20, 21, 237), 3);
	}
	////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////һЩ����//////////////////////////////////////
	//RotatedRect rectPoint = minAreaRect(twoContours);
	//rectPoint.points(fourPoint2f);
	//line(src, fourPoint2f[0], fourPoint2f[1], Scalar(0, 0, 255), 6);
	//line(src, fourPoint2f[1], fourPoint2f[2], Scalar(0, 0, 255), 6);
	//line(src, fourPoint2f[2], fourPoint2f[3], Scalar(0, 0, 255), 6);
	//line(src, fourPoint2f[3], fourPoint2f[0], Scalar(0, 0, 255), 6);
	//
	//vector<Point2f> points0;
	//Point2f fourPoint2f[4];
	//for (int i = 0; i < twoContours.size(); i++)
	//{
	//	RotatedRect rectPoint = minAreaRect(twoContours[i]);
	//	points0.push_back(twoContours[i]);
	//	rectPoint.points(fourPoint2f);
	//	points.push_back(fourPoint2f[i]);
	//}
	//Point2f fourPoint2f0[4];
	//RotatedRect rectPoint0 = minAreaRect(points);
	//rectPoint0.points(fourPoint2f0);
	//line(src, fourPoint2f0[0], fourPoint2f0[1], Scalar(0, 0, 255), 6);
	//line(src, fourPoint2f0[1], fourPoint2f0[2], Scalar(0, 0, 255), 6);
	//line(src, fourPoint2f0[2], fourPoint2f0[3], Scalar(0, 0, 255), 6);
	//line(src, fourPoint2f0[3], fourPoint2f0[0], Scalar(0, 0, 255), 6);
	//////////////////////////////////////////////////////////////////////////////////


	namedWindow("Ч��ͼ", WINDOW_NORMAL);
	imshow("Ч��ͼ", src);


	waitKey(0);
	return 0;
}