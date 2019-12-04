
#build for arm
ARCH=arm

ifeq ($(ARCH),arm)
    COMPILE_CROSS:= arm-hisiv300-linux-
    CFLAGS += -mfloat-abi=softfp 
    CFLAGS += -mfpu=neon
else
    COMPILE_CROSS:=
    CFLAGS    += -D __x86_64__
    INC       += -I ./src/ncnn/layer/x86
    X86_CPP   := $(wildcard ./src/ncnn/layer/x86/*.cpp)
    X86_OBJ   := $(patsubst %.cpp,%.o,$(X86_CPP))
endif

CC := $(COMPILE_CROSS)gcc
GG := $(COMPILE_CROSS)g++
 
INC := -I ./src
INC += -I ./src/ncnn
INC += -I ./src/ncnn/layer
INC += -I ./src/ncnn/layer/arm

SRC_CPP	  := $(wildcard ./src/*.cpp)
NCNN_CPP  := $(wildcard ./src/ncnn/*.cpp)
LAYER_CPP := $(wildcard ./src/ncnn/layer/*.cpp)
ARM_CPP   := $(wildcard ./src/ncnn/layer/arm/*.cpp)

SRC_OBJ	  := $(patsubst %.cpp,%.o,$(SRC_CPP))
NCNN_OBJ  := $(patsubst %.cpp,%.o,$(NCNN_CPP))
LAYER_OBJ := $(patsubst %.cpp,%.o,$(LAYER_CPP))
ARM_OBJ   := $(patsubst %.cpp,%.o,$(ARM_CPP))

CFLAGS += -std=c++11
CFLAGS += -g
CFLAGS += -D linux

test:$(SRC_OBJ) $(NCNN_OBJ) $(LAYER_OBJ) $(ARM_OBJ) $(X86_OBJ) 
	echo $(OBJS)
	$(GG) $(CFLAGS) $^ -o $@  $(INC)
	
$(SRC_OBJ):%.o:%.cpp
	echo $(SRC_OBJ)
	$(GG) $(CFLAGS) -c $< -o $@ $(INC)	

$(NCNN_OBJ):%.o:%.cpp
	echo $(NCNN_OBJ)
	$(GG) $(CFLAGS) -c $< -o $@ $(INC)
	
$(LAYER_OBJ):%.o:%.cpp
	echo $(LAYER_OBJ)
	$(GG) $(CFLAGS) -c $< -o $@ $(INC)
	
$(ARM_OBJ):%.o:%.cpp
	echo $(ARM_OBJ)
	$(GG) $(CFLAGS) -c $< -o $@ $(INC)

$(X86_OBJ):%.o:%.cpp
	echo $(X86_OBJ)
	$(GG) $(CFLAGS) -c $< -o $@ $(INC)	

clean:
	$(RM) ./src/*.o ./src/ncnn/*.o ./src/ncnn/layer/*.o
	$(RM) ./src/ncnn/layer/arm/*.o  ./src/ncnn/layer/x86/*.o test
	$(RM) ./test  ./out/*
