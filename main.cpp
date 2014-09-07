#include "base.h"
#include "cartoonfilter/cartoon.h"

#define MAXRESX 640
#define MAXRESY 480
#define THRESH 20

/*

struct Pointv
{
    int x;
    int y;

} pnt;

Pointv pointfinder(int x1,int y1,int dist, int slope , int direction)
{

    int c = y1-(slope * x1);
    int  m  =slope;
    int x2 =0 , y2 = 0;
    int c2 = x1*x1 + y1*y1 +c *c - 2*y1*c -dist*dist;
    int b= (m*m + 2*m*c - 2 * y1 * m - 2 *x1);
    x2 = (-1*b  + sqrt((b*b)-4*(c2) ))/2.0;
    y2 = m*x2 + c;
    int x3= (-1*b  + sqrt((b*b)-4*(c2) ))/2.0;
    int y3=m*x3 + c;
    if( direction > 0 )
    {

        if(x2>x1)
        {

            pnt.x = x2;
            pnt.y = y2;
        }
        else
        {

            pnt.x = x3;
            pnt.y = y3;

        }

    }
    else

    {

        if(x2>x1)
        {


            pnt.x = x3;
            pnt.y = y3;

        }
        else
        {

            pnt.x = x2;
            pnt.y = y2;


        }



    }
    cout<<"\nYOYOYOYO "<<pnt.x<<" "<<pnt.y;
    return pnt;

}


*/

int main(int argc, char** argv)
{

    int x_tl=MAXRESX,x_tr=0,x_bl=MAXRESX,x_br=0;
    int y_tl=MAXRESY,y_tr=MAXRESY,y_bl=0,y_br=0;


    int slopetl,slopetr,slopebl,slopebr;

    Mat inputFrame = imread("/home/master/custom/Projects/Cplusplus/2Dto3D/Testimages/test5.jpg");
    Mat edgeBlackImage;
    Mat outputFrame;

    vector<Vec4i> lines;
    lineclass *temp = NULL , *start = NULL;
    resize(inputFrame,inputFrame,Size(MAXRESX,MAXRESY));
    outputFrame=inputFrame.clone();

    imshow("org",inputFrame);

    blurImage(inputFrame,inputFrame,3,3);
    cartoonifyImage(inputFrame,inputFrame,true,false,false,1,180);
    //imshow("cartoonified",inputFrame);
    detectlines(inputFrame,edgeBlackImage,lines);
    /*selects lines based on thresh slope*/
    start=selectlinesonSlope(lines,10);

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

    line( outputFrame, Point(x_tl,y_tl), Point(x_br, y_br), Scalar(0,255,255), 3, CV_AA);
    line( outputFrame, Point(x_bl,y_bl), Point(x_tr, y_tr), Scalar(255,255,255), 3, CV_AA);

    /* pointfinder(x_tr,y_tr,MAXRESX/2,slopetr,-1);

     cout << "COOOOOOOO " << x_tr <<" "<<y_tr<< " "<<pnt.x<<" "<<pnt.y<<" "<<slopetr ;
     line( egdeBlackImage, Point(x_tr,y_tr), Point(pnt.x, pnt.y), Scalar(0,0,255), 3, CV_AA);

    */
    imshow("detected lines", outputFrame);
    //imshow("black image lines", edgeBlackImage);
    waitKey();

    return 0;
}
