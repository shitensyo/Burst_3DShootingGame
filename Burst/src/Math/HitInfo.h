#pragma once

#include "Vector3.h"

//当たり判定で返す情報
struct HitInfo
{
	//当たったか？
	bool isHit;
	//当たった地点
	Vector3 point;
	//相手の地点
	Vector3 otherPoint;
};