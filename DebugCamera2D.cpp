#include "DebugCamera2D.h"

void DebugCamera2D::Initialize()
{
    // メンバ変数初期化
    rotation_ = 0.0f;
    translation_ = { 0, 0 };
    viewMatrix_ = {};
    isShakeing_ = false;
    isReturning_ = false;
}

void DebugCamera2D::Update(BYTE key[256])
{
    // カメラの前後移動（上下に対応）
    if (key[DIK_W]) {
        const float speed = 0.3f;
        translation_.y += speed;
    }
    if (key[DIK_S]) {
        const float speed = -0.3f;
        translation_.y += speed;
    }

    // カメラの左右移動
    if (key[DIK_A]) {
        const float speed = -0.3f;
        translation_.x += speed;
    }
    if (key[DIK_D]) {
        const float speed = 0.3f;
        translation_.x += speed;
    }

    // シェイク処理（シェイクはそのまま利用可能）
    //if (isShakeing_) {
    //    shake_->AddTimer(0.016f);
    //    if (shake_->GetTimer() <= shake_->GetDuration()) {
    //        Vector2 shakeOffset = shake_->ApplyRandomShake(); // Vector2に変更
    //        translation_ += shakeOffset;
    //    } else {
    //        isShakeing_ = false;
    //        isReturning_ = true;
    //    }
    //}

    //// カメラの位置を元に戻す処理
    //if (isReturning_) {
    //    translation_ = shake_->ResetPosition(); // ここもVector2で問題なし
    //    isReturning_ = false;
    //}

    // ビュー行列の更新
    // 2Dの場合、z軸回りの回転行列と平行移動行列のみを作成
    Matrix3x3 rotateMatrix = MyMath::MakeRotateZMatrix3x3(rotation_); // z軸周りの回転
    Matrix3x3 translateMatrix = MyMath::MakeTranslateMatrix(translation_);
    viewMatrix_ = MyMath::Multiply(rotateMatrix, translateMatrix);
}

Matrix4x4 DebugCamera2D::Copy3x3To4x4()
{
    Matrix3x3 viewMatrix3x3 = GetViewMatrix();

    Matrix4x4 viewMatrix4x4 = {};

    // 3x3の値を左上にコピー
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            viewMatrix4x4.m[i][j] = viewMatrix3x3.m[i][j];
        }
    }

    // 4x4行列の対角成分を1に設定（4次元の単位行列のため）
    viewMatrix4x4.m[3][3] = 1.0f;

    return viewMatrix4x4;
}

