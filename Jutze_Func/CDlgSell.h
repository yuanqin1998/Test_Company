#pragma once



// CDlgSell 窗体视图

class CDlgSell : public CFormView
{
	DECLARE_DYNCREATE(CDlgSell)

protected:
	CDlgSell();           // 动态创建所使用的受保护的构造函数
	virtual ~CDlgSell();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELL };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo;
private:
	int m_price;
	int m_left;
	int m_num;
public:
	CString m_sellinfo;
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeComboSell();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};


