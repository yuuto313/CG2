#include "DirectXCommon.h"
#include "Debug.h"
#include <format>

void DirectXCommon::Initialize(Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory, HRESULT hr, Microsoft::WRL::ComPtr<ID3D12Device> device)
{

	//-------------------------------------
	//使用するアダプタ(GPU)を決める
	//-------------------------------------
	//使用するアダプタ（GPU）用の変数。最初にnullptrを入れておく
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;
	//良い順にアダプタを読む
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter)) != DXGI_ERROR_NOT_FOUND; ++i) {
		//アダプタの情報を取得する
		DXGI_ADAPTER_DESC3 adapterDesc{};
		hr = useAdapter->GetDesc3(&adapterDesc);
		//取得できないのは一大事
		assert(SUCCEEDED(hr));
		//ソフトウェアアダプタでなければ採用
		if(!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)){
			//採用したアダプタの方法をログに出力、wstringのほうなので注意
			Debug::Log(Debug::ConvertString(std::format(L"Use Adapter:{}\n", adapterDesc.Description)));
			break;
		}
		//ソフトウェアアダプタの場合は見なかったことにする
		useAdapter = nullptr;
	}
	//適切なアダプタが見つからなかったので起動できない
	assert(useAdapter != nullptr);

	//-------------------------------------
	// D3D12Deviceの生成
	//-------------------------------------

	//機能レベルとログ出力用の文字列
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_12_2,D3D_FEATURE_LEVEL_12_1,D3D_FEATURE_LEVEL_12_0
	};
	const char* featureLevelStrings[] = { "12.2","12.1","12.0" };
	//高い順に生成できるか試す
	for (size_t i = 0; i < _countof(featureLevels); ++i) {
		//採用したアダプタでデバイスを生成
		hr = D3D12CreateDevice(useAdapter.Get(), featureLevels[i], IID_PPV_ARGS(&device));
		//指定した機能レベルでデバイスが生成出来たか確認
		if (SUCCEEDED(hr)) {
			//生成できたのでログ出力を行ってループを抜ける
			Debug::Log(std::format("FeatureLevel:{}\n", featureLevelStrings[i]));
			break;
		}
	}
	//デバイスの生成がうまくいかなかったので起動できない
	assert(device != nullptr);
	//初期化完了のログを出す
	Debug::Log("Complete createD3D12Device!!!\n");
}
