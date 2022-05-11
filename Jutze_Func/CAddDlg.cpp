// CAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "Jutze_Func.h"
#include "CAddDlg.h"
#include "InfoFile.h"


// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(IDD_DIALOG_ADD)
	, m_price1(0)
	, m_num1(0)
	, m_name2(_T(""))
	, m_price2(0)
	, m_num2(0)
	, m_num3(0)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price1);
	//DDX_Text(pDX, IDC_EDIT2, m_num1);
	DDX_Text(pDX, IDC_EDIT3, m_name2);
	DDX_Text(pDX, IDC_EDIT4, m_price2);
	//DDX_Text(pDX, IDC_EDIT5, m_num2);
	DDX_Text(pDX, IDC_EDIT6, m_num1);
	DDX_Text(pDX, IDC_EDIT2, m_num2);
	DDX_Text(pDX, IDC_EDIT5, m_num3);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAddDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CAddDlg 诊断

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg 消息处理程序


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
		//初始化下拉框
	CInfoFile file;
	//file 读对象
	file.ReadDocline();
	for (auto it : file.ls)
	{
		//遍历程序容器 容器名称放入下拉框
		m_combo.AddString((CString)(it.name.c_str()));

		//默认选中第一个
		m_combo.SetCurSel(0);
		//UpdateData(false);
		OnCbnSelchangeCombo1();
	}
	file.ls.clear(); //清空list的内容
}


void CAddDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
		//切换程序

	//先获取所选索引
	int index = m_combo.GetCurSel();

	//索引获取名称
	CString name;
	m_combo.GetLBText(index, name);

	//获取程序价格和库存 显示到控件中
		//初始化下拉框
	CInfoFile file;
	//file 读对象
	file.ReadDocline();
	for (auto it : file.ls)
	{
		if ((CString)it.name.c_str() == name)
		{
			m_price1 = it.price;
			m_num1 = it.num;
			//同步到控件
			UpdateData(false);
			break;
		}
	}
	file.ls.clear(); //清空list的内容
}


void CAddDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加程序功能的实现

	//最新数据
	UpdateData(true);
	if (m_num1 <= 0)
	{
		MessageBox(L"添加个数小于零!!!");
		return;
	}

	//获取你要添加的程序名称
	CString name;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index,name);

	CInfoFile file;
	//file 读对象
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ((CString)it->name.c_str() == name)
		{

			//添加库存
			it->num += m_num2;
			m_num1 = it->num;
			m_num2 = 0;
			UpdateData(false);	
			MessageBox(L"添加成功");
			break;
		}
	}
	file.WirteDocline();

	file.ls.clear(); //清空list的内容

}


void CAddDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_num2 = 0;
	UpdateData(false);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	//添加新程序
	//验证有效性
	if (m_name2.IsEmpty() || m_num3 <= 0 || m_price2 <= 0)
	{
		MessageBox(L"输入信息有误！！！");
		return;
	}
	CInfoFile file;
	//file 读对象
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if ((CString)it->name.c_str() == m_name2)
		{
			MessageBox(L"程序已存在！！！");
			m_name2.Empty();
			m_num3 = 0;
			m_price2 = 0;
			UpdateData(false);
			return;
		}
	}

	file.Addline(m_name2, m_num3, m_price2);
	file.WirteDocline();//同步到文件中
	MessageBox(L"新程序添加成功");

	//同步到左侧下拉框
	m_combo.InsertString(0, m_name2);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();//同步所选

	//清空添加的数据
	m_name2.Empty();
	m_num3 = 0;
	m_price2 = 0;
	UpdateData(false);
}


void CAddDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空添加的数据
	m_name2.Empty();
	m_num3 = 0;
	m_price2 = 0;
	UpdateData(false);
}
