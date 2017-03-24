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

	//�[���s���Ԃ�
	static Matrix4 Zero;

	//�P�ʍs���Ԃ�
	static Matrix4 Identity;

public:

	//�R���X�g���N�^
	Matrix4();

	//�R���X�g���N�^
	Matrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	//�R���X�g���N�^
	Matrix4(Vector4 v0, Vector4 v1, Vector4 v2, Vector4 v3);

public:

	//���g�̍��W��Ԃ�
	Vector3 GetPosition() const;

	//���g�̉���Ԃ�
	Vector3 GetLeft() const;

	//���g�̏��Ԃ�
	Vector3 GetUp() const;

	//���g�̑O��Ԃ�
	Vector3 GetFront() const;

	//���g�̃X�P�[����Ԃ�
	Vector3 GetScale() const;

	//���g�̊e���̉�]�ʂ����W�A���ŕԂ�
	Vector3 GetRotate() const;

	//���g�̊e���̉�]�ʂ��p�x�ŕԂ�
	Vector3 GetRotateDegree() const;

	//���W���Z�b�g����
	void SetPosition(const Vector3& position);

	//�����Z�b�g����
	void SetLeft(const Vector3& left);

	//����Z�b�g����
	void SetUp(const Vector3& up);

	//�O���Z�b�g����
	void SetFront(const Vector3& front);

	//��]�s��X���Z�b�g����
	void SetRotateX(float angle);

	//��]�s��Y���Z�b�g����
	void SetRotateY(float angle);

	//��]�s��Z���Z�b�g����
	void SetotateZ(float angle);

public:

	//�g��k���s��
	static Matrix4 Scale(const Vector3& s);

	//��]�s��X
	static Matrix4 RotateX(float angle);

	//��]�s��Y
	static Matrix4 RotateY(float angle);

	//��]�s��Z
	static Matrix4 RotateZ(float angle);

	//���s�ړ��s��
	static Matrix4 Translate(const Vector3& pos);

	//�}�g���b�N�X���쐬���� �X�P�[���@X���@Y���@Z���@�ړ���
	static Matrix4 CreateMatrix(const Vector3& s = Vector3::One, const float& rototeXangle = 0, const float& rotateYangle = 0, const float& rotateZangle = 0, const Vector3& pos = Vector3::Zero);

	//�}�g���b�N�X���쐬����
	static Matrix4 CreateMatrix(const Matrix4& scale_ = Identity, const Matrix4& rotateX_ = Identity, const Matrix4& rotateY_ = Identity, const Matrix4& rotateZ_ = Identity, const Matrix4& translate_ = Identity);

	//�x�N�g���̍��W�ϊ�(�x�N�g���ƍs��̐�)
	static Vector3 Transform(const Vector3& v, const Matrix4& m);

	//�x�N�g���̍��W�ϊ�(��]�̂�)
	static Vector3 TransformRotateOnly(const Vector3& v, const Matrix4& m);

	//�]�u�s��
	static Matrix4 Transpose(const Matrix4& m);
	static Matrix4 TransposeRotateOnly(const Matrix4& m);

	//�t�s��(�g�k����)
	static Matrix4 InverseFast(const Matrix4& m);

	//�t�s��
	static Matrix4 Inverse(const Matrix4& m);


public:
	//���[���h�s����쐬���쐬����
	static Matrix4 World(const Vector3& scale, const Matrix4& rotation, const Vector3& translation);
	//���[���h�s����쐬���쐬����
	static Matrix4 World(const Vector3& position, const Vector3& forward, const Vector3& up);
	//����ϊ��s��(�r���[�s��)���쐬����
	static Matrix4 LookAt(const Vector3& eye, const Vector3& at, const Vector3& up);
	//�����ϊ��s����쐬����
	static Matrix4 Perspective(float fov, float aspect, float zn, float zf);
	//�X�N���[�����W�ϊ��s����쐬����
	static Matrix4 Screen(float x, float y, float width, float height);

public:

	//���W��Ԃ�
	static Vector3 GetPosition(const Matrix4& m);

	//����Ԃ�
	static Vector3 GetLeft(const Matrix4& m);

	//���Ԃ�
	static Vector3 GetUp(const Matrix4& m);

	//�O��Ԃ�
	static Vector3 GetFront(const Matrix4& m);

	//�X�P�[����Ԃ�
	static Vector3 GetScale(const Matrix4& m);

	//�e���̉�]�ʂ����W�A���Ԃ�
	static Vector3 GetRotate(const Matrix4& m);

	//�e���̉�]�ʂ��p�x�ŕԂ�
	static Vector3 GetRotateDegree(const Matrix4& m);

	//���W���Z�b�g�����s���Ԃ�
	static Matrix4 SetPosition(Matrix4& m, const Vector3& position);

	//�����Z�b�g�����s���Ԃ�
	static Matrix4 SetLeft(Matrix4& m, const Vector3& left);

	//����Z�b�g�����s���Ԃ�
	static Matrix4 SetUp(Matrix4& m, const Vector3& up);

	//�O���Z�b�g�����s���Ԃ�
	static Matrix4 SetFront(Matrix4& m, const Vector3& front);

	//���ʐ��`���
	static Matrix4 Slerp(const Matrix4& start, const Matrix4& end, float t);

	//���`���
	static Matrix4 Lerp(const Matrix4& start, const Matrix4& end, float t);

	//�s�b�`�p(���E���A�㉺������]��)�����߂�
	static float Pitch(const Matrix4& m);

	//���[�p(�㉺���A�O�������]��)�����߂�
	static float Yaw(const Matrix4& m);

	//���[���p(�O�㎲�A���E������]��)�����߂�
	static float Roll(const Matrix4& m);


	//�X�N���[���ϊ�
	static Vector3 Project(const Vector3& position,
		const Matrix4& screen,
		const Matrix4& projection,
		const Matrix4& view,
		const Matrix4& world = Identity);

	//��ʂ̍��W���烍�[�J�����W�����߂�
	static Vector3 UnProject(const Vector3& position,
		const Matrix4& screen,
		const Matrix4& projection,
		const Matrix4& view,
		const Matrix4& world = Identity);

	//��]�s��̐��K��
	static Matrix4 NormalizeRotate(const Matrix4& m);

public:
	//Matrix4�^��GSmatrix4�^�ɕϊ����ĕԂ�
	static GSmatrix4 ToGSmatrix4(const Matrix4& m);
	//���g��GSmatrix4�^�ɕϊ��������̂�Ԃ�
	GSmatrix4 ToGSmatrix4() const;
	//GSmatrix4�^��Matrix4�^�ɕϊ����ĕԂ�
	static Matrix4 ToMatrix4(const GSmatrix4& m);

public:
	Matrix4& operator = (const Matrix4& m_);
	operator std::string() const;
};

Matrix4& operator *= (Matrix4& m1, const Matrix4& m2);
Matrix4 operator * (const Matrix4& m1, const Matrix4& m2);
Vector3 operator * (const Vector3& v, const Matrix4& m);