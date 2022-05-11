#include "pch.h"
#include "InfoFile.h"


CInfoFile::CInfoFile()
{
}


CInfoFile::~CInfoFile()
{
}

//��ȡ��½��Ϣ
void CInfoFile::ReadLogin(CString &name, CString &pwd)
{
	ifstream ifs; //�����ļ��������
	ifs.open(_F_LOGIN); //���ļ�

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); //��ȡһ������
	name = CString(buf);			 //char *ת��ΪCString

	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close(); //�ر��ļ�
}

//�޸�����
void CInfoFile::WritePwd(char* name, char* pwd)
{
	ofstream ofs;	 //�����ļ��������
	ofs.open(_F_LOGIN); //���ļ�

	ofs << name << endl; //nameд���ļ�
	ofs << pwd << endl;	//pwdд���ļ�

	ofs.close();	//�ر��ļ�
}

//��ȡ������Ϣ
void CInfoFile::ReadDocline()
{
	ifstream ifs(_F_STOCK); //���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	num = 0;	//��ʼ��������ĿΪ0
	ls.clear();
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof()) //û���ļ���β
	{
		msg tmp;

		ifs.getline(buf, sizeof(buf)); //��ȡһ��
		num++;	//������Ŀ��һ

		//AfxMessageBox(CString(buf));
		char *sst = strtok(buf, "|"); //�ԡ�|���и�
		if (sst != NULL)
		{
			tmp.id = atoi(sst); //����id
		}
		else
		{
			break;
		}

		sst = strtok(NULL, "|");
		tmp.name = sst;	//��������

		sst = strtok(NULL, "|");
		tmp.price = atoi(sst);	//����۸�

		sst = strtok(NULL, "|");
		tmp.num = atoi(sst);	//������Ŀ

		ls.push_back(tmp); //��������ĺ���
	}

	ifs.close(); //�ر��ļ�
}

//����д���ļ�
void CInfoFile::WirteDocline()
{
	ofstream ofs(_F_STOCK);//�����ʽ���ļ�

	if (ls.size() > 0)	//�������������ݲ�ִ��
	{
		ofs << "����ID|��������|����۸�|���" << endl; //д���ͷ

		//ͨ��������ȡ���������ݣ�д���ļ����ԡ�|���ָ�����β�ӻ���
		for (list<msg>::iterator it = ls.begin(); it != ls.end(); it++)
		{
			ofs << it->id << "|";		
			ofs << it->name << "|";
			ofs << it->price << "|";
			ofs << it->num << endl;
		}
	}

	ofs.close();//�ر��ļ�
}

//����³���
//name:�������ƣ�num����棬price���۸�
void CInfoFile::Addline(CString name, int num, int price)
{
	msg tmp;

	if (ls.size() > 0)
	{
		//�������ƣ���棬�۸���Ч
		if (!name.IsEmpty() && num > 0 && price > 0)
		{
			tmp.id = ls.size() + 1;	//id�Զ���1
			CStringA str;
			str = name;	//CStringתCStirngA
			tmp.name = str.GetBuffer(); //CStirngAתchar *����������
			tmp.num = num;	//���
			tmp.price = price;	//�۸�

			ls.push_back(tmp);	//��������ĺ���
		}
	}
}
