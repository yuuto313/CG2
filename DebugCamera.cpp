#include "DebugCamera.h"
#include <time.h>

void DebugCamera::Initialize()
{
	shake_ = new Shake();
	shake_->Initialize(translation_);

	rotation_ = { 0,0,0 };
	translation_ = { 0,0,-50 };
	viewMatrix_ = {};
	projectionMatrix_ = {};
	isActive_ = false;
	isReturning_ = false;

	srand(static_cast<unsigned int>(time(0)));

}

void DebugCamera::Update(BYTE key[256])
{

	//入力によるカメラの移動や回転
	//前後移動
	if (key[DIK_W]) {
		const float speed = 0.3f;
		//カメラ移動ベクトル
		Vector3 move = { 0,0,speed };
		Matrix4x4 rotateZmatrix = MyMath::MakeRotateZMatrix(rotation_.z);
		//移動ベクトルを角度分だけ回転させる
		move = MyMath::TransformNormal(move, rotateZmatrix);
		translation_ += move;
	}
	if (key[DIK_S]) {
		const float speed = -0.3f;
		Vector3 move = { 0,0,speed };
		Matrix4x4 rotateZmatrix = MyMath::MakeRotateZMatrix(rotation_.z);
		move = MyMath::TransformNormal(move, rotateZmatrix);
		translation_ += move;
	}

	//左右移動
	if (key[DIK_A]) {
		const float speed = -0.3f;
		Vector3 move = { speed,0,0 };
		Matrix4x4 rotateXmatrix = MyMath::MakeRotateXMatrix(rotation_.x);
		move = MyMath::TransformNormal(move, rotateXmatrix);
		translation_ += move;
	}
	if (key[DIK_D]) {
		const float speed = 0.3f;
		Vector3 move = { speed,0,0 };
		Matrix4x4 rotateXmatrix = MyMath::MakeRotateXMatrix(rotation_.x);
		move = MyMath::TransformNormal(move, rotateXmatrix);
		translation_ += move;
	}

	//上下移動
	if (key[DIK_UP]) {
		const float speed = 0.3f;
		Vector3 move = { 0,speed,0 };
		Matrix4x4 rotateYmatrix = MyMath::MakeRotateYMatrix(rotation_.y);
		move = MyMath::TransformNormal(move, rotateYmatrix);
		translation_ += move;
	}
	if (key[DIK_DOWN]) {
		const float speed = -0.3f;
		Vector3 move = { 0,speed,0 };
		Matrix4x4 rotateYmatrix = MyMath::MakeRotateYMatrix(rotation_.y);
		move = MyMath::TransformNormal(move, rotateYmatrix);
		translation_ += move;
	}

	// シェイクを開始する
	if (key[DIK_K] && !isActive_) {
		isActive_ = true;
		shake_->SetValue(translation_);
	}

	// シェイク処理
	if (isActive_) {
		shake_->AddTimer(0.016f);
		if (shake_->GetTimer() <= shake_->GetDuration()) {
			Vector3 shakeOffset = shake_->ApplyRandomShake();
			translation_ += shakeOffset;
		} else {
			isActive_ = false;
			isReturning_ = true;
		}
	}

	if (isReturning_) {
		translation_ = shake_->ResetPosition();
		isReturning_ = false;
	}

	//ビュー行列の更新
	//角度から回転行列を作成する
	Matrix4x4 rotateMatrix = MyMath::MakeRotateMatrix(rotation_);
	//座標から平行移動行列を作成する
	Matrix4x4 translateMatrix = MyMath::MakeTranslateMatrix(translation_);
	//回転行列と平行移動行列からワールド行列を作成する
	Matrix4x4 worldMatrix = MyMath::Multiply(rotateMatrix, translateMatrix);

	//ワールド行列の逆行列をビュー行列に代入する
	viewMatrix_ = MyMath::Inverse(worldMatrix);

}
