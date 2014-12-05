#pragma once

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "ws2_32.lib")

#include <cstdio>
#include <WinSock2.h>
#include <Windows.h>

#include <thread>
// #include <memory>
#include <concurrent_queue.h>
#include <vector>
#include <set>
#include <map>
#include <exception>
#include <functional>
#include <mutex>

#define SAFE_DELETE(p) do{if(p){delete(p);(p)=nullptr;}}while(false)
#define SAFE_DELETE_ARR(p) do{if(p){delete[](p);(p)=nullptr;}}while(false)

#define BUF_SIZE 1024

#define ErrorLog(error) _ErrorLog(__FILE__, __LINE__, error)

void _ErrorLog(const char* const file, const int line, const int errorCode);