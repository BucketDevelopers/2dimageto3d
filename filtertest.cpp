#include<opencv2/opencv.hpp>

#include <iostream>
#include <iostream>

using namespace std;
using namespace cv;


int mai3n(int argc, char* argv[])
{


 Mat inputFrame = imread("/home/master/custom/Projects/Cplusplus/CV/testimage.jpg");
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
    imshow("final",outputFrame);
    waitKey(0);
}
