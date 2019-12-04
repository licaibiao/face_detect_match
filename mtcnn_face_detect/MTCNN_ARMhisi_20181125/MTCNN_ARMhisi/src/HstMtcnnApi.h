
#ifndef _HSTMTCNNAPI_H_
#define _HSTMTCNNAPI_H_

#define MAX_FACE_NUM			10
#define MTCNN_MODEL_PATH_NAME	"./models/"

#define __FOR_ARM_DEBUG__     
//#define __FOR_UBUNTU_DEBUG_

typedef struct
{
	char FileName[MAX_FACE_NUM][128];   /**输出文件名，作为输出**/
	char PathName[128];      			/**输出目录，作为输入**/
	unsigned char FaceNum;   			/**人脸截图个数**/
}MTCNN_OUT_IMAGE_S;


/******************************************************** 
Function:	 MTCNN_FaceNumDetect	
Description: 人脸数检测
Input:	ps8ImagePath   需要进行人脸检测图片所在的目录
OutPut: pu8FaceNum     检测结果：人脸数目
Return: 函数运行结果，0为成功，非0为异常
Others:
Author: Caibiao Lee
Date:	2018-10-25
*********************************************************/
int MTCNN_FaceNumDetect(char * ps8ImagePath, unsigned char *pu8FaceNum);



/******************************************************** 
Function:	 MTCNN_FaceCutOut	
Description: 将图片中识别到的人脸全部截取出来，最多为8个人脸
Input:	ps8ImagePath   需要进行人脸检测图片所在的目录
OutPut: OutImge     人脸截取数据信息
Return: 函数运行结果，0为成功，非0为异常
Others: 调用该函数需要输入PathName参数指定输出目录,
		只需要目录，不需要名字
Author: Caibiao Lee
Date:	2018-10-20
*********************************************************/
int MTCNN_FaceCutOut(char *ps8ImagePath, MTCNN_OUT_IMAGE_S *OutImge);

#endif

