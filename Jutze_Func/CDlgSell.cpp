// CDlgSell.cpp: 实现文件
//

#include "pch.h"
#include "Jutze_Func.h"
#include "CDlgSell.h"
#include "InfoFile.h"


// CDlgSell

IMPLEMENT_DYNCREATE(CDlgSell, CFormView)

CDlgSell::CDlgSell()
	: CFormView(IDD_DIALOG_SELL)
	, m_price(0)
	, m_left(0)
	, m_num(0)
	, m_sellinfo(_T(""))
{

}

CDlgSell::~CDlgSell()
{
}

void CDlgSell::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SELL, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_left);
	DDX_Text(pDX, IDC_EDIT3, m_num);
	DDX_Text(pDX, IDC_EDIT4, m_sellinfo);
}

BEGIN_MESSAGE_MAP(CDlgSell, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO_SELL, &CDlgSell::OnCbnSelchangeComboSell)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgSell::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgSell::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDlgSell 诊断

#ifdef _DEBUG
void CDlgSell::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDlgSell::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDlgSell 消息处理程序


void CDlgSell::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//初始化销售订单

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
		OnCbnSelchangeComboSell();
	}
	file.ls.clear(); //清空list的内容
}


void CDlgSell::OnCbnSelchangeComboSell()
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
			m_price = it.price;
			m_left = it.num;
			//同步到控件
			UpdateData(false);
			break;
		}
	}
	file.ls.clear(); //清空list的内容
}


void CDlgSell::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//购买功能
	if (m_num <= 0)
	{
		MessageBox(TEXT("购买数量要大于零"));
		return;
	}
	//删除数量不能大于库存
	else if (m_num > m_left)
	{
		MessageBox(TEXT("购买数量要大于库存"));
		return;
	}

	//购买
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);

	CInfoFile file;
	//file 读对象
	file.ReadDocline();
	//用指针才能修改list链表内容
	for (list<msg>::iterator it= file.ls.begin(); it != file.ls.end(); it++)
	{
		if (it->name.c_str() == name)
		{
			//同步库存
			it->num -= m_num;
			m_left = it->num;
			//告诉用户具体信息
			CString str;
			str.Format(_T("程序：%s\r\n单价：%ld\r\n个数：%ld\r\n总价：%ld元"), name, m_price, m_num, m_price* m_num);
			m_sellinfo = str;
			//同步到控件
			UpdateData(FALSE);
			MessageBox(_T("购买成功！！！"));
			//break;
		}
	}
	//数据写入文件；
	file.WirteDocline();

	//清空数据
	file.ls.clear(); //清空list的内容
	m_num = 0;
	m_sellinfo.Empty();
	UpdateData(FALSE);

}


void CDlgSell::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//取消按钮
	m_num = 0;
	UpdateData(false);
	//默认选中第一个
	m_combo.SetCurSel(0);
	OnCbnSelchangeComboSell();
}
