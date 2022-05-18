#include "pch.h"
#include "ALL_Func.h"


void Xml_Test()
{
	//const std::string msg("<?xml version=\"1.0\" encoding=\"utf-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><soap:Body><OnProcessWorkResponse xmlns=\"http://tempuri.org/\"><OnProcessWorkResult>{\"Success\":false,\"Message\":\"工序：[AOI检验]未在[工序配置管理]配置！\",\"Data\":\"0\"}</OnProcessWorkResult></OnProcessWorkResponse></soap:Body></soap:Envelope>");
	//const std::string msg("<?xml version=\"1.0\" encoding=\"utf - 8\"?><string xmlns = \"http://tempuri.org/\"> {\"Success\":false,\"Message\":\"基板：[HJRQWBPD034781]在上一个工序：[固晶]未找到作业记录!\",\"Data\":\"0\"}</string>");
	const std::string msg("<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\"><SOAP-ENV:Body SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:NS1=\"urn:WebServiceInf-IWebService\"><NS1:CheckSPIAOIRouteResponse><return xsi:type = \"xsd:string\">NG这里是错误信息</return></NS1:CheckSPIAOIRouteResponse></SOAP-ENV:Body></SOAP-ENV:Envelope>");
	boost::property_tree::ptree ptParse;
	std::istringstream jsonIStream;
	jsonIStream.str(msg);
	boost::property_tree::xml_parser::read_xml(jsonIStream, ptParse);

	//auto m = ptParse.get<Json::Value>("soap:Envelope.soap:Body.OnProcessWorkResponse.OnProcessWorkResult");

	//auto j_result = ptParse.get<Json::Value>("SOAP-ENV:Envelope.SOAP-ENV:Body.NS1:CheckSPIAOIRouteResponse.return");
	//string Message = j_result["Message"].asCString();

	string j_result = ptParse.get<string>("SOAP-ENV:Envelope.SOAP-ENV:Body.NS1:CheckSPIAOIRouteResponse.return");
	cout << j_result << endl;
	TRACE(j_result.c_str());
}

void xml_Read_Write()
{
	const std::string msg("<soapenv:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:urn=\"urn:WebServiceInf-IWebService\"><soapenv:Header/><soapenv:Body><urn:CommitSPIAOIData soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"></urn:CommitSPIAOIData></soapenv:Body></soapenv:Envelope>");
	//SOAP-ENV:Envelope.SOAP-ENV:Body.NS1:CheckSPIAOIRouteResponse.return
	boost::property_tree::ptree ptParse;
	std::istringstream jsonIStream;
	std::ostringstream jsonOStream;
	jsonIStream.str(msg);
	cout << "输入的xml:\n" << jsonIStream.str() << endl;
	boost::property_tree::xml_parser::read_xml(jsonIStream, ptParse);

	//read_xml("info.xml", ptParse, boost::property_tree::xml_parser::trim_whitespace, std::locale());
	//增加节点(位置，节点名、值、属性和值)

	//节点头：
	std::string Xml_front = "soapenv:Envelope.soapenv:Body.urn:CommitSPIAOIData."; //加 . 增加节点
	//boost::property_tree::ptree Xml_root = ptParse.get_child("soapenv:Envelope.soapenv:Body.urn:CommitSPIAOIData");
	std::string sn = "1WMHP86RA02185";
	//增加节点 内容设置为(string)sn   :::<sn>1WMHP86RA02185</sn>
	ptParse.add((Xml_front + "sn"), sn);

	//节点属性表 
	std::string Xml_back = ".<xmlattr>.xsi:type";
	std::string Xml_int = "xsi:type=\"xsd:int\"";
	std::string Xml_string = "xsi:type=\"xsd:string\"";
	//增加节点属性 ：<user account="0610">temp</user>
	ptParse.put((Xml_front + "sn" + Xml_back), Xml_string);


	//删除节点(位置)
	//auto nodes = ptParse.get_child("SOAP-ENV:Envelope.SOAP-ENV:Body.NS1:CheckSPIAOIRouteResponse");
	//ptree::iterator it = ptParse.get_child("SOAP-ENV:Envelope.SOAP-ENV:Body.NS1:CheckSPIAOIRouteResponse").begin();
	////it++;
	//nodes.erase(it);

	////修改节点值
	//ptParse.put("string.MessageBoxTitle", "不可更新");
	////修改节点属性值
	//ptParse.put("string.MessageBoxTitle.<xmlattr>.extraCmd", "file");


	/*写入,缩进,编码*/
	boost::property_tree::xml_writer_settings<string> settings =
		boost::property_tree::xml_writer_make_settings<string>('\t', 1);
	boost::property_tree::xml_parser::write_xml(jsonOStream, ptParse, settings);
	cout << "\n输出的xml:\n" << jsonOStream.str().c_str() << endl;
}

void Chrono_Test()
{
	//当前时间（chrono）
	__time64_t clockNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	tm timeNow;
	_localtime64_s(&timeNow, &clockNow);
	char time_msg[32];
	memset(time_msg, '\0', 32);
	sprintf_s(time_msg, "%04d/%02d/%02d %02d:%02d:%02d",
		timeNow.tm_year + 1900,
		timeNow.tm_mon + 1,
		timeNow.tm_mday,
		timeNow.tm_hour,
		timeNow.tm_min,
		timeNow.tm_sec);
	string time = (string)time_msg;
	cout << time << endl;
	TRACE(time.c_str());
}

std::vector<int> findSame(const std::vector<int>& nLeft, const std::vector<int>& nRight)
{
	std::vector<int> nResult;
	for (std::vector<int>::const_iterator nIterator = nLeft.begin(); nIterator != nLeft.end(); nIterator++)
	{
		if (std::find(nRight.begin(), nRight.end(), *nIterator) != nRight.end())
			nResult.push_back(*nIterator);
	}

	return nResult;
}

void Json_Array(string Array_in)
{
	cout << "输入的字符串" << Array_in << endl;

	Json::CharReaderBuilder build;
	Json::CharReader* reader(build.newCharReader());
	Json::Value root;
	JSONCPP_STRING errs;
	reader->parse(Array_in.c_str(), Array_in.c_str() + std::strlen(Array_in.c_str()), &root, &errs);
	cout << "读取的Json数组" << root << endl;
}

int* Test_lambda_sort(int* num)
{
	num[0] = 4;
	num[1] = 2;
	num[2] = 3;
	num[3] = 1;
	//对 a 数组中的元素进行排序
	sort(num, num + 4, [=](int x, int y) -> bool { return x > y; });
	return num;
}

void Write_File()
{
	CStdioFile File_1;
	CAtlString strLogFileName = _T("file.TXT");
	if (File_1.Open(strLogFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		CAtlString strBuffer_1;
		strBuffer_1.Format(_T("%s\n%d\n"),
			_T("qinyuan"),//机种名称
			15//拼板数量
		);
		File_1.WriteString(strBuffer_1);
	}
	File_1.Close();
}

void String_WString_CAtlString()
{
	//CodeConvert对象
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	//log
	std::string str_msg("");
	std::wstring wstr_msg(L"");

	std::wstring Test = L"1231231231231";
	str_msg = conv.to_bytes(Test);
	wstr_msg = conv.from_bytes(str_msg);
	cout << str_msg << endl;
	wcout << wstr_msg << endl;

	// string = CW2A(wstring) 
	CAtlString sn_1 = L"1WMHP86RA02185";
	cout << CW2A(sn_1.GetString()) << endl;
}
