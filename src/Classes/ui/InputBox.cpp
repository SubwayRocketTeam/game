#include "pch.h"
#include "InputBox.h"

using namespace std;
using namespace cocos2d;

InputBox::InputBox() :
	maxLength(255),
	editbox(nullptr), lastConv(IME_CMODE_NATIVE){
}
InputBox::~InputBox(){
}

InputBox *InputBox::create(
	const string &str,
	const string &name, float size){

	auto i = new InputBox();

	if(i && i->init(str, name, size)){
		i->autorelease();
		return i;
	}

	CC_SAFE_DELETE(i);
	return nullptr;
}
bool InputBox::init(
	const string &str,
	const string &name, float size){

	if(!LabelTTF::initWithString(str, name, size))
		return false;

	HWND hWnd =
		Director::getInstance()->getOpenGLView()->getWin32Window();
	editbox = CreateWindowA(
		"edit", "",
		WS_CHILD | WS_VISIBLE, -1000,0,1000,40, hWnd, 0,
		GetModuleHandle(0), NULL);

	SendMessage(
		editbox, EM_SETLIMITTEXT, (WPARAM)maxLength, NULL);
	SendMessage(
		editbox, EM_SETIMESTATUS, (WPARAM)EMSIS_COMPOSITIONSTRING, (LPARAM)EIMES_CANCELCOMPSTRINFOCUS);

	SetWindowLongPtr(
		editbox, GWLP_USERDATA, (long)this);
	oldProc = (WNDPROC)SetWindowLongPtr(
		editbox, GWLP_WNDPROC, (long)HookProc);

	return true;
}
LRESULT InputBox::HookProc(
	HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam){

	auto _this =
		(InputBox*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	auto result = CallWindowProc(
		_this->oldProc, hWnd, Msg, wParam, lParam);

	switch(Msg){
	case WM_KEYDOWN:
		if(wParam == VK_RETURN)
			_this->endInput();
		break;
	case WM_IME_COMPOSITION:
	case WM_IME_NOTIFY:
		_this->refreshContent();
		break;
	}

	return result;
}

void InputBox::refreshContent(){
	wchar_t *msg = new wchar_t[maxLength];
	char *cmsg = new char[maxLength * 3];

	GetWindowText(editbox, msg, maxLength);
	WideCharToMultiByte(CP_UTF8, 0, msg, -1, cmsg, maxLength*3, 0,0);

	setString(cmsg);

	delete[] msg;
	delete[] cmsg;
}

void InputBox::saveConvMode(){
	HIMC ime = ImmGetContext(editbox);
	ImmGetConversionStatus(ime, &lastConv, nullptr);
	ImmReleaseContext(editbox, ime);
}
void InputBox::restoreConvMode(){
	HIMC ime = ImmGetContext(editbox);
	ImmSetConversionStatus(ime, lastConv, 0);
	ImmReleaseContext(editbox, ime);
}

void InputBox::beginInput(){
	SetFocus(editbox);
	restoreConvMode();
}
void InputBox::endInput(){
	HWND hWnd =
		Director::getInstance()->getOpenGLView()->getWin32Window();

	saveConvMode();
	SetFocus(hWnd);

	/* */
	HIMC ime = ImmGetContext(hWnd);
	ImmSetConversionStatus(ime, IME_CMODE_NOCONVERSION, 0);
	ImmReleaseContext(hWnd, ime);
}

void InputBox::clear(){
	setString("");
	SetWindowText(editbox, L"");
}