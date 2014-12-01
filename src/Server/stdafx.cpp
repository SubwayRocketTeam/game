#include "stdafx.h"

void ErrorLog(const int errorCode)
{
	char* buf = nullptr;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		nullptr,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&buf,
		0,
		nullptr);
	fputs("ERROR: ", stderr);
	fputs(buf, stderr);
}