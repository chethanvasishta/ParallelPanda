#include "stdafx.h"
#include "Options.h"
#include <iostream>
using namespace std;

Options gOptions; // make it thread safe

Options::Options()
{
	m_preemptionBound = 1; // default value
}

std::string WCharToStdString(_TCHAR* str)
{
	std::wstring wstr = str;
	return std::string(wstr.begin(), wstr.end());
}

Error ParseArguments(int argc, _TCHAR* argv[])
{
	if(argc < 2)
	{
		cout << "Usage: pp.exe yourdll.dll" << endl;
		return PP_ARG_ERROR;
	}
	gOptions.m_targetModuleName = WCharToStdString(argv[1]);
	// parse other arguments here
	return PP_NO_ERROR;
}