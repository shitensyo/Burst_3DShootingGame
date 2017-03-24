#pragma once

#include <gslib.h>
#include "Vector3.h"
#include "Vector4.h"
#include <string>

class Matrix4
{
public:
	float m[4][4];

public:

	//ゼロ行列を返す
	static Matrix4 Zero;

	//単位行列を返す
	static Matrix4 Identity;

public:

	//コンストラクタ
	Matrix4();

	//コンストラクタ
	Matrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	//コンストラクタ
	Matrix4(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3);

public:

	//自身の座標を返す
	Vector3 GetPosition() const;

	//自身の横を返す
	Vector3 GetLeft() const;

	//自身の上を返す
	Vector3 GetUp() const;

	//自身の前を返す
	Vector3 GetFront() const;

	//自身のスケールを返す
	Vector3 GetScale() const;

	//自身の各軸の回転量をラジアンで返す
	Vector3 GetRotate() const;

	//自身の各軸の回転量を角度で返す
	Vector3 GetRotateDegree() const;

	//座標をセットする
	void SetPosition(const Vector3& position);

	//左をセットする
	void SetLeft(const Vector3& left);

	//上をセットする
	void SetUp(const Vector3& up);

	//前をセットする
	void SetFront(const Vector3& front);

	//回転行列Xをセットする
	void SetRotateX(float angle);

	//回転行列Yをセットする
	void SetRotateY(float angle);

	//回転行列Zをセットする
	void SetotateZ(float angle);

public:

	//拡大縮小行列
	static Matrix4 Scale(const Vector3& s);

	//回転行列X
	static Matrix4 RotateX(float angle);

	//回転行列Y
	static Matrix4 RotateY(float angle);

	//回転行列Z
	static Matrix4 RotateZ(float angle);

	//平行移動行列
	static Matrix4 Translate(const Vector3& pos);

	//マトリックスを作成する スケール　X軸　Y軸　Z軸　移動量
	static Matrix4 CreateMatrix(const Vector3& s = Vector3::One, const float& rototeXangle = 0, const float& rotateYangle = 0, const float& rotateZangle = 0, const Vector3& pos = Vector3::Zero);

	//マトリックスを作成する
	static Matrix4 CreateMatrix(const Matrix4& scale_ = Identity, const Matrix4& rotateX_ = Identity, const Matrix4& rotateY_ = Identity, const Matrix4& rotateZ_ = Identity, const Matrix4& translate_ = Identity);

	//ベクトルの座標変換(ベクトルと行列の積)
	static Vector3 Transform(const Vector3& v, const Matrix4& m);

	//ベクトルの座標変換(回転のみ)
	static Vector3 TransformRotateOnly(const Vector3& v, const Matrix4& m);

	//転置行列
	static Matrix4 Transpose(const Matrix4& m);
	static Matrix4 TransposeRotateOnly(const Matrix4& m);

	//逆行列(拡縮除く)
	static Matrix4 InverseFast(const Matrix4& m);

	//逆行列
	static Matrix4 Inverse(const Matrix4& m);


public:
	//ワールド行列を作成を作成する
	static Matrix4 World(const Vector3& scale, const Matrix4& rotation, const Vector3& translation);
	//ワールド行列を作成を作成する
	static Matrix4 World(const Vector3& position, const Vector3& forward, const Vector3& up);
	//視野変換行列(ビュー行列)を作成する
	static Matrix4 LookAt(const Vector3& eye, const Vector3& at, const Vector3& up);
	//透視変換行列を作成する
	static Matrix4 Perspective(float fov, float aspect, float zn, float zf);
	//スクリーン座標変換行列を作成する
	static Matrix4 Screen(float x, float y, float width, float height);

public:

	//座標を返す
	static Vector3 GetPosition(const Matrix4& m);

	//横を返す
	static Vector3 GetLeft(const Matrix4& m);

	//上を返す
	static Vector3 GetUp(const Matrix4& m);

	//前を返す
	static Vector3 GetFront(const Matrix4& m);

	//スケールを返す
	static Vector3 GetScale(const Matrix4& m);

	//各軸の回転量をラジアン返す
	static Vector3 GetRotate(const Matrix4& m);

	//各軸の回転量を角度で返す
	static Vector3 GetRotateDegree(const Matrix4& m);

	//座標をセットした行列を返す
	static Matrix4 SetPosition(Matrix4& m, const Vector3& position);

	//左をセットした行列を返す
	static Matrix4 SetLeft(Matrix4& m, const Vector3& left);

	//上をセットした行列を返す
	static Matrix4 SetUp(Matrix4& m, const Vector3& up);

	//前をセットした行列を返す
	static Matrix4 SetFront(Matrix4& m, const Vector3& front);

	//球面線形補間
	static Matrix4 Slerp(const Matrix4& start, const Matrix4& end, float t);

	//線形補間
	static Matrix4 Lerp(const Matrix4& start, const Matrix4& end, float t);

	//ピッチ角(左右軸、上下方向回転量)を求める
	static float Pitch(const Matrix4& m);

	//ヨー角(上下軸、前後方向回転量)を求める
	static float Yaw(const Matrix4& m);

	//ロール角(前後軸、左右方向回転量)を求める
	static float Roll(const Matrix4& m);


	//スクリーン変換
	static Vector3 Project(const Vector3& position,
		const Matrix4& screen,
		const Matrix4& projection,
		const Matrix4& view,
		const Matrix4& world = Identity);

	//画面の座標からローカル座標を求める
	static Vector3 UnProject(const Vector3& position,
		const Matrix4& screen,
		const Matrix4& projection,
		const Matrix4& view,
		const Matrix4& world = Identity);

	//回転行列の正規化
	static Matrix4 NormalizeRotate(const Matrix4& m);

public:
	//Matrix4型をGSmatrix4型に変換して返す
	static GSmatrix4 ToGSmatrix4(const Matrix4& m);
	//自身をGSmatrix4型に変換したものを返す
	GSmatrix4 ToGSmatrix4() const;
	//GSmatrix4型をMatrix4型に変換して返す
	static Matrix4 ToMatrix4(const GSmatrix4& m);

public:
	Matrix4& operator = (const Matrix4& m_);
	operator std::string() const;
};

Matrix4& operator *= (Matrix4& m1, const Matrix4& m2);
Matrix4 operator * (const Matrix4& m1, const Matrix4& m2);
Vector3 operator * (const Vector3& v, const Matrix4& m);