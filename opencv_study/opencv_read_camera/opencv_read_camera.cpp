#include "cv.h"  
#include "cxcore.h"   
#include "highgui.h"  
#include <iostream>   
  
using namespace std;   
int main()   
{     
    CvCapture* capture=cvCaptureFromCAM(-1);  
    CvVideoWriter* video=NULL;  
    IplImage* frame=NULL;  
  
    int n;  
  
    if(!capture) //如果不能打开摄像头给出警告  
    {  
        cout<<"Can not open the camera."<<endl;  
        return -1;  
    }  
    else  
    {  
        frame=cvQueryFrame(capture); //首先取得摄像头中的一帧  
        video=cvCreateVideoWriter("camera.avi", CV_FOURCC('X', 'V', 'I', 'D'), 25,  
        cvSize(frame->width,frame->height)); //创建CvVideoWriter对象并分配空间  
        //保存的文件名为camera.avi，编码要在运行程序时选择，大小就是摄像头视频的大小，帧频率是32  
        if(video) //如果能创建CvVideoWriter对象则表明成功  
        {  
            cout<<"VideoWriter has created."<<endl;  
        }  
  
        cvNamedWindow("Camera Video",1); //新建一个窗口  
        int i = 0;  
        while(i <= 1000) // 让它循环1000次自动停止录取  
        {  
            frame=cvQueryFrame(capture); //从CvCapture中获得一帧  
            if(!frame)   
            {   
                cout<<"Can not get frame from the capture."<<endl;   
                break;   
            }   
            n=cvWriteFrame(video,frame); //判断是否写入成功，如果返回的是1，表示写入成功    
            cout<<n<<endl;   
            cvShowImage("Camera Video",frame); //显示视频内容的图片   
            i++;   
            if(cvWaitKey(2)>0)    
                break; //有其他键盘响应，则退出    
        }  
  
        cvReleaseVideoWriter(&video);   
        cvReleaseCapture(&capture);   
        cvDestroyWindow("Camera Video");    
    }  
    return 0;    
}  
