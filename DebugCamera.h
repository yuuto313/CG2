#pragma once
#include "MyMath.h"
#include <math.h>
#define DIRECTINPUT_VERSION 0x0800	
#include <dinput.h>

/// <summary>
/// デバッグカメラ
/// </summary>
class DebugCamera
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update(BYTE key[256]);


	Matrix4x4 GetViewMatrix()const { return viewMatrix_; }
private:
	//x,y,z軸周りのローカル回転角
	Vector3 rotation_ = { 0,0,0 };
	//ローカル座標
	Vector3 translation_ = { 0,0,-50 };
	//ビュー行列
	Matrix4x4 viewMatrix_ = {};
	//射影行列
	Matrix4x4 projectionMatrix_ = {};


};

