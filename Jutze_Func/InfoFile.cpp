#include "pch.h"
#include "InfoFile.h"


CInfoFile::CInfoFile()
{
}


CInfoFile::~CInfoFile()
{
}

//读取登陆信息
void CInfoFile::ReadLogin(CString &name, CString &pwd)
{
	ifstream ifs; //创建文件输入对象
	ifs.open(_F_LOGIN); //打开文件

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //读取一行内容
	name = CString(buf);			 //char *转换为CString

	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close(); //关闭文件
}

//修改密码
void CInfoFile::WritePwd(char* name, char* pwd)
{
	ofstream ofs;	 //创建文件输出对象
	ofs.open(_F_LOGIN); //打开文件

	ofs << name << endl; //name写入文件
	ofs << pwd << endl;	//pwd写入文件

	ofs.close();	//关闭文件
}

//读取程序信息
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //输入方式打开文件

	char buf[1024] = { 0 };
	num = 0;	//初始化程序数目为0
	ls.clear();
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //没到文件结尾
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //读取一行
		num++;	//程序数目加一

		//AfxMessageBox(CString(buf));
		char *sst = strtok(buf, "|"); //以“|”切割
		if (sst != NULL)
		{
			tmp.id = atoi(sst); //程序id
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//程序名称

		sst = strtok(NULL, "|");
		tmp.price = atoi(sst);	//程序价格

		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);	//程序数目

		ls.push_back(tmp); //放在链表的后面
	}

	ifs.close(); //关闭文件
}

//程序写入文件
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK);//输出方式打开文件

	if (ls.size() > 0)	//程序链表有内容才执行
	{
		ofs << "程序ID|程序名称|程序价格|库存" << endl; //写入表头

		//通过迭代器取出链表内容，写入文件，以“|”分隔，结尾加换行
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->id << "|";		
			ofs << it->name << "|";
			ofs << it->price << "|";
			ofs << it->num << endl;
		}
	}

	ofs.close();//关闭文件
}

//添加新程序
//name:程序名称，num：库存，price：价格
void CInfoFile::Addline(CString name, int num, int price)
{
	msg tmp;

	if (ls.size() > 0)
	{
		//程序名称，库存，价格有效
		if (!name.IsEmpty() && num > 0 && price > 0)
		{
			tmp.id = ls.size() + 1;	//id自动加1
			CStringA str;
			str = name;	//CString转CStirngA
			tmp.name = str.GetBuffer(); //CStirngA转char *，程序名称
			tmp.num = num;	//库存
			tmp.price = price;	//价格

			ls.push_back(tmp);	//放在链表的后面
		}
	}
}
