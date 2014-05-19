#include<opencv2/opencv.hpp>
#include<iostream>
#define WIDTH 640
#define HEIGHT 480
using namespace cv;
using namespace std;


void customMask(Mat src, Mat& Dst,Point* custom_points , int no_of_points)
{
/*
Create a Blank image with same size as that of Source image
Then draw a polygon of any color from the points passed
Finally apply the mask
*/

    Mat temp(src.rows,src.cols, CV_8UC3, Scalar(0,0,0));
    int lineType = 8;
    const Point* ppt[1] = { custom_points };
    int npt[] = { no_of_points };
    fillPoly(temp,
             ppt,
             npt,
             1,
             Scalar(255, 255, 255),
             lineType);

    //Bug Fix
    Dst.release();    //Fix for src == dst Bug in copyTo

    src.copyTo(Dst,temp);
}

int main2()
{
    Mat image=imread("/home/master/custom/Projects/Cplusplus/CV/test2.jpg");
    Mat Dest;
    Point custom_points[4];
    custom_points[0] = Point(200,40);
    custom_points[1] = Point(300,40);
    custom_points[2] = Point(500,450);
    custom_points[3] = Point(100,450);

    customMask(image,Dest,custom_points,4);
    imshow("Window",Dest);

    waitKey(10000);
}
