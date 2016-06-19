#include "stdafx.h"
#include "Panda.h"

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

Error Panda::Initialize()
{
	// m_targetModule = loadlibrary using options target module name
	return PP_NO_ERROR;
}

Error Panda::PandaStartProgram()
{
	// attach to the program, and catch hold of wrappers
	return PP_NO_ERROR;
}

Error Panda::PandaTestRun()
{
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


