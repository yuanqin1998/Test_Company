﻿#pragma once


// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_pwd;
	afx_msg void OnBnClickedButtonLoginSure();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonLoginCancel();
	virtual void OnOK();
	afx_msg void OnClose();
};
