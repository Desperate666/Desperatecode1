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
	Mat src = imread("二维码1.jpg");
	//namedWindow("原图", WINDOW_NORMAL);
    //imshow("原图", src);

	cvtColor(src, src_gray1, COLOR_BGR2GRAY);

	vector<vector<Point>> contours, twoContours;
	vector<Vec4i> hierarchy;

	//自适应二值化
	adaptiveThreshold(src_gray1, threshold_output, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 145, 15);
	//namedWindow("threshold_output", WINDOW_NORMAL);
	//imshow("threshold_output", threshold_output);

	//寻找轮廓
	findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_TC89_KCOS, Point(0, 0));



	//////////////////////////////////////////第一种方案////////////////////////////////////////
	//int ic = 0;//初始化子轮廓存在的个数
	//通过黑色定位角有两个子轮廓的特点，筛选出三个定位角
	//int parentIdx = -1;
	//初始化第一次存在子轮廓的i值
	//for (int i = 0; i < contours.size(); i++)
	//{
	//	//画出轮廓图
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

	//	//有三个子轮廓
	//	if (ic == 3)
	//	{
	//		//保存找到的三个黑色定位角
	//		twoContours.push_back(contours[parentIdx]);
	//		//画出三个黑色定位角的轮廓
	//		ic = 0;
	//		parentIdx = -1;
	//	}
	//}
	//////////////////////////////////////////////////////////////////////////////////////////





	/////////////////////////////////////筛选定位角的第二种方法/////////////////////////////////////////////
	//有两个以上子轮廓
	//vector<int>v1;//存放符合要求的索引编号
	for (int i = 0; i < contours.size(); i++)
	{
		if (hierarchy[i][2] != -1 && hierarchy[hierarchy[i][2]][2] != -1)
		{
			twoContours.push_back(contours[i]);//可以一次性输入一整个轮廓点集
			//v1.push_back(i);
		}
	}
	//////////////////////////////////////这里根本想不通是什么原因/////////////////////////////////////////
	////需要再添加一个筛选条件：同时有三个轮廓共用同一个父轮廓
	//int m = 0, i = 0, j = 0;
	//vector<int> v0;//预存装可能符合要求轮廓的索引编号
	//for (; i < v1.size(); i++)
	//{
	//	for (; j < v1.size(); j++)
	//	{
	//		if (hierarchy[v1[i]][3] == hierarchy[v1[j]][3] && i != j)
	//		//有一点可能不对的地方：原来的hierarchy和装到twocontours后的编号索引可能不一样
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
	////将符合要求的轮廓重新装到一个新的容器里
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

	//显示筛选出的轮廓
	Mat lunkuo(src.size(), CV_8UC3);
	drawContours(lunkuo, twoContours, -1, Scalar(0), 2);
	namedWindow("筛选出的轮廓", WINDOW_NORMAL);
	imshow("筛选出的轮廓", lunkuo);



	///////////////////////////////////画框的第一种方式////////////////////////////////////////
	//vector<Point2f> points;
	//Point2f fourPoint2f[4];
	//for (int i = 0; i < twoContours.size(); i++)
	//{
	//	RotatedRect rectPoint = minAreaRect(twoContours[i]);
	//	rectPoint.points(fourPoint2f);
	//	//这里是每一次循环的时候都会把fourPoint2f里面装的东西清空吗？
	//	points.push_back(fourPoint2f[i]);//把所有轮廓的点全部装到一个容器里用最小包围矩形框起来
	//	//这里一开始就是想把每一个矩形的顶点全部装到一个容器里再去最小框，但是这里点的形式好像不能转化，不能放到同一个容器里
	//}
	//Point2f fourPoint2f0[4];
	//RotatedRect rectPoint0 = minAreaRect(points);
	//rectPoint0.points(fourPoint2f0);
	//line(src, fourPoint2f0[0], fourPoint2f0[1], Scalar(0, 0, 255), 6);
	//line(src, fourPoint2f0[1], fourPoint2f0[2], Scalar(0, 0, 255), 6);
	//line(src, fourPoint2f0[2], fourPoint2f0[3], Scalar(0, 0, 255), 6);
	//line(src, fourPoint2f0[3], fourPoint2f0[0], Scalar(0, 0, 255), 6);
	//////////////////////////////////////////////////////////////////////////////////////////




	/////////////////////////////////////第二种方式///////////////////////////////////
    vector<Point2f> points;
	Point2f fourPoint2f[4];
	vector<Point> v;//构建一个一维的大容器
	for (vector<vector<Point>>::iterator it = twoContours.begin(); it != twoContours.end(); it++)
	{
		for (vector<Point>::iterator vit = (*it).begin(); vit != (*it).end(); vit++)
		{
			v.push_back(*vit);
		}
	}
	RotatedRect rectPoint = minAreaRect(v);//twocontours是二维的，不能作为minAreaRect的对象
	rectPoint.points(fourPoint2f);
	for (int i = 0; i < 4; i++)
	{
		line(src, fourPoint2f[i % 4], fourPoint2f[(i + 1) % 4], Scalar(20, 21, 237), 3);
	}
	////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////一些尝试//////////////////////////////////////
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


	namedWindow("效果图", WINDOW_NORMAL);
	imshow("效果图", src);


	waitKey(0);
	return 0;
}