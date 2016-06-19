#ifndef WrapperManager_H
#define WrapperManager_H

// Manages the wrapper functions for Win32 concurrency APIs

#include <map>

typedef std::map<void*, void*> WrappersMap;

class WrapperManager
{
public:
	static WrapperManager& GetInstance();
	Error ShimWrappers(HMODULE module);
private:
	WrapperManager();
	Error PopulateWrappersMap();

private:
	static WrapperManager *m_instance;
	static WrappersMap m_wrappersMap; // make it faster using a hash_map?
	static bool m_wrapperMapPopulated;
};

#endif // WrapperManager_H