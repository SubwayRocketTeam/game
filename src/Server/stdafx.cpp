#include "stdafx.h"

void _ErrorLog(const char* const file, const int line, const int errorCode)
{
	char* buf = nullptr;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		nullptr,
		errorCode,
		MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
		(LPSTR)&buf,
		0,
		nullptr);
	fprintf(stderr, "%s(%d): %s (%d)\n", file, line, buf, errorCode);
	__debugbreak();
}