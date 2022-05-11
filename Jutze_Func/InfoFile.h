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
	int id;				//����id
	string name;		//������
	int price;			//����۸�
	int num;			//�������
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//��ȡ��½��Ϣ
	void ReadLogin(CString &name, CString &pwd);

	//�޸�����
	void WritePwd(char* name, char* pwd);

	// ��ȡ��������
	void ReadDocline();

	//����д���ļ�
	void WirteDocline();

	//����³���
	void Addline(CString name, int num, int price);

	list<msg> ls;	//�洢��������
	int num;			//������¼�������
};

