#include "Line.h"

//コンストラクタ
Line::Line(const Vector3& start, const Vector3& end) :
  start(start), end(end) {
}

//デフォルトコンストラクタ
Line::Line() :
	Line({ 0.0f, 0.0f ,0.0f }, { 0.0f, 0.0f, 0.0f }) {
}
