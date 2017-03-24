#pragma once

#include "Vector3.h"
#include "Matrix4.h"

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

public:
	
	//コンストラクタ	
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	
	//コンストラクタ	
	Quaternion(const Vector3& v, float angle);
	
	//コンストラクタ(回転行列からクウォータニオンを作成)	
	Quaternion(const Matrix4& m);

public:
	
	//内積を返す	
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	
	//大きさ（長さ）を返す	
	static float Length(const Quaternion& q);
	
	//正規化をする	
	static Quaternion Normalize(const Quaternion& q);
	
	//球面線形補間	
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);
	
	//クォータニオンを回転行列にして返す	
	static Matrix4 Rotate(const Quaternion& q);
	
	//任意軸周りの回転行列を返す	
	static Matrix4 RotateAxis(const Vector3& v, float angle);

public:
	//Quaternion型をMatrix4型に変換する
	Matrix4 ToMatrix4(const Quaternion& q);
	//自身をMatrix4型に変換したものを返す
	Matrix4 ToMatrix4() const;
	//Matrix4型をQuaternion型に変換する
	Quaternion ToQuaternion(const Matrix4& m);
};

// 単項演算子オーバーロード
Quaternion operator + (const Quaternion& q);
Quaternion operator - (const Quaternion& q);
// 代入演算子オーバーロード
Quaternion& operator += (Quaternion& q1, const Quaternion& q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion& q2);
Quaternion& operator *= (Quaternion& q, float s);
Quaternion& operator /= (Quaternion& q, float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);
// ２項演算子オーバーロード
Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q, float s);
Quaternion operator * (float s, const Quaternion& q);
Quaternion operator / (const Quaternion& q, float s);