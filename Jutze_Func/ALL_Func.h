#pragma once
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>//BOOST_FOREACH
#include "json/json.h"
#include <iostream>
//#include <windows.h>
#include <wchar.h>
#include <vector>
#include <afx.h>
#include <atlstr.h>
#include <comdef.h>
#include <codecvt>

#include <chrono>
using namespace boost::property_tree;
using namespace std;

#pragma comment(lib,"jsoncpp.lib")

//测试xml数据的解析。
void Xml_Test();
void xml_Read_Write();

//测试显示当前时间
void Chrono_Test();

//找到两个vector里相同的元素（重复的元素只要一个）
std::vector<int> findSame(const std::vector<int>& nLeft, const std::vector<int>& nRight);

//测试toStyledString 和 CharReaderBuilder（Json的字符输出和输入转换）
void Json_Array(string Array_in);

//测试lambda函数
int* Test_lambda_sort(int* num);

//写文件
void Write_File();

//测试字符串
void String_WString_CAtlString();


