# opencv_study

# 编译注意事项：
1. 直接编译，添加编译选项 `pkg-config --cflags --libs opencv`
2. 使用Makefile 编译opencv程序，包含的头文件路径名，库文件名，链接文件
   会因为安装环境的不同而有所不同，可使用下面命令进行查询：
		pkg-config --cflags --libs opencv

# opencd_read_camera
1.在linux系统读取摄像头设备数据，在显示屏中直接显示。

2.将摄像头采集到的数据保存成 avi 视频格式


# basic_opencv
工程中包含三个opencv基本操作函数的使用

1、图像虚化 cvSmooth

2、图像尺寸缩小一半 cvCreateImage

3、图像边缘检测 cvCanny


# draw_box_on_screen
在屏幕上画矩形框


# watershed_image
图像分割--分水岭算法

