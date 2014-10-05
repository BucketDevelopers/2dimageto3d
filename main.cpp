#include "base.h"
#include "cartoonfilter/cartoon.h"

#define MAXRESX 640
#define MAXRESY 480
#define THRESH 20


int main(int argc, char** argv)
{

    Mat inputFrame = imread("/home/raveendra/Testimages/test5.jpg");
    Mat edgeBlackImage;
    Mat outputFrame;

    vector<Vec4i> lines;
    lineclass *temp = NULL , *start = NULL;
    resize(inputFrame,inputFrame,Size(MAXRESX,MAXRESY));
    outputFrame=inputFrame.clone();

    imshow("org",inputFrame);

    blurImage(inputFrame,inputFrame,3,3);
    cartoonifyImage(inputFrame,inputFrame,true,false,false,0,180);
    //imshow("cartoonified",inputFrame);
    detectlines(inputFrame,edgeBlackImage,lines);
    /*selects lines based on thresh slope*/
    start=selectlinesonSlope(lines,5);

    temp=start;
    int i=1;
    while(temp!=NULL)
    {

        cout<<"\n"<<i<<"->";
        temp->display();
        //line(edgeBlackImage, Point(temp->x1, temp->y1), Point(temp->x2, temp->y2), Scalar(0,0,255), 3, CV_AA);

        line(outputFrame, Point(temp->x1, temp->y1), Point(temp->x2, temp->y2), Scalar(0,0,255), 3, CV_AA);

        temp=temp->next;
        i++;
    }

    int line_count;
    for(unsigned int k=1,sum =0;k<MAXRESX/2;k++)
    {
        temp=start;
        sum=0;
        line_count=0;
        while(temp!=NULL)
        {
            //circle(outputFrame,(Point(k,temp->get_y(k))),1,CV_RGB(0,10,255),3);

            if(temp->get_y(k)>0)
            {
                sum+= temp->get_y(k);
                line_count++;
            }
            temp=temp->next;
        }
        if(line_count)
            circle(outputFrame,(Point(k,sum/line_count)),1,CV_RGB(0,10,255),3);
    }
    //line(outputFrame, Point(0, 0), Point(MAXRESX/2, MAXRESY/2), Scalar(255,25,255), 3, CV_AA);

    imshow("detected lines", outputFrame);
    //imshow("black image lines", edgeBlackImage);
    int x2,y2;
    pointfinder(0,0,x2,y2,10,45,1);
    cout<<"\nHELLO "<<x2<<" "<<y2;
    fflush(stdout);
    waitKey();

    return 0;
}
