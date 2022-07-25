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
	DDX_Control(pDX, IDC_BUTTON_Xml_Read_Write, m_Xml_Read_Write);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_open);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_close);
	DDX_Control(pDX, IDC_BUTTON_CHRONO, m_chrono);
	DDX_Control(pDX, IDC_BUTTON_JSON, m_json);
	DDX_Control(pDX, IDC_BUTTON_LAMBDA, m_lambda);
	DDX_Control(pDX, IDC_BUTTON_WRITEFILE, m_writefile);
	DDX_Control(pDX, IDC_BUTTON_CODECVT, m_codeCvt);
}

BEGIN_MESSAGE_MAP(CRunDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CRunDlg::OnBnClickedButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_Xml_Read_Write, &CRunDlg::OnBnClickedButtonXmlReadWrite)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CRunDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CRunDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_CHRONO, &CRunDlg::OnBnClickedButtonChrono)
	ON_BN_CLICKED(IDC_BUTTON_JSON, &CRunDlg::OnBnClickedButtonJson)
	ON_BN_CLICKED(IDC_BUTTON_LAMBDA, &CRunDlg::OnBnClickedButtonLambda)
	ON_BN_CLICKED(IDC_BUTTON_WRITEFILE, &CRunDlg::OnBnClickedButtonWritefile)
	ON_BN_CLICKED(IDC_BUTTON_CODECVT, &CRunDlg::OnBnClickedButtonCodecvt)
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
	m_Xml_Read_Write.SetFont(&m_font);
	m_open.SetFont(&m_font);
	m_close.SetFont(&m_font);
	m_chrono.SetFont(&m_font);
	m_json.SetFont(&m_font);
	m_lambda.SetFont(&m_font);
	m_writefile.SetFont(&m_font);
	m_codeCvt.SetFont(&m_font);
}

void CRunDlg::OnFinalRelease()
{
	// TODO: 在此添加专用代码和/或调用基类
	FreeConsole();//释放控制台资源
	CFormView::OnFinalRelease();
}

void CRunDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	::AllocConsole();//打开控件台资源
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w+t", stdout);//申请写
	//freopen("CONOUT$", "w+t", stdout);
}


void CRunDlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	fclose(stdout);
	FreeConsole();//释放控制台资源
}

void CRunDlg::OnBnClickedButtonRun()
{
	// TODO: 在此添加控件通知处理程序代码
	//TRACE("RUN");//debug可用于打印输出
	Xml_Test();
	//MessageBox(L"RUN");
}

void CRunDlg::OnBnClickedButtonXmlReadWrite()
{
	// TODO: 在此添加控件通知处理程序代码
	xml_Read_Write();
}

void CRunDlg::OnBnClickedButtonChrono()
{
	// TODO: 在此添加控件通知处理程序代码
	Chrono_Test();
}


void CRunDlg::OnBnClickedButtonJson()
{
	// TODO: 在此添加控件通知处理程序代码
#pragma region Json_Array
	CAtlString strShopfloorDir = L"URL";
	CAtlString strStationCode = L"StationCode";

	CAtlString strTestResult = L"OK";
	int nNGPart = 0, nFCPart = 0;
	if (nNGPart > 0)
	{
		strTestResult = L"Fail";
	}
	int aoinfo_BoardBarcodeList_size = 9;
	CAtlString strBigBarcode = L"null";
	if (aoinfo_BoardBarcodeList_size > 0)
	{
		strBigBarcode = L"Pa120405244";
	}
	const int PanelCount = 8;
	//载具条码
	CAtlString strBindData = L"NULL";
	if (aoinfo_BoardBarcodeList_size > 0)
	{
		strBindData = L"BindData";
	}

	//操作员
	std::string strTester = "SFCAUTO";

	//当前时间（chrono）
	__time64_t clockNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tm timeNow;
	_localtime64_s(&timeNow, &clockNow);
	char time_msg[32];
	memset(time_msg, '\0', 32);
	sprintf_s(time_msg, "%04d-%02d-%02d %02d:%02d:%02d",
		timeNow.tm_year + 1900,
		timeNow.tm_mon + 1,
		timeNow.tm_mday,
		timeNow.tm_hour,
		timeNow.tm_min,
		timeNow.tm_sec);
	string strTest_time = (string)time_msg;
	Json::Value SendData;
	if (strShopfloorDir != L"")
	{
		//Json::Value SendData;
		SendData["sn:"] = Json::Value(CW2A(strBigBarcode.GetString()));
		SendData["StationCode:"] = Json::Value(CW2A(strStationCode.GetString()));
		SendData["PanelCount:"] = Json::Value(PanelCount);
		SendData["TestResult:"] = Json::Value(CW2A(strTestResult.GetString()));
		SendData["bindData:"] = Json::Value(CW2A(strBindData.GetString()));
		if (PanelCount > 0)
		{
			for (int i = 1; i < PanelCount; i++)
			{
				//strPanelArray[i] = i;
				//strBadMark[i] = "0";
				SendData["panelArray:"].append(i);
				SendData["BadMark:"].append(0);
			}
		}
		wstring PcbCode = L"3190Xasd";
		const char* PCBCode = (_bstr_t)PcbCode.c_str();
		cout << PCBCode << endl;
		SendData["tester:"] = Json::Value(strTester.c_str());
		SendData["test_time:"] = Json::Value(strTest_time.c_str());
		SendData["PCBCode:"] = PCBCode;
	}
	Json::StreamWriterBuilder writerBuilder;
	std::unique_ptr<Json::StreamWriter> json_write(writerBuilder.newStreamWriter());
	std::ostringstream ss;
	json_write->write(SendData, &ss);
	std::string strContent = ss.str();
	//std::cout << strContent << std::endl;
	cout << "原Json数组" << SendData << endl;
	cout << "Json_String" << strContent << endl;
	Json_Array(strContent);
#pragma endregion
}


void CRunDlg::OnBnClickedButtonLambda()
{
	// TODO: 在此添加控件通知处理程序代码
#pragma region Test_lambda_sort
	const int len = 4;
	int num_in[len];
	int* num = Test_lambda_sort(num_in);
	//lambda示例 打印输出
	auto display =
		[num, len]() -> void {
		for (int i = 0; i < len; i++)
		{
			cout << *(num + i) << " ";
		}
		// cout << *num << " "; 
	};
	display();
#pragma endregion
}


void CRunDlg::OnBnClickedButtonWritefile()
{
	// TODO: 在此添加控件通知处理程序代码
	Write_File();
}


void CRunDlg::OnBnClickedButtonCodecvt()
{
	// TODO: 在此添加控件通知处理程序代码
	String_WString_CAtlString();
}
