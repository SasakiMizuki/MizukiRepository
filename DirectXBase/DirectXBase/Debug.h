#pragma once
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define _CRT_SECURE_NO_WARNIGS
#include <tchar.h>
#include <Windows.h>

// ==========================
//  デバッグ表示
// ==========================
#ifdef _DEBUG
# define Dprint(str, ...) \
{ \
TCHAR c[256]; \
_stprintf_s(c, str, __VA_ARGS__); \
OutputDebugString(c); \
OutputDebugString(_T("\n")); \
}
#else
# define Dprint(str, ...)
#endif

class CDebug
{
public:
	CDebug();
	~CDebug();
};