// ParallelPanda.cpp : Defines the entry point for the console application.
//



// ConcurrencyBugFinder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "Panda.h"
#include "Options.h"
using namespace std;

FARPROC GetTestRunFunction(_TCHAR* fileName)
{
	std::string fileNameStr = "";
	HMODULE module = LoadLibraryA(fileNameStr.c_str());
	if (module == NULL)
	{
		cout << "Couldn't load library " << fileName << endl;
		exit(0);
	}
	FARPROC testRunProc = GetProcAddress(module, "PandaTestRun");
	if (testRunProc == NULL)
	{
		cout << "Couldn't find PandaTestRun()" << endl;
		exit(0);
	}
	return testRunProc;
}

int _tmain(int argc, _TCHAR* argv[])
{
	ParseArguments(argc, argv);
	Panda panda;
	panda.Initialize();	
	// once we have our panda initialized, we will start creating schedules and running them.
	return 0;
}

