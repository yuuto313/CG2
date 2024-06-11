#include <d3d12.h>
#pragma once
/// <summary>
/// ID3D12Resourceを自動で開放するクラス
/// </summary>
class ResourceObject
{
public:
	ResourceObject(ID3D12Resource* resource) :resource_(resource) {};
	~ResourceObject() {
		if (resource_) {
			resource_->Release();
		}
	};

	ID3D12Resource* Get() {
		return resource_;
	}
private:
	ID3D12Resource* resource_;
};

