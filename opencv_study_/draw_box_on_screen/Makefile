APP = test
INCLUDES = -I/usr/local/include/opencv -I/usr/local/include  
LIBS = -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core  
LIBDIRS = -L/usr/local/lib 
OPT = 
CC=g++  
OBJS= draw_box_on_screen.o  
  
%.o:%.cpp  
	$(CC) -c $(INCLUDES) $+ $(OPT)  
  
$(APP):$(OBJS)  
	$(CC) -o $@ $(OBJS) $(LIBDIRS) $(LIBS)
clean:  
	rm -rf *o *.avi  $(APP) 
