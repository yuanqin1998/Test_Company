#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>

#define _F_LOGIN "login.ini"
#define _F_STOCK "stock.txt"

using namespace std;

struct msg
{
	int id;				//程序id
	string name;		//程序名
	int price;			//程序价格
	int num;			//程序个数
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//读取登陆信息
	void ReadLogin(CString &name, CString &pwd);

	//修改密码
	void WritePwd(char* name, char* pwd);

	// 读取程序数据
	void ReadDocline();

	//程序写入文件
	void WirteDocline();

	//添加新程序
	void Addline(CString name, int num, int price);

	list<msg> ls;	//存储程序容器
	int num;			//用来记录程序个数
};

