#include "BoundigSphere.h"

BoundingSphere::BoundingSphere(const Vector3& center, float radius) :
	center(center),
	radius(radius) {
}

BoundingSphere::BoundingSphere(float radius) :
  BoundingSphere(Vector3::Zero, radius) {
}

BoundingSphere BoundingSphere::Translate(const Vector3& position) const {
	return { center + position, radius };
}

BoundingSphere BoundingSphere::Transform(const Matrix4& matrix) const {
	return { Matrix4::Transform(center,matrix), radius * matrix.GetScale().y };
}

HitInfo BoundingSphere::Intersects(const BoundingSphere& other) const {
	HitInfo info;
	info.isHit = gsCollisionSphereAndSphere(&center.ToGSvector3(), radius, &other.center.ToGSvector3(), other.radius);
	info.point = center;
	info.otherPoint = other.center;
	return info;
}

void BoundingSphere::Draw() const {
	glPushMatrix();
		glTranslatef(center.x, center.y, center.z);
		glutWireSphere(radius, 16, 16);
	glPopMatrix();
}
