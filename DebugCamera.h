#pragma once
#include <math.h>
#define DIRECTINPUT_VERSION 0x0800	
#include <dinput.h>

#include "Shake.h"
#include "MyMath.h"

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

	// 有効か
	bool isActive_ = false;
	// 元の位置に戻っているかどうか
	bool isReturning_ = false;
	// 持続時間
	float duration_ = 0.0f;
	// 経過時間
	float timer_ = 0.0f;
	// 強度
	float intensity_ = 0.5f;
	// 元のローカル座標
	Vector3 originalTranslation_ = {};

	// 渦を巻く振動のための変数
	float spiralRadius_ = {};
	float spiralAngle_ = {};


	/// <summary>
	/// 縦揺れ
	/// </summary>
	/// <returns></returns>
	Vector3 Pitching();

	// 横揺れ
	Vector3 HorizontalShake();

	/// <summary>
	/// 渦を巻くシェイク
	/// </summary>
	void SpiralShake();

	/// <summary>
	/// カメラの位置を保管して戻す
	/// </summary>
	void ReturnToOriginalPosition();

};

