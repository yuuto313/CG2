#pragma once
#include "MyMath.h"

class Shake
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="translation"></param>
	void Initialize(const Vector3& translation);

	/// <summary>
	/// ランダムでシェイクさせる
	/// </summary>
	/// <returns></returns>
	Vector3 ApplyRandomShake();

	/// <summary>
	/// 縦揺れさせる
	/// </summary>
	/// <returns></returns>
	Vector3 ApplyVerticalShake();

	// 横揺れさせる
	Vector3 ApplyHorizontalShake();

	/// <summary>
	/// 渦を巻くシェイク
	/// </summary>
	void SpiralShake();

	/// <summary>
	/// 位置を戻す
	/// </summary>
	Vector3 ResetPosition();
	
	/// <summary>
	/// シェイクフラグのゲッター
	/// </summary>
	/// <returns></returns>
	bool GetIsActive()const { return isActive_; }

	/// <summary>
	/// タイマーの値を取得
	/// </summary>
	/// <returns></returns>
	float GetTimer()const { return timer_; }

	/// <summary>
	/// 持続時間の値を取得
	/// </summary>
	/// <returns></returns>
	float GetDuration()const { return duration_; }

	/// <summary>
	/// タイマーを加算させる
	/// </summary>
	/// <param name="timer"></param>
	void AddTimer(float timer) { timer_ += timer; }

	/// <summary>
	/// シェイクに必要な値を設定
	/// </summary>
	void SetValue(const Vector3& translation);

private:
	// メンバ変数

	// ローカル座標
	Vector3 translation_ = {};
	// 元のローカル座標
	Vector3 originalTranslation_ = {};

	// 有効かどうか
	bool isActive_ = false;
	// 元の位置に戻っているかどうか
	bool isReturning_ = false;
	// 持続時間
	float duration_ = 0.0f;
	// 経過時間
	float timer_ = 0.0f;
	// 強度
	float intensity_ = 0.5f;
	

	// 渦を巻く振動のための変数
	float spiralRadius_ = {};
	float spiralAngle_ = {};

};

