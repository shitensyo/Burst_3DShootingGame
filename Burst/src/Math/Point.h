#pragma once

#include <string>

class Vector2;


//二次元座標クラス

class Point
{
public:
	int x;
	int y;
public:
	
	//(0, 0)で初期化された二次元座標を返す	
	static Point Zero;
	
	//(1, 1)で初期化された二次元座標を返す	
	static Point One;
	
	//(-1, 0)で初期化された二次元座標を返す	
	static Point Left;
	
	//(1, 0)で初期化された二次元座標を返す	
	static Point Right;
	
	//(0, -1)で初期化された二次元座標を返す	
	static Point Up;
	
	//(0, 1)で初期化された二次元座標を返す	
	static Point Down;
	
	//画面中央の座標で初期化された二次元座標を返す	
	static Point WindowCenter();
public:
	
	//コンストラクタ	
	Point();

	//コンストラクタ	
	Point(int x, int y);
	
	//コンストラクタ	
	Point(const Point& vec);
	
	//コンストラクタ	
	Point(int s);
public:
	
	//長さを返す	
	float Length() const;
	
	//長さの二乗を返す	
	float LengthPow2() const;
	
	//二点間の距離を返す	
	float Distance(const Point& other) const;

public:
	Point& operator = (const Point& v);
	operator Vector2() const;
	operator std::string() const;
};

bool operator == (const Point& v1, const Point& v2);
bool operator != (const Point& v1, const Point& v2);
Point operator + (const Point& v1, const Point& v2);
Point& operator += (Point& v1, const Point& v2);
Point operator - (const Point& v1, const Point& v2);
Point& operator -= (Point& v1, const Point& v2);
Point operator * (const Point& v, const int f);
Point operator * (const int f, const Point& v);
Point& operator *= (Point& v, const int f);
Point& operator *= (const int f, Point& v);
Point operator / (const Point& v, const int f);
Point operator / (const int f, const Point& v);
Point& operator /= (Point& v, const int f);
Point operator - (const Point& v);
