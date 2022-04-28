
// Jutze_FuncView.cpp: CJutzeFuncView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Jutze_Func.h"
#endif

#include "Jutze_FuncDoc.h"
#include "Jutze_FuncView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJutzeFuncView

IMPLEMENT_DYNCREATE(CJutzeFuncView, CView)

BEGIN_MESSAGE_MAP(CJutzeFuncView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CJutzeFuncView 构造/析构

CJutzeFuncView::CJutzeFuncView() noexcept
{
	// TODO: 在此处添加构造代码

}

CJutzeFuncView::~CJutzeFuncView()
{
}

BOOL CJutzeFuncView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CJutzeFuncView 绘图

void CJutzeFuncView::OnDraw(CDC* /*pDC*/)
{
	CJutzeFuncDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CJutzeFuncView 打印

BOOL CJutzeFuncView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CJutzeFuncView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CJutzeFuncView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CJutzeFuncView 诊断

#ifdef _DEBUG
void CJutzeFuncView::AssertValid() const
{
	CView::AssertValid();
}

void CJutzeFuncView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJutzeFuncDoc* CJutzeFuncView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJutzeFuncDoc)));
	return (CJutzeFuncDoc*)m_pDocument;
}
#endif //_DEBUG


// CJutzeFuncView 消息处理程序
