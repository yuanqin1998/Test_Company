#pragma once



// CRunDlg 窗体视图

class CRunDlg : public CFormView
{
	DECLARE_DYNCREATE(CRunDlg)

protected:
	CRunDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CRunDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RUN };
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
	virtual void OnInitialUpdate();
private:
	//CString m_run;
	CFont m_font;
	CButton m_run;
public:
	afx_msg void OnBnClickedButtonRun();
};


