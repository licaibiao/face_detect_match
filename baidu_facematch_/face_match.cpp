#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include "include/curl.h"
#include "include/json.h"
using namespace std;
#define PATH_LEN	50

const std::string AccessKey ="24.aeb0199102972324f40e88bf7ee70228.2592000.1505703119.282335-9971270";
static const char* base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const static std::string face_match_url = "https://aip.baidubce.com/rest/2.0/face/v2/match";
static std::string face_match_result;

/**
 * curl发送http请求调用的回调函数，回调函数中对返回的json格式的body进行了解析，解析结果储存在全局的静态变量当中
 * @param 参数定义见libcurl文档
 * @return 返回值定义见libcurl文档
 */
static size_t callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    // 获取到的body存放在ptr中，先将其转换为string格式
    face_match_result = std::string((char *) ptr, size * nmemb);
    return size * nmemb;
}

/**
 * 调用人脸匹配接口，返回json格式的结果，具体格式解析见百度大脑文档
 * @param json_result 以string格式返回的json格式的结果
 * @param images 多个base64编码的图像数据字符串 注：base64数据不包含格式信息（即不包含data:image/jpeg;base64））
 * @param access_token 以string格式传入的access token数据，access token获取方式见access_token获取相关文档及代码
 * @return 调用成功返回0，发生错误返回其他错误码
 */
int match(std::string &json_result, const std::vector<std::string> &images, const std::string &access_token) {
    std::string url = face_match_url + "?access_token=" + access_token;
    CURL *curl = NULL;
    CURLcode result_code;
    int is_success;

	
	double start,end,cost;

	start=clock(); 

    curl = curl_easy_init();
    if (curl) {
        std::string image_plain = images[0];
        for (int i = 1; i < images.size(); i++) {
            image_plain.append("," + images[i]);
        }
#if 0
		end=clock(); 
		cost=end-start;
		cout << "test clock1 = " << cost << endl;
#endif
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_httppost *post = NULL;
        curl_httppost *last = NULL;

        curl_formadd(&post, &last, CURLFORM_COPYNAME, "images", CURLFORM_COPYCONTENTS, image_plain.data(),
                     CURLFORM_END);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        result_code = curl_easy_perform(curl);
        if (result_code != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(result_code));
            is_success = 1;
            return is_success;
        }
		cout<<"result_code=" <<result_code<<endl;

        json_result = face_match_result;
        curl_easy_cleanup(curl);
        is_success = 0;
    } else {
        fprintf(stderr, "curl_easy_init() failed.");
        is_success = 1;
    }
    return is_success;
}

int Read_Image(char *path, char* out)
{
	FILE *fd;
	int length;
	int ret;
	
	fd = fopen(path,"r");
	if(fd==NULL)
	{
		cout<<"Read_Image open file err"<<endl;
	}
	
	fseek(fd, 0, SEEK_END);
	length = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	ret = fread(out, 1, length, fd);
	if(ret == 0)
	{
		cout<<"Read_Image fread err" <<endl;
	}
	fclose(fd);
	
	return ret;
}


//chsrc为源数据，chdes为Base64编码后的数据，len为数据长度
void Base64_Code(char* chsrc, char* chdes, int len)
{
      unsigned char char_array_3[3], char_array_4[4];
      int i = 0, j = 0;
  
      while(len--)
      {
            char_array_3[i++] = *(chsrc++);
            if(3 == i)
            {
                  char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                  char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                  char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                  char_array_4[3] = char_array_3[2] & 0x3f;
                  for(i = 0; i < 4; i++)
                        *(chdes+i) = base64_chars[char_array_4[i]];
     
                  i = 0;
                 chdes += 4;
            }
      }
      if(i)
      {
             for(j = i; j < 3; j++)
             char_array_3[j] = '\0';
   
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
   
            for(j = 0; j < (i+1); j++)
                  *(chdes++) = base64_chars[char_array_4[j]];
    
            while((3 > i++))
                  *(chdes++) = '=';
      }
  
      *chdes = '\0';
      return;
}   

int Calculat_FlieLength(char *path)
{
	FILE *fd;
	int length;

	fd = fopen(path,"r");
	fseek(fd, 0, SEEK_END);
	length = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	fclose(fd);
	return length;
	
}

int ReadJson_Int(const std::string & strValue, std::string key, int &value)
{
	Json::Reader reader;  
	Json::Value  root;
	int ret = -1;
	
	if (reader.parse(strValue, root))
	{
		value = root[key].asInt();
		ret = 0;
	}else
	{
		ret = -1;
	}
	
	return ret;
}

int  ReadJson_Long(const std::string & strValue, std::string key, long &value)
{
	Json::Reader reader;  
	Json::Value  root;
	int ret = -1;

	if (reader.parse(strValue, root))
	{
		value = root[key].asDouble();
		ret = 0;
	}else
	{
		ret = -1;
	}
	return ret;
}

int ReadJson_string(const std::string & strValue, std::string key, std::string &value)
{
	Json::Reader reader;  
	Json::Value  root;
	int ret = -1;

	if (reader.parse(strValue, root))
	{
		value  = root[key].asString();
		ret = 0;
	}
	
	return ret;
}

int ReadJson_arrayObj_int(const std::string & strValue, std::string obj, std::string key, int &value)
{
	Json::Reader reader;  
	Json::Value  root; 
	int ret = -1;

	if (reader.parse(strValue, root))
	{
		Json::Value arrayObj = root[obj];	
		 for(unsigned int i = 0; i < arrayObj.size(); i++)
		 {			 
			if (arrayObj[i].isMember(key))
			{
			  	value = arrayObj[i][key].asInt();
				ret = 0;
			}else
			{
				ret = -1;
			}
		}
	}
	return ret;
}

int ReadJson_arrayObj_string(const std::string & strValue, std::string obj, std::string key, std::string &value)
{
	Json::Reader reader;  
	Json::Value  root; 
	int ret = -1;

	if (reader.parse(strValue, root))
	{
		Json::Value arrayObj = root[obj];	
		 for(unsigned int i = 0; i < arrayObj.size(); i++)
		 {			 
			if (arrayObj[i].isMember(key))
			{
			  	value = arrayObj[i][key].asString();
				ret = 0;
			}else
			{
				ret = -1;
			}
		}
	}
	return ret;
}



int main(void)
{
	int ret = -1;
	int file_len = 0;
	int fread_len = 0;

	std::string  result ;
	std::string ImageA;
	std::string ImageB;
	
	char pathA[PATH_LEN] = "./1.jpg";
	char pathB[PATH_LEN] = "./2.jpg";
		
	char* PpathA = pathA;
	char* PpathB = pathB;
	char* PdataA = NULL;
	char* PdataB = NULL;
	char* Pbase64A = NULL;
	char* Pbase64B = NULL;

	
	file_len = Calculat_FlieLength(pathA);
	PdataA = (char *)malloc(file_len);
	Pbase64A = (char *)malloc(file_len*3/2); /*base63 = 1.33 jpg*/
	fread_len = Read_Image(pathA, PdataA);

	if(file_len==fread_len)
	{
		Base64_Code(PdataA, Pbase64A, fread_len);
		ImageA = Pbase64A;
		cout << "fileA len = " << file_len<<"   "<< "Pbase64A len = " << strlen(Pbase64A)<< endl;
	}
	else
	{
		cout << "Image A read err" << endl;
	}

		
	file_len = Calculat_FlieLength(pathB);
	PdataB = (char *)malloc(file_len);
	Pbase64B = (char *)malloc(file_len*3/2);
	

	fread_len = Read_Image(pathB, PdataB);
	if(file_len==fread_len)
	{
		Base64_Code(PdataB, Pbase64B, fread_len);
		ImageB = Pbase64B;		
		cout << "fileB len = " << file_len<<"   "<< "Pbase64B len = " << strlen(Pbase64B) << endl;
	}
	else
	{
		cout<<"Image B read err"<<endl;
	}

	std::vector<std::string> InputImag;
	InputImag.push_back(ImageA);
	InputImag.push_back(ImageB);

	ret = match(result, InputImag, AccessKey);
	if(ret!=0)
	{
		cout<<"face_detect functtion err  "<<ret<<endl;
	}else
	{
		cout<<result<<endl;	
	}

	if(result.empty())
	{
		cout<<"result id empty " <<endl;
	}
	

	std::string index_i;
	ret = ReadJson_arrayObj_string(result, "result", "index_i", index_i);
	if(0==ret)
	{
		cout << " index_i = " << index_i <<endl;
	}
	
	std::string index_j;
	ret = ReadJson_arrayObj_string(result, "result", "index_j", index_j);
	if(0==ret)
	{
		cout << " index_j = " << index_j <<endl;
	}

	int score = 0 ;
	ret = ReadJson_arrayObj_int(result, "result", "score", score);
	if(0==ret)
	{
		cout << " score = " << score <<endl;
	}
	

	int result_num = 0;
	ret = ReadJson_Int(result, "result_num", result_num);
	if(0==ret)
	{
		cout << " result_num = " << result_num <<endl;
	}
	
	long log_id = 0;
	ret = ReadJson_Long(result, "log_id", log_id);
	if(0==ret)
	{
		cout << " log_id = " << log_id <<endl;
	}
	
	free(PdataA);
	free(Pbase64A);
	free(PdataB);
	free(Pbase64B);
	
	return 0;
}


