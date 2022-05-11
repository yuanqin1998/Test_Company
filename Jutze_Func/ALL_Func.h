#pragma once
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>//BOOST_FOREACH
#include "json/json.h"
#include <iostream>
//#include <windows.h>
#include <wchar.h>
#include <vector>
#include <afx.h>
#include <atlstr.h>
#include <comdef.h>

#include <chrono>
using namespace boost::property_tree;
using namespace std;

#pragma comment(lib,"jsoncpp.lib")

void Xml_Test();
void xml_Read_Write();