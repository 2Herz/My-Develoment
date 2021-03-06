#pragma once

#include <Windows.h>
#include <windowsx.h>

class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Update(float _elapseTime) = 0;
	virtual void Render(HDC _hdc) = 0;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};