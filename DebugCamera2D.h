#pragma once
#include <math.h>
#define DIRECTINPUT_VERSION 0x0800	
#include <dinput.h>

#include "Shake.h"
#include "MyMath.h"
/// <summary>
/// 2Dデバッグカメラ
/// </summary>
class DebugCamera2D
{
public:

	void Initialize();

	void Update(BYTE key[256]);

	/// <summary>
	/// ビュー行列のゲッター
	/// </summary>
	/// <returns></returns>
	Matrix3x3 GetViewMatrix()const { return viewMatrix_; }

	Matrix4x4 Copy3x3To4x4();

private:

	// x, y軸周りのローカル回転角
	float rotation_ = 0.0f;
	// ローカル座標
	Vector2 translation_ = { 0,0 };
	// ビュー行列
	Matrix3x3 viewMatrix_ = {};
	//射影行列
	Matrix3x3 projectionMatrix_ = {};

	// シェイク関連

	// シェイクフラグ
	bool isShakeing_ = false;
	// 縦揺れフラグ
	bool isVertical_ = false;
	// 横揺れフラグ
	bool isHorizontal_ = false;
	// 渦巻きシェイクフラグ
	bool isSpiral_ = false;
	// 元の位置に戻っているかどうか
	bool isReturning_ = false;
};

