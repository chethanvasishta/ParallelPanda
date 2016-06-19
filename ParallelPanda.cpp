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

int _tmain(int argc, _TCHAR* argv[])
{
	ParseArguments(argc, argv);
	Panda panda;
	panda.Initialize();	
	panda.Run();
	// once we have our panda initialized, we will start creating schedules and running them.
	return 0;
}

