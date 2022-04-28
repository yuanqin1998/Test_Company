// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "Jutze_Func.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"
#include "CLoginDlg.h"
#include "InfoFile.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_name(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_PWD, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN_SURE, &CLoginDlg::OnBnClickedButtonLoginSure)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN_CANCEL, &CLoginDlg::OnBnClickedButtonLoginCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedButtonLoginSure()
{
	// TODO: 在此添加控件通知处理程序代码
	//登录按钮点击事件
	UpdateData(TRUE);

	if (m_name.IsEmpty()||m_pwd.IsEmpty())
	{
		MessageBox(L"输入内容不能为空", L"ERROR");
		return;
	}

	CInfoFile file; //创建操作文件类对象，需要头文件#include "InfoFile.h" 
	CString user, pwd;

	//读取配置文件，获取用户名密码，参数为引用传递
	file.ReadLogin(user, pwd);

	if (m_name == user)//用户名相等
	{
		if (m_pwd != pwd)
		{
			MessageBox(_T("密码错误"),L"ERROR");
			m_name.Empty(); //清空
			m_pwd.Empty();
		}
		else
		{
			CDialogEx::OnOK();
		}
	}
	else
	{
		MessageBox(_T("用户名不存在", L"ERROR"));
		m_name.Empty();
		m_pwd.Empty();
	}
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//默认登录信息
	m_name = TEXT("秦源");	//用户名
	m_pwd = TEXT("123");//密码
	UpdateData(FALSE); //内容更新到对应的控件

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnBnClickedButtonLoginCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//CDialogEx::OnOK();//注释已防止回车进入,调用登录按键
	CLoginDlg::OnBnClickedButtonLoginSure();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	exit(0);//关闭退出程序
	CDialogEx::OnClose();
}
