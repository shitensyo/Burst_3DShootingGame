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
	
	//�R���X�g���N�^	
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	
	//�R���X�g���N�^	
	Quaternion(const Vector3& v, float angle);
	
	//�R���X�g���N�^(��]�s�񂩂�N�E�H�[�^�j�I�����쐬)	
	Quaternion(const Matrix4& m);

public:
	
	//���ς�Ԃ�	
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	
	//�傫���i�����j��Ԃ�	
	static float Length(const Quaternion& q);
	
	//���K��������	
	static Quaternion Normalize(const Quaternion& q);
	
	//���ʐ��`���	
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);
	
	//�N�H�[�^�j�I������]�s��ɂ��ĕԂ�	
	static Matrix4 Rotate(const Quaternion& q);
	
	//�C�ӎ�����̉�]�s���Ԃ�	
	static Matrix4 RotateAxis(const Vector3& v, float angle);

public:
	//Quaternion�^��Matrix4�^�ɕϊ�����
	Matrix4 ToMatrix4(const Quaternion& q);
	//���g��Matrix4�^�ɕϊ��������̂�Ԃ�
	Matrix4 ToMatrix4() const;
	//Matrix4�^��Quaternion�^�ɕϊ�����
	Quaternion ToQuaternion(const Matrix4& m);
};

// �P�����Z�q�I�[�o�[���[�h
Quaternion operator + (const Quaternion& q);
Quaternion operator - (const Quaternion& q);
// ������Z�q�I�[�o�[���[�h
Quaternion& operator += (Quaternion& q1, const Quaternion& q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion& q2);
Quaternion& operator *= (Quaternion& q, float s);
Quaternion& operator /= (Quaternion& q, float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);
// �Q�����Z�q�I�[�o�[���[�h
Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q, float s);
Quaternion operator * (float s, const Quaternion& q);
Quaternion operator / (const Quaternion& q, float s);