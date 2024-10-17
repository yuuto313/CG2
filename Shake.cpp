#include "Shake.h"
#include <math.h>
#include <stdlib.h>

void Shake::Initialize(const Vector3& translation)
{
	translation_ = translation;
}

Vector3 Shake::ApplyRandomShake()
{
	// シェイクの進行に基づいて強度を減少させる
	float progress = timer_ / duration_;
	// 徐々に強度を減少
	float currentIntensity = intensity_ * (1.0f - progress);

	// ランダムな値を設定
	Vector3 direction = { static_cast<float>(rand() % 50 / 50.0f - 0.5f) * currentIntensity,static_cast<float>(rand() % 50 / 50.0f - 0.5f) * currentIntensity, 0.0f };

	// 振動を加える
	// 周波数
	float frequency = 10.0f;
	float amplitude = currentIntensity * sinf(frequency * timer_);

	return direction * amplitude;
}

Vector3 Shake::ResetPosition()
{
	const float returnSpeed = 5.0f;  // 速度調整
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
}
