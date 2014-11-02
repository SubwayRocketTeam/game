#include "pch.h"
#include "main.h"
#include "../Classes/AppDelegate.h"

using namespace cocos2d;

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow){
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	ShowCursor(false);

	AppDelegate app;
	return Application::getInstance()->run();
}
