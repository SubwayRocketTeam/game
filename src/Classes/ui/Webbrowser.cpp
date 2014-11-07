#include "pch.h"
#include "Webbrowser.h"

#include <comutil.h>
#include <exdisp.h>
#include <process.h>
#include <stddef.h>

#pragma comment(lib, "comsuppw.lib")

using namespace std;

struct BrowserInfo{
	char uri[256];
	int width;
	int height;
	HICON icon;
};

void BrowserThread(void *arg){
	OleInitialize(NULL);
	BrowserInfo *info = (BrowserInfo*)arg;
  	IWebBrowser2* m_pInetExplorer;

    HRESULT hr;
	HICON hIcon;
    CLSID clsid;
    LPUNKNOWN punk=NULL;
    CLSIDFromProgID (OLESTR("InternetExplorer.Application"), &clsid);
    hr = CoCreateInstance (clsid, NULL, CLSCTX_SERVER, IID_IUnknown, (LPVOID *) &punk);
    if(SUCCEEDED(hr)){
		punk->QueryInterface (IID_IWebBrowser2, (LPVOID *) &m_pInetExplorer);
		punk->Release();
		VARIANT vars[4];
        memset(vars,0,sizeof(vars));
        BSTR BStrURL = _com_util::ConvertStringToBSTR((const char *)(info->uri));
		
        m_pInetExplorer->put_ToolBar(FALSE);
        m_pInetExplorer->put_AddressBar(VARIANT_FALSE);
        m_pInetExplorer->put_MenuBar(VARIANT_FALSE);
        m_pInetExplorer->put_StatusBar(VARIANT_FALSE);
        m_pInetExplorer->put_Width(info->width);
        m_pInetExplorer->put_Height(info->height);

        m_pInetExplorer->put_Visible(VARIANT_TRUE);

		HWND hWnd = NULL;
		m_pInetExplorer->get_HWND ((long*)(&hWnd));

		SetWindowLong(
			hWnd, GWL_STYLE, 
			WS_VISIBLE | WS_POPUP | WS_SYSMENU);

		int windowWidth = GetSystemMetrics(SM_CXSCREEN);
		int windowHeight = GetSystemMetrics(SM_CYSCREEN);
		
		SetWindowPos(hWnd, NULL,
			windowWidth/2 - info->width/2, windowHeight/2 - info->height/2,
			info->width, info->height, 0);

        HRESULT hrie = m_pInetExplorer->Navigate(BStrURL,vars,vars+1,vars+2,vars+3);
        SysFreeString(BStrURL);
				if (SUCCEEDED(hrie))
				{
						VARIANT_BOOL bBusy = VARIANT_TRUE;
						while(bBusy == VARIANT_TRUE)
						{
								Sleep(500);
								m_pInetExplorer->get_Busy(&bBusy);
						}
 						HWND hWnd = NULL;
						m_pInetExplorer->get_HWND ((long*)(&hWnd));

		//	Do other interesting IE stuff here while the window is valid.
		//			while(IsWindow(hWnd))
		//			{
		//					Sleep(500);
		//					m_pInetExplorer->get_HWND ((long*)(&hWnd));
		//			}
				}
				m_pInetExplorer->Release();
	  }
    OleUninitialize();
	
	//delete arg;
}

void Webbrowser::show(
	const string &uri,
	int width, int height){

	BrowserInfo *info = new BrowserInfo();

	memset(info, 0, sizeof(BrowserInfo));
	info->width = width;
	info->height = height;
	strcpy(info->uri, uri.c_str());

	HANDLE hThread = (HANDLE) _beginthread(
		BrowserThread, 0, info );
}