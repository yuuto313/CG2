#include "DirectXCommon.h"
#include "Debug.h"
#include <format>

void DirectXCommon::Initialize(IDXGIFactory7* dxgiFactory, HRESULT hr,ID3D12Device* device)
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
			Debug::Log(Debug::ConvertString(std::format(L"Use Adapter:{}\n", adapterDesc.Description));
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



}
