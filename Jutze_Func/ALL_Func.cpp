#include "pch.h"
#include "ALL_Func.h"


void Xml_Test()
{
	//const std::string msg("<?xml version=\"1.0\" encoding=\"utf-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"><soap:Body><OnProcessWorkResponse xmlns=\"http://tempuri.org/\"><OnProcessWorkResult>{\"Success\":false,\"Message\":\"����[AOI����]δ��[�������ù���]���ã�\",\"Data\":\"0\"}</OnProcessWorkResult></OnProcessWorkResponse></soap:Body></soap:Envelope>");
	//const std::string msg("<?xml version=\"1.0\" encoding=\"utf - 8\"?><string xmlns = \"http://tempuri.org/\"> {\"Success\":false,\"Message\":\"���壺[HJRQWBPD034781]����һ������[�̾�]δ�ҵ���ҵ��¼!\",\"Data\":\"0\"}</string>");
	const std::string msg("<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\"><SOAP-ENV:Body SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:NS1=\"urn:WebServiceInf-IWebService\"><NS1:CheckSPIAOIRouteResponse><return xsi:type = \"xsd:string\">NG�����Ǵ�����Ϣ</return></NS1:CheckSPIAOIRouteResponse></SOAP-ENV:Body></SOAP-ENV:Envelope>");
	boost::property_tree::ptree ptParse;
	std::istringstream jsonIStream;
	jsonIStream.str(msg);
	boost::property_tree::xml_parser::read_xml(jsonIStream, ptParse);

	//auto m = ptParse.get<Json::Value>("soap:Envelope.soap:Body.OnProcessWorkResponse.OnProcessWorkResult");

	//auto j_result = ptParse.get<Json::Value>("SOAP-ENV:Envelope.SOAP-ENV:Body.NS1:CheckSPIAOIRouteResponse.return");
	//string Message = j_result["Message"].asCString();

	string j_result = ptParse.get<string>("SOAP-ENV:Envelope.SOAP-ENV:Body.NS1:CheckSPIAOIRouteResponse.return");
	//cout << j_result << endl;
	TRACE(j_result.c_str());
}

void xml_Read_Write()
{
	//const std::string msg("<?xml version=\"1.0\" encoding=\"utf - 8\"?><string xmlns = \"http://tempuri.org/\"> {\"Success\":false,\"Message\":\"���壺[HJRQWBPD034781]����һ������[�̾�]δ�ҵ���ҵ��¼!\",\"Data\":\"0\"}</string>");
	//const std::string msg("<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\"><SOAP-ENV:Body SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:NS1=\"urn:WebServiceInf-IWebService\"><NS1:CheckSPIAOIRouteResponse><return xsi:type = \"xsd:string\">NG�����Ǵ�����Ϣ</return></NS1:CheckSPIAOIRouteResponse></SOAP-ENV:Body></SOAP-ENV:Envelope>");
	const std::string msg("<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\">"
		"<SOAP-ENV:Body SOAP-ENV:encodingStyle = \"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:NS1=\"urn:WebServiceInf-IWebService\">"
		"<NS1:CheckSPIAOIRouteResponse >"
		"<return xsi:type = \"xsd:string\">NG�����Ǵ�����Ϣ</return>"
		"</NS1:CheckSPIAOIRouteResponse >"
		"</SOAP-ENV:Body>"
		"</SOAP-ENV:Envelope>");
	//SOAP-ENV:Envelope.SOAP-ENV:Body.NS1:CheckSPIAOIRouteResponse.return
	boost::property_tree::ptree ptParse;
	std::istringstream jsonIStream;
	std::ostringstream jsonOStream;
	jsonIStream.str(msg);
	//cout << "�����xml:\n" << jsonIStream.str() << endl;
	TRACE("�����xml:%s\n",jsonIStream.str());
	boost::property_tree::xml_parser::read_xml(jsonIStream, ptParse);
	//read_xml("info.xml", ptParse, boost::property_tree::xml_parser::trim_whitespace, std::locale());
	//���ӽڵ�(λ�ã��ڵ�����ֵ�����Ժ�ֵ)
	ptParse.add("SOAP-ENV:Envelope.SOAP-ENV:Body.NS1:CheckSPIAOIRouteResponse.user", "temp");
	ptParse.put("SOAP-ENV:Envelope.SOAP-ENV:Body.NS1:CheckSPIAOIRouteResponse.user.<xmlattr>.account", "0610");

	//ɾ���ڵ�(λ��)
	auto nodes = ptParse.get_child("SOAP-ENV:Envelope.SOAP-ENV:Body.NS1:CheckSPIAOIRouteResponse");
	ptree::iterator it = ptParse.get_child("SOAP-ENV:Envelope.SOAP-ENV:Body.NS1:CheckSPIAOIRouteResponse").begin();
	//it++;
	nodes.erase(it);

	////�޸Ľڵ�ֵ
	//ptParse.put("string.MessageBoxTitle", "���ɸ���");
	////�޸Ľڵ�����ֵ
	//ptParse.put("string.MessageBoxTitle.<xmlattr>.extraCmd", "file");

	/*д��,����,����*/
	boost::property_tree::xml_writer_settings<string> settings =
	boost::property_tree::xml_writer_make_settings<string>('\t', 1, "utf-8");
	boost::property_tree::xml_parser::write_xml(jsonOStream, ptParse, settings);
	//cout << "\n�����xml:\n" << jsonOStream.str() << endl;
	TRACE("�����xml:%s\n", jsonOStream.str());

}