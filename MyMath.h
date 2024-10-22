#pragma once

//-------------------------------------
//構造体
//-------------------------------------

struct Vector2 final {
	float x;
	float y;

	// 複合代理演算子
	Vector2 operator+=(const Vector2& v) {
		x += v.x, y += v.y;
		return *this;
	}
};

struct Vector3 final {
	float x;
	float y;
	float z;

	// 複合代理演算子
	Vector3 operator+=(const Vector3& v) {
		x += v.x, y += v.y, z += v.z;
		return *this;
	}

	// 複合代理演算子
	Vector3 operator+(const Vector3& v) {
		x + v.x, y + v.y, z + v.z;
		return *this;
	}

	Vector3 operator*(float scalar) const {
		return Vector3{ x * scalar, y * scalar, z * scalar };
	}

	Vector3 operator-(const Vector3& other) const {
		return Vector3{ x - other.x, y - other.y, z - other.z };
	}
};

struct Vector4 final {
	float x;
	float y;
	float z;
	float w;
};

struct Matrix3x3 final {
	float m[3][3];
};

struct Matrix4x4 final {
	float m[4][4];
};

namespace MyMath
{
	//-------------------------------------
	//関数
	//-------------------------------------

	//線形補間
	Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

	//cotangent(cot)、tanの逆数
	float cot(float other);

	//単位行列を求める
	Matrix4x4 MakeIdentity4x4();
	// 積
	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

	// 積
	Matrix3x3 Multiply(const Matrix3x3& m1, const Matrix3x3& m2);

	//長さ
	float Length(const Vector3& v);

	//正規化
	Vector3 Normalize(const Vector3& v);

	//逆行列
	Matrix4x4 Inverse(const Matrix4x4& m);

	// 平行移動
	Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

	Matrix3x3 MakeTranslateMatrix(const Vector2& translate);

	// 拡縮
	Matrix4x4 MakeScaleMatrix(const Vector3& scale);

	// X軸回転行列
	Matrix4x4 MakeRotateXMatrix(float radian);
	// Y軸回転行列
	Matrix4x4 MakeRotateYMatrix(float radian);

	// Z軸回転行列
	Matrix4x4 MakeRotateZMatrix(float radian);

	Matrix3x3 MakeRotateZMatrix3x3(float radian);

	//回転行列をX,Y,Zで合成
	Matrix4x4 MakeRotateMatrix(Vector3 rotation);

	// アフィン変換
	Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

	// 正射影行列（平行投影行列）
	Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
	// ビューポート変換行列
	Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

	//透視投影行列
	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

	// ベクトル変換
	// ベクトルの向きだけを回転させるため、4x4行列の平行移動成分を打ち消して、回転（とスケーリング）のみ反映させたもの
	Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

	// イージング関数
	float EaseOutQuad(float t);
};