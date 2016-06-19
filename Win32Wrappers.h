#ifndef Win32Wrappers_H
#define Win32Wrappers_H

#include "stdafx.h"
#include <Windows.h>
// define all wrapper methods here
// For our purposes, let's start with CreateThread, CriticalSection

HANDLE _wrapper_CreateThread(
  _In_opt_  LPSECURITY_ATTRIBUTES  lpThreadAttributes,
  _In_      SIZE_T                 dwStackSize,
  _In_      LPTHREAD_START_ROUTINE lpStartAddress,
  _In_opt_  LPVOID                 lpParameter,
  _In_      DWORD                  dwCreationFlags,
  _Out_opt_ LPDWORD                lpThreadId
);

#endif // Win32Wrappers_H