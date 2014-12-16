#pragma once

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "ws2_32.lib")

#include <cstdio>
#include <cmath>
#include <cfloat>
#include <WinSock2.h>
#include <Windows.h>

#include <thread>
// #include <memory>
#include <concurrent_queue.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <exception>
#include <functional>
#include <mutex>
#include <atomic>

#define SAFE_DELETE(p) do{if(p){delete(p);(p)=nullptr;}}while(false)
#define SAFE_DELETE_ARR(p) do{if(p){delete[](p);(p)=nullptr;}}while(false)

#define DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f)
#define RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f)

#define BUF_SIZE 1024

#define ErrorLog(error) _ErrorLog(__FILE__, __LINE__, error)

void _ErrorLog(const char* const file, const int line, const int errorCode);