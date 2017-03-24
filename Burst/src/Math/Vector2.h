#pragma once

#include <gslib.h>
#include <string>
class Point;

class Vector2
{
public:
	float x;
	float y;
public:
	
	//(0, 0)で初期化されたベクトルを返す
	
	static Vector2 Zero;
	
	//(1, 1)で初期化されたベクトルを返す
	
	static Vector2 One;
	
	//(-1, 0)で初期化されたベクトルを返す
	
	static Vector2 Left;
	
	//(1, 0)で初期化されたベクトルを返す
	
	static Vector2 Right;
	
	//(0, -1)で初期化されたベクトルを返す
	
	static Vector2 Up;
	
	//(0, 1)で初期化されたベクトルを返す
	
	static Vector2 Down;
	
	//画面中央の座標で初期化されたベクトルを返す
	
	static Vector2 WindowCenter;
public:
	
	//コンストラクタ
	
	Vector2();
	
	//コンストラクタ
	
	Vector2(float x, float y);
	
	//コンストラクタ
	
	Vector2(int x, int y);
	
	//コンストラクタ
	
	Vector2(const Vector2& vec);
	
	//コンストラクタ
	
	Vector2(const GSvector2& vec);
	
	//コンストラクタ
	
	Vector2(float s);
	
	//コンストラクタ
	
	Vector2(int s);
public:
	
	//自身のベクトルの大きさ（長さ）を返す
	
	float Length() const;
	
	//自身のベクトルの大きさ（長さ）の二乗を返す
	
	float LengthPow2() const;
	
	//２点間の距離を返す
	
	float Distance(const Vector2& other) const;
	
	//２点間の距離の二乗を返す
	
	float DistancePow2(const Vector2& other) const;
	
	//自身のベクトルを正規化する
	
	void Normalize();
	
	//自身の正規化されたベクトルを返す
	
	Vector2 Normalized() const;
	
	//自身と相手のベクトルの内積を返す
	
	float Dot(const Vector2& v) const;
	
	//自身と相手のベクトルのなす角を返す
	
	float Inner(const Vector2& v) const;
public:
	
	//ベクトルを正規化する
	
	static Vector2 Normalize(const Vector2& v);
	
	//２点間の距離を返す
	
	static float Distance(const Vector2& v1, const Vector2& v2);
	
	//２点間の距離の二乗を返す
	
	static float DistancePow2(const Vector2& v1, const Vector2& v2);
	
	//２つのベクトルの内積を返す
	
	static float Dot(const Vector2& v1, const Vector2& v2);
	
	//２つのベクトルのなす角を返す
	
	static float Inner(const Vector2& v1, const Vector2& v2);
	
	//二つのベクトルの外積を返す
	
	static float Cross(const Vector2& v1, const Vector2& v2);
	///<summary>
	//二つのベクトル間の線形補間する
	///</summary>
	static Vector2 Lerp(const Vector2& start, const Vector2& end, float amount);
	
public:
	///<summary>
	//Vector2型をPoint型に変換して返す
	///</summary>
	static Point ToPoint(const Vector2& v);
	///<summary>
	//自身をPoint型に変換したものを返す
	///</summary>
	Point ToPoint() const;
	///<summary>
	//Vector2型をGSvector2型に変換して返す
	///</summary>
	static GSvector2 ToGSvector2(const Vector2& v);
	///<summary>
	//自身をGSvector2型に変換したものを返す
	///</summary>
	GSvector2 ToGSvector2() const;


public:
	Vector2& operator = (const Vector2& v);
	operator std::string() const;
};

Vector2 operator + (const Vector2& v1, const Vector2& v2);
Vector2& operator += (Vector2& v1, const Vector2& v2);
Vector2 operator - (const Vector2& v1, const Vector2& v2);
Vector2& operator -= (Vector2& v1, const Vector2& v2);
Vector2 operator * (const Vector2& v, const float f);
Vector2 operator * (const float f, const Vector2& v);
Vector2& operator *= (Vector2& v, const float f);
Vector2& operator *= (const float f, Vector2& v);
Vector2 operator / (const Vector2& v, const float f);
Vector2 operator / (const float f, const Vector2& v);
Vector2& operator /= (Vector2& v, const float f);
Vector2 operator - (const Vector2& v);