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
	Vector3 SpiralShake();

	/// <summary>
	/// 回転シェイク
	/// </summary>
	/// <returns></returns>
	Vector3 ApplyRotationShake();

	/// <summary>
	/// 位置を戻す
	/// </summary>
	Vector3 ResetPosition();

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

	/// <summary>
	/// シェイクの強度を調整
	/// </summary>
	void CalculateShakeIntensity();

private:
	// メンバ変数

	// ローカル座標
	Vector3 translation_ = {};
	// 元のローカル座標
	Vector3 originalTranslation_ = {};

	// 持続時間
	float duration_ = 0.0f;
	// 経過時間
	float timer_ = 0.0f;
	// 強度
	float intensity_ = 0.5f;
	// シェイク全体の進行状況を示す値（0は開始、1は終了）
	float progress_ = 0.0f;
	// 進行状況に基づいて減少した後の強度
	float currentIntensity_ = 0.0f;

	// 渦を巻く振動のための変数
	float spiralRadius_ = {};
	float spiralAngle_ = {};

	// 回転シェイク用のメンバ変数
	float rotationIntensity_ = 0.1f; // 回転の強度
	float rotationAngle_ = 0.0f; // 現在の回転角度

};

