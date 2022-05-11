// CInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "Jutze_Func.h"
#include "CInfoDlg.h"
#include "InfoFile.h"


// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)

CInfoDlg::CInfoDlg()
	: CFormView(IDD_DIALOG_INFO)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_STATIC_TOP, m_text);
}

BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
END_MESSAGE_MAP()


// CInfoDlg 诊断

#ifdef _DEBUG
void CInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoDlg 消息处理程序


void CInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 设置扩展风格
	//LVS_EX_FULLROWSELECT选中整行，LVS_EX_GRIDLINES网格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT
		| LVS_EX_GRIDLINES);
		//| LVS_EX_CHECKBOXES);
		//| LVS_EX_HEADERDRAGDROP);可拖拽

	// 初始化表头
	CString field[] = { _T("程序ID"), _T("程序名称"), _T("程序价格"), _T("库存数量") };
	for (int i = 0; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 120);
	}

	//需要包含#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //读取程序信息

	//添加数据
	int i = 0;
	CString str;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		str.Format(_T("%d"), it->id);
		m_list.InsertItem(i, str);
		int column = 1;
		m_list.SetItemText(i, column++, (CString)it->name.c_str());
		str.Format(_T("%d"), it->price);
		m_list.SetItemText(i, column++, str);
		str.Format(_T("%d"), it->num);
		m_list.SetItemText(i, column++, str);
		i++;
	}
	m_font_1.CreatePointFont(150, L"");
	m_list.SetFont(&m_font_1);
	m_font_2.CreatePointFont(160, L"");
	m_text.SetFont(&m_font_2);
}
