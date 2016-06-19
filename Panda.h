#ifndef Panda_H
#define Panda_H

#include "stdafx.h"
#include <Windows.h>
typedef unsigned int uInt;

class Panda // rename
{
public:
	Panda()	{ }

	void Run();
	Error Initialize(); // using gOptions
	Error PandaStartProgram();
	Error PandaTestRun();
	Error PandaFinish();
	bool MoreSchedules();

private:
	Error Panda::LoadModule(std::string moduleName, HMODULE* moduleHandlePtr);
	Error Panda::ShimWrappers(HMODULE moduleHandlePtr);
	Error Panda::LoadProcAddress(HMODULE hModule, FARPROC* procPtr);

private:
	HMODULE m_targetModule;
	FARPROC m_testRunProc;
	uInt m_maxPreemptions;
};

#endif // Panda_H