#pragma once
#include <Windows.h>
#include <cstdint>

//-------------------------------------
//ウィンドウプロシージャ
//-------------------------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

/// <summary>
/// ウィンドウプロシージャ
/// ウィンドウを作成、表示する
/// </summary>
class WinApp
{
public:
	void Initialize();

	int32_t GetClientWidth() { return kClientWidth; }
	int32_t GetClientHeight() { return kClientHeight; }
	HWND GetHWND() { return hwnd; }

private:
	//クライアント領域のサイズ
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;
	HWND hwnd;
};
