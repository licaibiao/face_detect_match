// Basic_OpenCV_2.cpp : 定义控制台应用程序的入口点。  
//  
  
//#include "stdafx.h"  
#include <iostream>  
#include "cv.h"  
#include "highgui.h"  
  
using namespace std;  

/*
 * 通过修改 cvSmooth 函数最后两个参数，设置输出图像的
 * 虚化效果程度，数值越大，虚化月明显
 *
 */ 
void SmoothImage(IplImage* image)//平滑函数  
{  
    cvNamedWindow("Smooth_in");  
    cvNamedWindow("Smooth_out");  
    cvShowImage("Smooth_in",image);  
  
    IplImage* out = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,3);  
    //cvSmooth(image,out,CV_BLUR,32,32);//平滑函数,后面两个参数是窗口大小  
    cvSmooth(image,out,CV_BLUR,10,10); 
    cvShowImage("Smooth_out",out);  
  
    cvReleaseImage(&out);  
  
    cvWaitKey(0);  
    cvDestroyAllWindows();  
}  

/*
 * 经测试，好像该函数只能缩小为原图的一半，并不能缩放成其他的尺寸
 *
 */  
void doPyrDown(IplImage* in )//图像缩小为一半  
{  
    //Best to make sure input image is divisible by two.  
    //assert(in->width/2 == 0 && in->height/2 == 0);  
    IplImage* out = cvCreateImage(cvSize(in->width/2 , in->height/2) , in->depth , in->nChannels);  
    cvPyrDown(in , out);  
  
    cvNamedWindow("PyrDown_out");  
    cvShowImage("PyrDown_out",out);  
    cvReleaseImage(&out);  
  
    cvWaitKey(0);  
    cvDestroyAllWindows();  
    //return out;  
  
  
}  
  
/*
 *图像边缘检测
 *in 单通道输入图像 
 *lowThresh 低阈值
 *highThresh 高个阈值
 *aperture 算子内核大小 (见 cvSobel).
 *采用 CANNY 算法发现输入图像的边缘而且在输出图像中标识这些边缘。
 *lowThresh和highThresh 当中的小阈值用来控制边缘连接，大的阈值用来控制强边缘的初始分割
 */
void doCanny(IplImage* in , double lowThresh , double highThresh , double aperture)  
{  
    IplImage* out = cvCreateImage(cvSize(in->width,in->height) , IPL_DEPTH_8U , 1);  
    if(in->nChannels != 1)  
    {  
        //cout<<"error! unsupported format or combination of formats() in unknown function"<<endl;  
        //return;//canny only handles gray scale image  
  
        //若不是灰度图，直接转化成灰度图  
        IplImage* gray =  cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 1);    
        cvCvtColor(in, gray, CV_BGR2GRAY);  
        out = gray;  
    }  
          
  
    cvCanny(in , out , lowThresh , highThresh , aperture );  
  
    cvNamedWindow("Canny_out");  
    cvShowImage("Canny_out",out);  
    cvReleaseImage(&out);  
  
    cvWaitKey(0);  
    cvDestroyAllWindows();  
}  
  
int main(int argc, char* argv[])  
{  
    IplImage* image = cvLoadImage("test.jpg");  
    //SmoothImage(image);  
    //doPyrDown(image);  
    //doCanny(image ,10 , 100 , 3 );  
    doCanny(image ,10 , 100 , 3);  
    system("pause");  
    return 0;  
}  
