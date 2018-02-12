#include <iostream>   
#include <string>    
#include <jsoncpp/json/json.h> 
using namespace std;          
int main(void)   {   
	Json::Value root;      
	Json::FastWriter fast;   
	root["ModuleType"] = Json::Value("你好");     
	root["ModuleCode"] = Json::Value("22");    
	root["ModuleDesc"] = Json::Value("33");      
	root["DateTime"] = Json::Value("44");     
	root["LogType"] = Json::Value("55");    
	Json::Value val;      
	val[0] = 1;
	val[1] = 2;
	val[2] = 3;
	root["array"] = val;
	
	cout<<fast.write(root)<<endl;
	cout<<root["array"][1]<<endl;
	return 0;  
}
