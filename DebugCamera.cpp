#include "DebugCamera.h"

void DebugCamera::Initialize()
{
	rotation_ = { 0,0,0 };
	translation_ = { 0,0,-50 };
	viewMatrix_ = {};
	projectionMatrix_ = {};
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

	//回転



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
