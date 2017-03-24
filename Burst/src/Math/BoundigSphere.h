#pragma once

#include <gslib.h>
#include "../Math/MathsInclude.h"
#include "HitInfo.h"

//“–‚½‚è”»’è‹…
class BoundingSphere
{
public:
	BoundingSphere(const Vector3& center, float radius);

	explicit BoundingSphere(float radius = 0.0f);

	BoundingSphere Translate(const Vector3& position) const;

	BoundingSphere Transform(const Matrix4& matrix) const;

	HitInfo Intersects(const BoundingSphere& other) const;

	void Draw() const;

public:
	//’†SÀ•W
	Vector3	center;
	//”¼Œa
	float radius;
};

