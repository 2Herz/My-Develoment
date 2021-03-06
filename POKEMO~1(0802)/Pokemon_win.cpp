#include "stdafx.h"

LPCSTR CLASS_NAME = "Pokemon_win";

float g_time = 0.0f;
bool g_isGridMode = false;
bool g_isMoving = false;
float g_xOffset = 0.0f;
float g_yOffset = 0.0f;
POINT g_prevCamPosition;
std::stringstream g_posStr;
POINT g_mousePos;

ImgClass g_background;

void Init(HWND _hWnd)
{
	TIMER.SetFPS(DEFAULT_FPS);
	PLAYER_MANAGER.Init(_hWnd);
	NPC_MANAGER.Init(_hWnd);
	SKILL_MANAGER.Init();
	ITEM_MANAGER.Init();
	POKEDEX.Init();

	SCENE_MGR.Init(_hWnd);
}

void Update(float _elapseTime)
{
	SCENE_MGR.Update(_elapseTime);
}

void Render(HDC _hdc)
{
	SCENE_MGR.Render(_hdc);
}

LRESULT	CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	if (SCENE_MGR.WndProc(_hWnd, _message, _wParam, _lParam) == true)
	{
		return 0;
	}

	switch (_message)
	{
		case WM_KEYDOWN:
		{
			switch (_wParam)
			{
				case VK_ESCAPE:
				{
					PostQuitMessage(0);
				}break;

				default:
					break;
			}
		}break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;
	}

	return DefWindowProc(_hWnd, _message, _wParam, _lParam);
}

int APIENTRY WinMain(HINSTANCE _hInst, HINSTANCE _prevInst, LPSTR _cmdParam, int _cmdShow)
{
	WNDCLASS wndClass = {};
	wndClass.hInstance = _hInst;
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClass(&wndClass);

	int		wsOption = WS_OVERLAPPEDWINDOW;
	RECT	rt = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

	AdjustWindowRect(&rt, wsOption, FALSE);

	HWND hWnd = CreateWindow(CLASS_NAME, CLASS_NAME, wsOption, 0, 0, rt.right - rt.left, rt.bottom - rt.top, nullptr, nullptr, _hInst, nullptr);

	if (hWnd == 0)
	{
		return 0;
	}

	Init(hWnd);
	ShowWindow(hWnd, _cmdShow);

	MSG msg = {};

	g_background.LoadImg(hWnd, "Images/PewterCity2.bmp");

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update(TIMER.DoTick());
			HDC			hdc = GetDC(hWnd);

			HDC	backDC = CreateCompatibleDC(hdc);
			HBITMAP hBit = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
			HBITMAP hOldBit = SelectBitmap(backDC, hBit);

			RECT rc = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
			FillRect(backDC, &rc, GetStockBrush(WHITE_BRUSH));
			g_background.Render(backDC,-320, -384);
			Render(backDC);

			BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, backDC, 0, 0, SRCCOPY);

			DeleteObject(SelectBitmap(backDC, hOldBit));
			DeleteDC(backDC);

			ReleaseDC(hWnd, hdc);
		}
	}

	IMG_MGR->Destroy();

	return 0;
}