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
	virtual void OnFinalRelease();
	afx_msg void OnBnClickedButtonXmlReadWrite();
private:
	CButton m_Xml_Read_Write;
	CButton m_open;
public:
	afx_msg void OnBnClickedButtonOpen();
private:
	CButton m_close;
public:
	afx_msg void OnBnClickedButtonClose();
private:
	CButton m_chrono;
public:
	afx_msg void OnBnClickedButtonChrono();
private:
	CButton m_json;
public:
	afx_msg void OnBnClickedButtonJson();
private:
	CButton m_lambda;
public:
	afx_msg void OnBnClickedButtonLambda();
private:
	CButton m_writefile;
public:
	afx_msg void OnBnClickedButtonWritefile();
private:
	CButton m_codeCvt;
public:
	afx_msg void OnBnClickedButtonCodecvt();

private:
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
};


