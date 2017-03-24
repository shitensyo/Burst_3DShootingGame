#pragma once

#include "MathsInclude.h"

//線分クラス
class Line {
public:
	//コンストラクタ
	Line(const Vector3& start, const Vector3& end);
	//デフォルトコンストラクタ
	Line();
public:
	//始点
	Vector3	start;
	//終点
	Vector3	end;
};
