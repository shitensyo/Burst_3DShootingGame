#include "Line.h"

//�R���X�g���N�^
Line::Line(const Vector3& start, const Vector3& end) :
  start(start), end(end) {
}

//�f�t�H���g�R���X�g���N�^
Line::Line() :
	Line({ 0.0f, 0.0f ,0.0f }, { 0.0f, 0.0f, 0.0f }) {
}
