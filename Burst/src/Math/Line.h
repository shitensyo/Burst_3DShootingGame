#pragma once

#include "MathsInclude.h"

//�����N���X
class Line {
public:
	//�R���X�g���N�^
	Line(const Vector3& start, const Vector3& end);
	//�f�t�H���g�R���X�g���N�^
	Line();
public:
	//�n�_
	Vector3	start;
	//�I�_
	Vector3	end;
};
