
// JutzeView.cpp: CJutzeView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Jutze.h"
#endif

#include "JutzeDoc.h"
#include "JutzeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJutzeView

IMPLEMENT_DYNCREATE(CJutzeView, CView)

BEGIN_MESSAGE_MAP(CJutzeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CJutzeView 构造/析构

CJutzeView::CJutzeView() noexcept
{
	// TODO: 在此处添加构造代码

}

CJutzeView::~CJutzeView()
{
}

BOOL CJutzeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CJutzeView 绘图

void CJutzeView::OnDraw(CDC* pDC)
{
	CJutzeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	pDC->TextOutW(610, 260, TEXT("为了部落！！！"));

}


// CJutzeView 打印

BOOL CJutzeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CJutzeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CJutzeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CJutzeView 诊断

#ifdef _DEBUG
void CJutzeView::AssertValid() const
{
	CView::AssertValid();
}

void CJutzeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJutzeDoc* CJutzeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJutzeDoc)));
	return (CJutzeDoc*)m_pDocument;
}
#endif //_DEBUG


// CJutzeView 消息处理程序

void CJutzeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonDown(nFlags, point);
	CString str;
	str.Format(TEXT("X = %d,Y = %d"), point.x, point.y);
	MessageBox(str);
}
