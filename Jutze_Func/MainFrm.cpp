
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Jutze_Func.h"
#include "InfoFile.h"
#include "CDisplayView.h"
#include "CSelectView.h"
#include "CUserDlg.h"
#include "CDlgSell.h"
#include "CInfoDlg.h"
#include "CAddDlg.h"
#include "CRunDlg.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	//ON_MESSAGE响应的是自定义消息
	//产生NM_X消息，自动调用OnMyChange函数
	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)

	ON_COMMAND(ID_32771, &CMainFrame::On32771)
	ON_COMMAND(ID_32772, &CMainFrame::On32772)
	ON_COMMAND(ID_32773, &CMainFrame::On32773)
	ON_COMMAND(ID_32774, &CMainFrame::On32774)
	ON_COMMAND(ID_32775, &CMainFrame::On32775)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
	Sleep(100);
	//终止子进程  
	TerminateProcess(pi.hProcess, 300);
	// 等待子进程结束
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//设置图标，IDI_ICON_WIN为图标资源ID，此为WINAPI函数
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_WIN));

	//设置副标题
 	SetTitle(TEXT("2022-04-28"));

	//设置窗口的位置和大小：CWnd::MoveWindow
	//0, 0, 起点坐标x和y
	//800, 500, 窗口宽度和高度
	MoveWindow(0, 0, 1000, 600);
	//将窗口移动到屏幕中央，CWnd::CenterWindow
	CenterWindow();

	//启动AdapterPI（启动之前此软件不在运行）<------------------
	char cWindowsDirectory[MAX_PATH];
	//LPTSTR 与 wchar_t* 等价(Unicode环境下)  
	//LPTSTR cWinDir = new TCHAR[MAX_PATH];
	LPTSTR cModuleDir = new TCHAR[MAX_PATH];
	//GetCurrentDirectory(MAX_PATH, cWinDir);
	GetModuleFileName(NULL, cModuleDir, MAX_PATH);

	CString strEXEPath = cModuleDir;
	int nPos = strEXEPath.ReverseFind(_T('\\'));
	strEXEPath = strEXEPath.Left(nPos + 1);
	strEXEPath += L".\\..\\..\\QT\\release\\AdapterPI.exe";

	//LPTSTR sConLin = wcscat(cWinDir, L"\\..\\Debug\\another.exe a b c d");
	//LPTSTR sConLin = wcscat(strEXEPath.GetBuffer(), L".\\..\\..\\QT\\release\\AdapterPI.exe");

	//char chPath[301];
	//::GetCurrentDirectory(300, (LPTSTR)chPath);//得到当前目录
	//char path[200] = "\\123.exe";
	//strcat(chPath, path);

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	si.cb = sizeof(si);
	si.dwFlags = STARTF_FORCEONFEEDBACK;

	try
	{
		if (CreateProcess(strEXEPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			AfxMessageBox(_T("AdapterPI启动成功!"));
			//下面两行关闭句柄，解除本进程和新进程的关系，不然有可能不小心调用TerminateProcess函数关掉子进程  
			//CloseHandle(pi.hProcess);
			//CloseHandle(pi.hThread);
		}
	}
	catch (...)
	{
		AfxMessageBox(_T("AdapterPI启动失败! failed: %d"), GetLastError());
		HANDLE hProcess = GetCurrentProcess();//get current process
		TerminateProcess(hProcess, 0);         //close process
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	
	// 静态拆分窗口，1行2列，CSplitterWnd::CreateStatic
	m_spliter.CreateStatic(this, 1, 2);

	// 创建视图：CSplitterWnd::CreateView
	//0, 0 ： 放在第0行第0列的位置
	//RUNTIME_CLASS(CSelectView) ：需要头文件#include "SelectView.h"， CSelectView在SelectView.h中声明
	// CSize(250, 500)：指定视图宽度和高度
	//pContext ： 为OnCreateClient()最后一个形参
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(250, 600), pContext);

	//0, 1： 放在第0行第1列的位置
	//CDispalyView，需要头文件#include "DispalyView.h"
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(750, 600), pContext);

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	return TRUE;
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext   Context;
	if (wParam == NM_A)
	{
		//MessageBox(L"个人信息界面挂载");
		//界面挂载
		Context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(750, 600), &Context);
		CUserDlg* pNewView = (CUserDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);

	}
	else if (wParam == NM_B)
	{
		//MessageBox(L"程序管理界面挂载");
		Context.m_pNewViewClass = RUNTIME_CLASS(CDlgSell);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDlgSell), CSize(750, 600), &Context);
		CDlgSell* pNewView = (CDlgSell*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_C)
	{
		//MessageBox(L"程序信息界面挂载");
		Context.m_pNewViewClass = RUNTIME_CLASS(CInfoDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CInfoDlg), CSize(750, 600), &Context);
		CInfoDlg* pNewView = (CInfoDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);

	}
	else if (wParam == NM_D)
	{
		//MessageBox(L"程序添加界面挂载");
		Context.m_pNewViewClass = RUNTIME_CLASS(CAddDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAddDlg), CSize(750, 600), &Context);
		CAddDlg* pNewView = (CAddDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);

	}
	else if (wParam == NM_E)
	{
		//MessageBox(L"程序运行界面挂载");
		Context.m_pNewViewClass = RUNTIME_CLASS(CRunDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CRunDlg), CSize(750, 600), &Context);
		CRunDlg* pNewView = (CRunDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	return 0;
}


void CMainFrame::On32771()
{
	// TODO: 在此添加命令处理程序代码
	//退出按钮
	exit(0);
}


void CMainFrame::On32772()
{
	// TODO: 在此添加命令处理程序代码
	//个人信息
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
}


void CMainFrame::On32773()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);

}



void CMainFrame::On32774()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);

}


void CMainFrame::On32775()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);

}
