// CRunDlg.cpp: 实现文件
//

#include "pch.h"
#include "Jutze_Func.h"
#include "CRunDlg.h"
#include "ALL_Func.h"


// CRunDlg

IMPLEMENT_DYNCREATE(CRunDlg, CFormView)

CRunDlg::CRunDlg()
	: CFormView(IDD_DIALOG_RUN)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CRunDlg::~CRunDlg()
{
}

void CRunDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_RUN, m_run);
}

BEGIN_MESSAGE_MAP(CRunDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CRunDlg::OnBnClickedButtonRun)
END_MESSAGE_MAP()


// CRunDlg 诊断

#ifdef _DEBUG
void CRunDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CRunDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRunDlg 消息处理程序


void CRunDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_font.CreatePointFont(150, L"");
	m_run.SetFont(&m_font);

}


void CRunDlg::OnBnClickedButtonRun()
{
	// TODO: 在此添加控件通知处理程序代码
	//TRACE("RUN");
	//TRACE("RUN");//debug可用于打印输出
	Xml_Test();
	//xml_Read_Write();
	MessageBox(L"RUN");
}
