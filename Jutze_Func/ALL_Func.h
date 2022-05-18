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

//����xml���ݵĽ�����
void Xml_Test();
void xml_Read_Write();

//������ʾ��ǰʱ��
void Chrono_Test();

//�ҵ�����vector����ͬ��Ԫ�أ��ظ���Ԫ��ֻҪһ����
std::vector<int> findSame(const std::vector<int>& nLeft, const std::vector<int>& nRight);

//����toStyledString �� CharReaderBuilder��Json���ַ����������ת����
void Json_Array(string Array_in);

//����lambda����
int* Test_lambda_sort(int* num);

//д�ļ�
void Write_File();

//�����ַ���
void String_WString_CAtlString();


