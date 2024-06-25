#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <wrl.h>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
/// <summary>
/// DirectX12を初期化する
/// </summary>
class DirectXCommon
{
public:
	
	void Initialize(Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory, HRESULT hr, Microsoft::WRL::ComPtr<ID3D12Device> device);

private:

};

