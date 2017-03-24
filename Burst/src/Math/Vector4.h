#pragma once

#include <string>

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector4();
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector4(float x, float y, float z, float w);
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector4(float s);
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector4(int x, int y, int z, int w);
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector4(int s);
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector4(const Vector4& vector);

public:
	///<summary>
	//(0,0,0,0)�ŏ��������ꂽ�x�N�g����Ԃ�
	///</summary>
	static Vector4 Zero;
	///<summary>
	//(1,1,1,1)�ŏ��������ꂽ�x�N�g����Ԃ�
	///</summary>
	static Vector4 One;

public:
	Vector4& operator = (const Vector4& v);
	operator std::string() const;
};

Vector4 operator + (const Vector4& v1, const Vector4& v2);
Vector4& operator += (Vector4& v1, const Vector4& v2);
Vector4 operator - (const Vector4& v1, const Vector4& v2);
Vector4& operator -= (Vector4& v1, const Vector4& v2);
Vector4 operator * (const Vector4& v, const float f);
Vector4 operator * (const float f, const Vector4& v);
Vector4 operator * (const Vector4& v1, const Vector4& v2);
Vector4& operator *= (Vector4& v, const float f);
Vector4& operator *= (const float f, Vector4& v);
Vector4 operator / (const Vector4& v, const float f);
Vector4 operator / (const float f, const Vector4& v);
Vector4 operator / (const Vector4& v1, const Vector4& v2);
Vector4& operator /= (Vector4& v, const float f);
Vector4 operator - (const Vector4& v);