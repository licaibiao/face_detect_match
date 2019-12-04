CC = g++
INC_JSON_DIR = ./json/
INC_CURL_DIR = ./curl/
JSON_INC = -I$(INC_JSON_DIR)
CURL_INC = -I$(INC_CURL_DIR)
EXT_INC = $(JSON_INC) $(CURL_INC)
 

JSON_LIB_PATH =  -L./curl/lib/ -lcurl
CURL_LIB_PATH =  -L./json/lib/ -ljson_linux-gcc-4.6_libmt
EXT_LIB = $(JSON_LIB_PATH) $(CURL_LIB_PATH)
 
LINK_LIB = 

BUILD_TARGE = face_match.cpp
#BUILD_TARGE = access_taken.cpp
TARGE = test

all:$(TARGE)
 
$(TARGE):$(BUILD_TARGE)
	$(CC) $(BUILD_TARGE) $(EXT_INC)  -g  -o $(TARGE) $(LINK_LIB) $(EXT_LIB)

clean:
	rm -rf *.o $(TARGE)
