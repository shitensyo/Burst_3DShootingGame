#pragma once

#include "Vector3.h"

//�����蔻��ŕԂ����
struct HitInfo
{
	//�����������H
	bool isHit;
	//���������n�_
	Vector3 point;
	//����̒n�_
	Vector3 otherPoint;
};