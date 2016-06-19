#include "stdafx.h"
#include "Panda.h"
#include "Options.h"
#include "WrapperManager.h"

void Panda::Run()
{
	// errors from any of these functions?
	PandaStartProgram();
	while (MoreSchedules())
	{
		PandaTestRun();
	}
	PandaFinish();
}

Error Panda::LoadModule(std::string moduleName, HMODULE* moduleHandlePtr)
{
	if (moduleHandlePtr == NULL)
		return PP_NULL_ARG;
	*moduleHandlePtr = LoadLibraryA(moduleName.c_str());
	if (*moduleHandlePtr == NULL)
	{
		std::cout << "Couldn't load target module " << moduleName << std::endl;
		return PP_MODULE_NOT_FOUND;
	}
	return ShimWrappers(*moduleHandlePtr);;
}

Error Panda::LoadProcAddress(HMODULE hModule, FARPROC* procPtr)
{
	if (hModule == NULL || procPtr == NULL)
		return PP_NULL_ARG;

	FARPROC testRunProc = GetProcAddress(hModule, "ChessTestRun"); // TODO: Fix this!
	if (testRunProc == NULL)
	{
		cout << "Couldn't find PandaTestRun()" << endl;
		return PP_PROC_NOT_FOUND;
	}
	*procPtr = testRunProc;
	return PP_NO_ERROR;
}

Error Panda::ShimWrappers(HMODULE moduleHandle)
{
	return WrapperManager::GetInstance().ShimWrappers(moduleHandle);
}

Error Panda::Initialize()
{
	Error err = PP_NO_ERROR;
	if (err = LoadModule(gOptions.m_targetModuleName, &m_targetModule))
		return err;
	if (err = LoadProcAddress(m_targetModule, &m_testRunProc))
		return err;
	return PP_NO_ERROR;
}

Error Panda::PandaStartProgram()
{
	// attach to the program, and catch hold of wrappers
	return PP_NO_ERROR;
}

Error Panda::PandaTestRun()
{
	m_testRunProc();
	return PP_NO_ERROR;
}

Error Panda::PandaFinish()
{

	return PP_NO_ERROR;
}

bool Panda::MoreSchedules()
{
	// Generate the next schedule here
	return true;
}


