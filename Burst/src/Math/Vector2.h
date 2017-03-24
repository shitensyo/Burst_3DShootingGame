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
	
	//(0, 0)�ŏ��������ꂽ�x�N�g����Ԃ�
	
	static Vector2 Zero;
	
	//(1, 1)�ŏ��������ꂽ�x�N�g����Ԃ�
	
	static Vector2 One;
	
	//(-1, 0)�ŏ��������ꂽ�x�N�g����Ԃ�
	
	static Vector2 Left;
	
	//(1, 0)�ŏ��������ꂽ�x�N�g����Ԃ�
	
	static Vector2 Right;
	
	//(0, -1)�ŏ��������ꂽ�x�N�g����Ԃ�
	
	static Vector2 Up;
	
	//(0, 1)�ŏ��������ꂽ�x�N�g����Ԃ�
	
	static Vector2 Down;
	
	//��ʒ����̍��W�ŏ��������ꂽ�x�N�g����Ԃ�
	
	static Vector2 WindowCenter;
public:
	
	//�R���X�g���N�^
	
	Vector2();
	
	//�R���X�g���N�^
	
	Vector2(float x, float y);
	
	//�R���X�g���N�^
	
	Vector2(int x, int y);
	
	//�R���X�g���N�^
	
	Vector2(const Vector2& vec);
	
	//�R���X�g���N�^
	
	Vector2(const GSvector2& vec);
	
	//�R���X�g���N�^
	
	Vector2(float s);
	
	//�R���X�g���N�^
	
	Vector2(int s);
public:
	
	//���g�̃x�N�g���̑傫���i�����j��Ԃ�
	
	float Length() const;
	
	//���g�̃x�N�g���̑傫���i�����j�̓���Ԃ�
	
	float LengthPow2() const;
	
	//�Q�_�Ԃ̋�����Ԃ�
	
	float Distance(const Vector2& other) const;
	
	//�Q�_�Ԃ̋����̓���Ԃ�
	
	float DistancePow2(const Vector2& other) const;
	
	//���g�̃x�N�g���𐳋K������
	
	void Normalize();
	
	//���g�̐��K�����ꂽ�x�N�g����Ԃ�
	
	Vector2 Normalized() const;
	
	//���g�Ƒ���̃x�N�g���̓��ς�Ԃ�
	
	float Dot(const Vector2& v) const;
	
	//���g�Ƒ���̃x�N�g���̂Ȃ��p��Ԃ�
	
	float Inner(const Vector2& v) const;
public:
	
	//�x�N�g���𐳋K������
	
	static Vector2 Normalize(const Vector2& v);
	
	//�Q�_�Ԃ̋�����Ԃ�
	
	static float Distance(const Vector2& v1, const Vector2& v2);
	
	//�Q�_�Ԃ̋����̓���Ԃ�
	
	static float DistancePow2(const Vector2& v1, const Vector2& v2);
	
	//�Q�̃x�N�g���̓��ς�Ԃ�
	
	static float Dot(const Vector2& v1, const Vector2& v2);
	
	//�Q�̃x�N�g���̂Ȃ��p��Ԃ�
	
	static float Inner(const Vector2& v1, const Vector2& v2);
	
	//��̃x�N�g���̊O�ς�Ԃ�
	
	static float Cross(const Vector2& v1, const Vector2& v2);
	///<summary>
	//��̃x�N�g���Ԃ̐��`��Ԃ���
	///</summary>
	static Vector2 Lerp(const Vector2& start, const Vector2& end, float amount);
	
public:
	///<summary>
	//Vector2�^��Point�^�ɕϊ����ĕԂ�
	///</summary>
	static Point ToPoint(const Vector2& v);
	///<summary>
	//���g��Point�^�ɕϊ��������̂�Ԃ�
	///</summary>
	Point ToPoint() const;
	///<summary>
	//Vector2�^��GSvector2�^�ɕϊ����ĕԂ�
	///</summary>
	static GSvector2 ToGSvector2(const Vector2& v);
	///<summary>
	//���g��GSvector2�^�ɕϊ��������̂�Ԃ�
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