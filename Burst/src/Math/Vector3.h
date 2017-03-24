#pragma once

#include <gslib.h>
#include <string>

class Vector3
{
public:
	float x;
	float y;
	float z;

public:
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector3();
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector3(float s);
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector3(float x, float y);
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector3(float x, float y, float z);
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector3(int s);
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector3(int x, int y);
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector3(int x, int y, int z);
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector3(const Vector3& vector);
	///<summary>
	//�R���X�g���N�^
	///</summary>
	Vector3(const GSvector3& vector);

public:
	///<summary>
	//(0,0,0)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Zero;
	///<summary>
	//(1,1,1)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 One;
	///<summary>
	//(0,1,0)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Up;
	///<summary>
	//(0,-1,0)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Down;
	///<summary>
	//(-1,0,0)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Left;
	///<summary>
	//(1,0,0)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Right;
	///<summary>
	//(0,0,1)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Forward;
	///<summary>
	//(0,0,-1)�ŏ��������ꂽ�x�N�g��
	///</summary>
	static Vector3 Backward;

	//�F
	static Vector3 White;
	static Vector3 Black;
	static Vector3 Blue;
	static Vector3 Red;
	static Vector3 Green;

public:
	///<summary>
	//���g�̃x�N�g���̑傫���i�����j��Ԃ�
	///</summary>
	float Length() const;
	///<summary>
	//���g�̃x�N�g���𐳋K������
	///</summary>
	void Normalize();
	///<summary>
	//���g�̐��K�����ꂽ�x�N�g����Ԃ�
	///</summary>
	Vector3 Normalized() const;
	///<summary>
	//���g�̒l�𐧌�����
	///</summary>
	void Clamp(const Vector3& min, const Vector3& max);

public:
	///<summary>
	//�x�N�g���̑傫���i�����j��Ԃ�
	///</summary>
	static float Length(const Vector3& v);
	///<summary>
	//�Q�_�Ԃ̋�����Ԃ�
	///</summary>
	static float Distance(const Vector3& v1, const Vector3& v2);
	///<summary>
	//�x�N�g���𐳋K�����ĕԂ�
	///</summary>
	static Vector3 Normalize(const Vector3& v);
	///<summary>
	//�Q�̃x�N�g���̓��ς�Ԃ�
	///</summary>
	static float Dot(const Vector3& v1, const Vector3& v2);
	///<summary>
	//�Q�̃x�N�g���̊O�ς�Ԃ�
	///</summary>
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);
	///<summary>
	//�Q�̃x�N�g���̂Ȃ��p��Ԃ�
	///</summary>
	static float Inner(const Vector3& v1, const Vector3& v2);
	///<summary>
	//�O�̃x�N�g����Ԃ�(���W�A��]��)
	///</summary>
	static Vector3 FrontVec(Vector3& position, Vector3& rotation);
	///<summary>
	//��̃x�N�g���Ԃ̐��`��Ԃ�����
	///</summary>
	static Vector3 Lerp(const Vector3& start, const Vector3& end, float amount);
	///<summary>
	//�o�l�̗͂�������(���݂̈ʒu,�o�l�̌��݂̈ړ����x,�o�l�̐Î~�ʒu,�o�l�萔,�o�l�̋���,���C��,����)
	///</summary>
	static void Spring(Vector3& position, Vector3& velocity, const Vector3& restPosition, float stiffness, float friction, float mass);
	///<summary>
	//�s�b�`�����߁A���W�A���ŕԂ�
	///</summary>
	static float Pitch(const Vector3& front);
	///<summary>
	//���[�����߁A���W�A���ŕԂ�
	///</summary>
	static float Yaw(const Vector3& front);
	///<summary>
	//���W������W�֌������P�ʃx�N�g����Ԃ�
	///</summary>
	static Vector3 Direction(const Vector3& start, const Vector3& end);
	///<summary>
	//�l�𐧌�����
	///</summary>
	static Vector3 Clamp(const Vector3& value, const Vector3& min, const Vector3& max);
	///<summary>
	//���ʊp�C�p����x�N�g�������߂�D
	///</summary>
	static Vector3 CreateFromEleDir(float elavation, float direction);
	///<summary>
	//���ʊp�C�p����x�N�g�������߂�D
	///</summary>
	static Vector3 CreateFromPitchYaw(float pitch, float yaw);

public:
	///<summary>
	//Vector3�^��GSvector3�^�ɕϊ����ĕԂ�
	///</summary>
	static GSvector3 ToGSvector3(const Vector3& v);
	///<summary>
	//���g��GSvector3�^�ɕϊ��������̂�Ԃ�
	///</summary>
	GSvector3 ToGSvector3() const;

public:
	Vector3& operator = (const GSvector3& v);
	operator std::string() const;
	operator GSvector3() const;
};

Vector3 operator + (const Vector3& v1, const Vector3& v2);
Vector3& operator += (Vector3& v1, const Vector3& v2);
Vector3 operator - (const Vector3& v1, const Vector3& v2);
Vector3& operator -= (Vector3& v1, const Vector3& v2);
Vector3 operator * (const Vector3& v, const float f);
Vector3 operator * (const float f, const Vector3& v);
Vector3 operator * (const Vector3& v1, const Vector3& v2);
Vector3& operator *= (Vector3& v, const float f);
Vector3& operator *= (const float f, Vector3& v);
Vector3 operator / (const Vector3& v, const float f);
Vector3 operator / (const float f, const Vector3& v);
Vector3 operator / (const Vector3& v1, const Vector3& v2);
Vector3& operator /= (Vector3& v, const float f);
Vector3 operator - (const Vector3& v);
bool operator != (const Vector3& v1, const Vector3& v2);