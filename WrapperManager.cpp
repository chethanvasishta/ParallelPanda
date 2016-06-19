#include "stdafx.h"
#include <Windows.h>
#include "WrapperManager.h"
#include "Win32Wrappers.h"
#include <Psapi.h> // Process Status API
#include <DbgHelp.h>
#include <memoryapi.h>

WrapperManager *WrapperManager::m_instance = NULL;
WrappersMap WrapperManager::m_wrappersMap;
bool WrapperManager::m_wrapperMapPopulated = false;

WrapperManager& WrapperManager::GetInstance() // make this thread safe
{
	if (m_instance == NULL)
	{
		m_instance = new WrapperManager();
	}
	assert(m_instance != NULL && "Singleton WrapperManager instance cannot be NULL!");
	return *m_instance;
}

Error WrapperManager::ShimWrappers(HMODULE hModule)
{
	if (hModule == NULL)
		return PP_NULL_ARG;

	// Get the module import table
	// virtual protect it to be read write
	// patch the pointers
	// virtual protect it to previous protection
	HANDLE hProcess = GetCurrentProcess();
	MODULEINFO moduleInfo;

	if(!GetModuleInformation(hProcess, hModule, &moduleInfo, sizeof(MODULEINFO))){
		cout << "Couldn't get module information!" << endl;
		return PP_SHIM_ERROR;
	}
	
	ULONG tableSize;
	PVOID tableBase = ImageDirectoryEntryToData(moduleInfo.lpBaseOfDll, TRUE, IMAGE_DIRECTORY_ENTRY_IAT, &tableSize);
	if (tableBase == NULL)
	{
		cout << "Couldn't get import address table information!" << endl;
		return PP_SHIM_ERROR;
	}

	PVOID protectedTableBase = tableBase;
	ULONG protectedTableSize = tableSize;
	DWORD oldProtection;
	if (!VirtualProtect(protectedTableBase, protectedTableSize, PAGE_READWRITE, &oldProtection))
	{
		cout << "Couldn't virtual protect table information during DLL shim!" << endl;
		return PP_SHIM_ERROR;
	}

	PVOID* procAddresses = (PVOID*)(tableBase);
	ULONG numProcs = (ULONG) (tableSize/sizeof(PVOID));

	for (unsigned int i = 0 ; i < numProcs ; ++i)
	{
		PVOID proc = procAddresses[i];
		if (proc == NULL)
			continue;
		WrappersMap::iterator itr = m_wrappersMap.find(proc);
		if (itr != m_wrappersMap.end())
		{
			procAddresses[i] = itr->second;
			itr->second = proc; // why are we doing this?
		}
	}

	if (!VirtualProtect(protectedTableBase, protectedTableSize, oldProtection, &oldProtection))
	{
		cout << "Couldn't virtual protect table information during DLL shim!" << endl;
		return PP_SHIM_ERROR;
	}
	return PP_NO_ERROR;
}

WrapperManager::WrapperManager()
{
	if (!m_wrapperMapPopulated)
	{
		PopulateWrappersMap();
		m_wrapperMapPopulated = true;
	}
	// anything else to construct?
}

Error WrapperManager::PopulateWrappersMap()
{
	std::map<void*, void*>& w = m_wrappersMap;
	w[&CreateThread] = _wrapper_CreateThread;
	// put more functions here
	return PP_NO_ERROR;
}