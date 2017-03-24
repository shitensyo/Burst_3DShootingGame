#pragma once

#include <string>

class Vector2;


//�񎟌����W�N���X

class Point
{
public:
	int x;
	int y;
public:
	
	//(0, 0)�ŏ��������ꂽ�񎟌����W��Ԃ�	
	static Point Zero;
	
	//(1, 1)�ŏ��������ꂽ�񎟌����W��Ԃ�	
	static Point One;
	
	//(-1, 0)�ŏ��������ꂽ�񎟌����W��Ԃ�	
	static Point Left;
	
	//(1, 0)�ŏ��������ꂽ�񎟌����W��Ԃ�	
	static Point Right;
	
	//(0, -1)�ŏ��������ꂽ�񎟌����W��Ԃ�	
	static Point Up;
	
	//(0, 1)�ŏ��������ꂽ�񎟌����W��Ԃ�	
	static Point Down;
	
	//��ʒ����̍��W�ŏ��������ꂽ�񎟌����W��Ԃ�	
	static Point WindowCenter();
public:
	
	//�R���X�g���N�^	
	Point();

	//�R���X�g���N�^	
	Point(int x, int y);
	
	//�R���X�g���N�^	
	Point(const Point& vec);
	
	//�R���X�g���N�^	
	Point(int s);
public:
	
	//������Ԃ�	
	float Length() const;
	
	//�����̓���Ԃ�	
	float LengthPow2() const;
	
	//��_�Ԃ̋�����Ԃ�	
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
