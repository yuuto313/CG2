#include "WinApp.h"
#include "cstdint"
#include "externals/imgui/imgui_impl_win32.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
		return true;
	}
	//メッセージに応じてゲーム固有の処理を行う
	switch (msg) {
		//ウィンドウが破棄された
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	//標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WinApp::Initialize()
{
	WNDCLASS wc{};
	//ウィンドウプロシージャ
	wc.lpfnWndProc = WindowProc;
	//ウィンドウクラス名
	wc.lpszClassName = L"CG2";
	//インスタンスハンドル
	wc.hInstance = GetModuleHandle(nullptr);
	//カーソル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	//ウィンドウクラスを登録する
	RegisterClass(&wc);


	//ウィンドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc = { 0,0,kClientWidth,kClientHeight };

	//クライアント領域を元に実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウの生成
	hwnd = CreateWindow(
		wc.lpszClassName,               //引用するクラス名
		L"CG2",                         //タイトルバーの文字
		WS_OVERLAPPEDWINDOW,            //よく見るウィンドウスタイル
		CW_USEDEFAULT,                  //表示X座標（Windowsに任せる）
		CW_USEDEFAULT,                  //表示Y座標（WindowsOSに任せる）
		wrc.right - wrc.left,           //ウィンドウ横幅
		wrc.bottom - wrc.top,           //ウィンドウ縦幅
		nullptr,                        //親ウィンドウハンドル
		nullptr,                        //メニューハンドル
		wc.hInstance,                   //インスタンスハンドル
		nullptr                         //オプション
	);

	//ウィンドウを表示する
	ShowWindow(hwnd, SW_SHOW);
}
