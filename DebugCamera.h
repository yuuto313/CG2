#pragma once
#include <math.h>
#define DIRECTINPUT_VERSION 0x0800	
#include <dinput.h>

#include "Shake.h"
#include "MyMath.h"

/// <summary>
/// 3Dデバッグカメラ
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
	void Update(BYTE key[256],BYTE preKey[256]);

	/// <summary>
	/// ビュー行列のゲッター
	/// </summary>
	/// <returns></returns>
	Matrix4x4 GetViewMatrix()const { return viewMatrix_; }
private:
	// メンバ変数

	Shake* shake_ = nullptr;

	//x,y,z軸周りのローカル回転角
	Vector3 rotation_ = { 0,0,0 };
	//ローカル座標
	Vector3 translation_ = { 0,0,-25 };
	//ビュー行列
	Matrix4x4 viewMatrix_ = {};
	//射影行列
	Matrix4x4 projectionMatrix_ = {};


	// シェイク関連

	// シェイクフラグ
	bool isShakeing_ = false;
	// 縦揺れフラグ
	bool isVertical_ = false;
	// 横揺れフラグ
	bool isHorizontal_ = false;

	// 元の位置に戻っているかどうか
	bool isReturning_ = false;

};

