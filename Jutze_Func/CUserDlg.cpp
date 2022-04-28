// UserDlg.cpp : 实现文件
//

#include "pch.h"
#include "Jutze_Func.h"
#include "CUserDlg.h"
#include "InfoFile.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(CUserDlg::IDD)
	, m_Pwd_New(_T(""))
	, m_Pwd_New_Sureagain(_T(""))
	, m_user(_T(""))
	, m_name(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PWD_NEW, m_Pwd_New);
	DDX_Text(pDX, IDC_EDIT_PWD_NEW_SUREAGAIN, m_Pwd_New_Sureagain);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序



void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//初始化
	m_user = L"管理员";

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	m_name = name;
	UpdateData(false);

}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//修改密码
	UpdateData(TRUE);
	if (m_Pwd_New.IsEmpty()||m_Pwd_New_Sureagain.IsEmpty())
	{
		MessageBox(L"输入内容不能为空", L"ERROR");
		return;
	}
	if (m_Pwd_New != m_Pwd_New_Sureagain)
	{
		MessageBox(L"新密码与确定密码要一致！", L"ERROR");
		return;
	}
	//新密码与旧密码要不同
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (m_Pwd_New == pwd)
	{
		MessageBox(L"新旧密码相同！", L"ERROR");
		return;
	}
	CStringA temp;
	CStringA temp2;
	temp = name;
	temp2 = m_Pwd_New_Sureagain;
	file.WritePwd(temp.GetBuffer(), temp2.GetBuffer());
	temp.ReleaseBuffer();
	temp2.ReleaseBuffer();
	MessageBox(L"修改成功");
	//清空数据
	m_Pwd_New.Empty();
	m_Pwd_New_Sureagain.Empty();
	UpdateData(false);
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Pwd_New.Empty();
	m_Pwd_New_Sureagain.Empty();
	UpdateData(false);
}
