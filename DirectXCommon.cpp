#include "DirectXCommon.h"
#include "Debug.h"
#include <format>

void DirectXCommon::Initialize(WinApp* winApp)
{
	winApp_ = winApp;
	winApp_->Initialize();

	InitializeDXGIDevice();
}

void DirectXCommon::InitializeDXGIDevice()
{
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory_));

	//使用するアダプタ（GPU）用の変数。最初にnullptrを入れておく
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;
	//良い順にアダプタを読む
	for (UINT i = 0; dxgiFactory_->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter)) != DXGI_ERROR_NOT_FOUND; ++i) {
		//アダプタの情報を取得する
		DXGI_ADAPTER_DESC3 adapterDesc{};
		hr = useAdapter->GetDesc3(&adapterDesc);
		assert(SUCCEEDED(hr));   //取得できないのは一大事
		//ソフトウェアアダプタでなければ採用！
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			//採用したアダプタの情報をログに出力、wstringの方なので注意
			Debug::Log(Debug::ConvertString(std::format(L"USE Adapter:{}\n", adapterDesc.Description))); //???
			break;
		}
		useAdapter = nullptr; //ソフトウェアアダプタの場合は見なかったことにする
	}
	//適切なアダプタが見つからなかったので起動できない
	assert(useAdapter != nullptr);


	//機能レベルとログ出力用の文字列
	D3D_FEATURE_LEVEL featureLevels[] = {
	D3D_FEATURE_LEVEL_12_2,D3D_FEATURE_LEVEL_12_1,D3D_FEATURE_LEVEL_12_0
	};
	const char* featureLevelStrings[] = { "12.2","12.1",{"12.0"} };
	//高い順に生成できるか試す
	for (size_t i = 0; i < _countof(featureLevels); ++i) {
		//採用したアダプタでデバイスを生成
		hr = D3D12CreateDevice(useAdapter.Get(), featureLevels[i], IID_PPV_ARGS(&device_));
		//指定した機能レベルでデバイスが生成できたかを確認
		if (SUCCEEDED(hr)) {
			//生成できたのでログ出力を行ってループを抜ける
			Debug::Log(std::format("FeatureLevel:{}\n", featureLevelStrings[i]));
			break;
		}
	}

	//デバイスの生成がうまくいかなかったので起動できない
	assert(device_ != nullptr);
	Debug::Log("Complete createD3D12Device!!!\n"); //初期化完了のログを出す

#ifdef _DEBUG

	//-------------------------------------
	//エラーと警告の抑制
	//-------------------------------------

	Microsoft::WRL::ComPtr<ID3D12InfoQueue> infoQueue = nullptr;
	if (SUCCEEDED(device_->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
		//やばいエラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		//エラー時に止まる
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
		//警告時に止まる
		//infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);

		D3D12_MESSAGE_ID denyIds[] = {
			//Windows11でのDXGIデバッグレイヤーとDX12デバッグレイヤーの相互作用バグによるエラーメッセージ
			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};

		//抑制するレベル
		D3D12_MESSAGE_SEVERITY severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER filter{};
		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;
		//指定したメッセージの表示を抑制する
		infoQueue->PushStorageFilter(&filter);

		//解放
		//infoQueue->Release();

	}
#endif
}

void DirectXCommon::CreateSwapChain()
{
	//HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory_));

	////-------------------------------------
	////スワップチェーンを生成する
	////-------------------------------------

	//Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain = nullptr;
	//DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	//swapChainDesc.Width = winApp_->GetClientWidth();                 //画面の幅。ウィンドウのクライアント領域を同じものにしておく
	//swapChainDesc.Height = winApp_->GetClientHeight();               // 画面の高さ。ウィンドウのクライアント領域を同じものにしておく
	//swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  //色の形式
	//swapChainDesc.SampleDesc.Count = 1;                 //マルチサンプルしない
	//swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  //描画のターゲットとして利用する
	//swapChainDesc.BufferCount = 2;                      //ダブルバッファ
	//swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;     //モニターにうつしたら、中身を破棄
	////コマンドキュー、ウィンドウハンドル、設定を渡して生成する
	//hr = dxgiFactory_->CreateSwapChainForHwnd(commandQueue.Get(), winApp->GetHWND(), &swapChainDesc, nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(swapChain.GetAddressOf()));
	//assert(SUCCEEDED(hr));

}
