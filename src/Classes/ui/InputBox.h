#pragma once

#include "cocos2d.h"

#include <string>

class InputBox : public cocos2d::LabelTTF{
public:
	static InputBox *create(
		const std::string &str,
		const std::string &name, float size);

	void beginInput();
	void endInput();

protected:
	InputBox();
	virtual ~InputBox();
	
	virtual bool init(
		const std::string &str,
		const std::string &name, float size);
	
	void refreshContent();

	static LRESULT HookProc(
		HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

private:
	int maxLength;

	bool inputEnabled;
	HWND editbox;
	WNDPROC oldProc;
};