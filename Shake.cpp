#include "Shake.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

void Shake::Initialize(const Vector3& translation)
{
	translation_ = translation;

	srand(static_cast<unsigned int>(time(0)));
}

Vector3 Shake::ApplyRandomShake()
{
	//　強度を調整
	CalculateShakeIntensity();

	// ランダムな値を設定
	Vector3 direction = { static_cast<float>(rand() % 50 / 50.0f - 0.5f) * currentIntensity_,static_cast<float>(rand() % 50 / 50.0f - 0.5f) * currentIntensity_, 0.0f };

	// 振動を加える
	// 周波数
	float frequency = 10.0f;
	float amplitude = currentIntensity_ * sinf(frequency * timer_);

	return direction * amplitude;
}

Vector3 Shake::ApplyVerticalShake()
{
	// 強度を調整
	CalculateShakeIntensity();

	// ランダムな縦方向の振動を生成
	float offsetY = (rand() % 50 / 50.0f - 0.5f) * currentIntensity_;

	// 振動をY軸方向に加える
	return Vector3(0.0f, offsetY, 0.0f);
}

Vector3 Shake::ApplyHorizontalShake()
{
	// 強度を調整
	CalculateShakeIntensity();

	// ランダムな横方向の振動を生成
	float offsetX = (rand() % 50 / 50.0f - 0.5f) * currentIntensity_;

	// 振動をX軸方向に加える
	return Vector3(offsetX, 0.0f, 0.0f);
}

Vector3 Shake::SpiralShake()
{
	// 強度を調整
	CalculateShakeIntensity();

	// 渦巻きの半径と角度を更新
	spiralAngle_ += 0.1f;  // 渦巻きのスピード
	spiralRadius_ = currentIntensity_ * (1.0f - progress_);

	// 渦巻きのオフセットを計算
	float xOffset = spiralRadius_ * cos(spiralAngle_);
	float yOffset = spiralRadius_ * sin(spiralAngle_);

	// 渦巻きによる位置を加算
	return Vector3(xOffset, yOffset, 0.0f);
}

Vector3 Shake::ApplyRotationShake()
{
	CalculateShakeIntensity();

	// 回転のオフセットを計算
	rotationAngle_ += 0.1f; // 回転の速度
	float angleOffset = rotationIntensity_ * currentIntensity_ * sin(rotationAngle_);

	// XとYのオフセットに回転の影響を加える
	return Vector3(angleOffset, angleOffset, 0.0f); // 簡単な実装
}

Vector3 Shake::ResetPosition()
{
	const float returnSpeed = 0.1f;  // 速度調整
	Vector3 translation = MyMath::Lerp(translation_, originalTranslation_, returnSpeed * 0.016f);

	translation_ = { translation.x,translation.y,originalTranslation_.z };

	// 位置がほぼ元に戻ったら戻す処理を終了
	if (MyMath::Length(translation_ - originalTranslation_) < 0.01f) {
		translation_ = originalTranslation_;
	}

	return translation_;

}

void Shake::SetValue(const Vector3& translation)
{
	// 時間を設定する
	duration_ = 0.5f;
	timer_ = 0.0f;
	originalTranslation_ = translation;
	progress_ = 0.0f;
	currentIntensity_ = 0.0f;
	spiralAngle_ = 0.0f;
	spiralRadius_ = 0.0f;
	rotationAngle_ = 0.0f;
}

void Shake::CalculateShakeIntensity()
{
	// シェイクの進行に基づいて強度を減少させる
	progress_ = timer_ / duration_;
	// 徐々に強度を減少
	currentIntensity_ = intensity_ * (1.0f - progress_);
}
