#pragma once
#include "MathsInclude.h"

//無限線分クラス
class Ray {
public:
	//コンストラクタ
	Ray(const Vector3& position, const Vector3& direction);
	//デフォルトコンストラクタ
	Ray();
public:
	//座標
	Vector3 position;
	//方向
	Vector3 direction;
};
