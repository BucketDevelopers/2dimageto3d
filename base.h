#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED
#define MAXRESX 640
#define MAXRESY 480
#include<math.h>
#include<iostream>
#include <opencv2/opencv.hpp>
#define PI (3.141592653589793)

using namespace cv;
using namespace std;


class lineclass
{
    float slope;

public:
    int x1,x2,y1,y2;
    lineclass *next;
    void calculateSlope();
    void swaplinecords();
    int getSlope();
    void display();


    lineclass(int xone,int yone,int xtwo,int ytwo)
    {

        this->x1=xone;
        this->y1=yone;
        this->x2=xtwo;
        this->y2=ytwo;
        this->next=NULL;
        swaplinecords();
        calculateSlope();

    }

};
void lineclass::display()
{

    cout<<"\nCoords x1,y1,x2,y2 and slope "<<this->x1<<" "<<this->y1<<" "<<this->x2<<" "<<this->y2<<" "<<this->slope;


}
void lineclass::calculateSlope()
{
    if(!(x2-x1))
    {
        slope=90.0;
    }
    else
    {
        slope = (float)(y2-y1)/(float)(x2-x1);
        slope=atan(slope)*180.0/3.14;
        swaplinecords();
        //cout<<"\nSlope of line : "<<slope ;
    }
}
void lineclass::swaplinecords()
{
    if(this->x1 < this->x2)
    {
        return;
    }
    else
    {
        int t1,t2;
        t1=this->x1;
        t2=this->y1;
        this->x1=this->x2;
        this->y1=this->y2;
        this->x2=t1;
        this->y2=t2;
    }
}

int lineclass::getSlope()
{

    return slope;

}

lineclass * allocate (lineclass& li)
{

    lineclass * temp = new lineclass(li.x1,li.y1,li.x2,li.y2);
    return temp;

}

lineclass * allocate (int x1,int y1,int x2,int y2)
{

    lineclass * temp = new lineclass(x1,y1,x2,y2);
    return temp;

}


/*********************************/
/***IMAGE PROCESSING FUNCTIONS****/
/*********************************/

/*Blurs the image based on parameters*/
void blurImage(Mat &inputFrame, Mat &outputFrame,int kx,int ky)
{
    /*Blurring the image*/
    blur(inputFrame,outputFrame,Size(kx,ky));
}


/*Detect Lines on the image*/

void detectlines(Mat& src,Mat& linesimage, vector<Vec4i> &lines)
{

    Mat temp;
    Canny(src, temp, 50, 50);
    cvtColor(temp, linesimage, CV_GRAY2BGR);
    HoughLinesP(temp, lines, 1, CV_PI/180, 50, 30, 12 );

}


/*Select only particular lines*/

lineclass* selectlinesonSlope(vector<Vec4i> &lines,int threshholdSlope)
{
    lineclass* temp = NULL,*start=NULL;
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        lineclass linetemp(l[0],l[1],l[2],l[3]);

        if(fabs(linetemp.getSlope())>threshholdSlope)
        {
            if(start==NULL)
            {
                temp= allocate(linetemp);
                start=temp;
            }
            else
            {
                temp->next= allocate(linetemp);
                temp=temp->next;
            }
        }
    }
    return start;
}

/************/
/***MATH*****/
/************/
/*Find x2,y2 if x1,y1 and slope ,direction and distance is given*/
void pointfinder(int x1,int y1,int& x2,int& y2,int dist,int angle,int direction)
{

    y2=y1+((direction>0)?1:-1)*(dist*sin(angle*PI/180.0));
    x2=x1+((direction>0)?1:-1)*(dist*cos(angle*PI/180.0));

}


#endif // BASE_H_INCLUDED
