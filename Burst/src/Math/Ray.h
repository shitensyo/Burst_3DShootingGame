#pragma once
#include "MathsInclude.h"

//���������N���X
class Ray {
public:
	//�R���X�g���N�^
	Ray(const Vector3& position, const Vector3& direction);
	//�f�t�H���g�R���X�g���N�^
	Ray();
public:
	//���W
	Vector3 position;
	//����
	Vector3 direction;
};
