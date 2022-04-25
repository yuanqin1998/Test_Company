
// JutzeEditCtrlDlg.h: 头文件
//

#pragma once


// CJutzeEditCtrlDlg 对话框
class CJutzeEditCtrlDlg : public CDialogEx
{
// 构造
public:
	CJutzeEditCtrlDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JUTZEEDITCTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
private:
	CEdit m_edit_1;
	CEdit m_edit_2;
	virtual void OnOK();
	CString m_Edit_3;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
