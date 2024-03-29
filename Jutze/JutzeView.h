﻿
// JutzeView.h: CJutzeView 类的接口
//

#pragma once


class CJutzeView : public CView
{
protected: // 仅从序列化创建
	CJutzeView() noexcept;
	DECLARE_DYNCREATE(CJutzeView)

// 特性
public:
	CJutzeDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CJutzeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // JutzeView.cpp 中的调试版本
inline CJutzeDoc* CJutzeView::GetDocument() const
   { return reinterpret_cast<CJutzeDoc*>(m_pDocument); }
#endif

