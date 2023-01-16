#pragma once

#include <string>

using std::wstring;

int rt_core(const wstring fname);
inline int rt_core(const wchar_t* fname) {
	return rt_core(wstring(fname));
}