#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
using namespace std;



int main(int argc, char** argv)
{
 Mat inputFrame = imread("/home/master/custom/Projects/Cplusplus/CV/test8.jpg");
resize(inputFrame,inputFrame,Size(640,480));
Mat outputFrame;

    Mat bgr,edgesBgr,edges,gray;

    cvtColor(inputFrame, bgr, COLOR_BGRA2BGR);
    pyrMeanShiftFiltering(bgr, bgr, 0.3, 0.2);

        int numChannes = bgr.channels();

        if (numChannes == 4){
            cvtColor(bgr, gray, COLOR_BGRA2GRAY);

        }
        else if (numChannes == 3)
        {
            cvtColor(bgr, gray, COLOR_BGR2GRAY);
        }
        else if (numChannes == 1)
        {
            gray = bgr;
        }
    Canny(gray, edges, 150, 150);

    cvtColor(edges, edgesBgr, COLOR_GRAY2BGR);

        //bgr = bgr - edgesBgr;
    subtract(bgr, edgesBgr, bgr);

    cvtColor(bgr, outputFrame,COLOR_BGR2BGRA);
        imshow("org",inputFrame);
   // imshow("final",outputFrame);
Mat src(outputFrame);
blur(src,src,Size(3,3));
Mat dst,cdst;
 Canny(src, dst, 50, 50);



 cvtColor(dst, cdst, CV_GRAY2BGR);


  vector<Vec4i> lines;
  HoughLinesP(dst, lines, 1, CV_PI/180, 50, 30, 12 );
  for( size_t i = 0; i < lines.size(); i++ )
  {
    Vec4i l = lines[i];
    float angle=0.0;

    //Finding the angle of the line with the x-axis
    //theta = (tan-1 of l3-l1/l2-l0)*180/PI;
    //angle=atan((l[3]-l[1])/(l[2]-l[0]))*180.0/3.14159265;
    cout<<"\nAngle "<<i<<" "<<angle<<" x1,y1,x2,y2: "<<l[0]<<" "<<l[1]<<" "<<l[2]<<" "<<l[3]<<" ";
    if(fabs(l[3]-l[1])>100){
    cout<<"printed";
    line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);

    imshow("detected lines", cdst);
    //waitKey();
    }


  }

 imshow("source", src);
 imshow("detected lines", cdst);

 waitKey();

 return 0;
}
