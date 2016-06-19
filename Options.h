#ifndef Options_H
#define Options_H

#include "stdafx.h"
#include <string>

typedef unsigned int uInt;

class Options
{
public:
	Options();
public: // we'll write accessors later
	std::string m_targetModuleName;
	uInt m_preemptionBound;
};

extern Options gOptions;

// helper functions
Error ParseArguments(int argc, _TCHAR* argv[]);

#endif // Options_H