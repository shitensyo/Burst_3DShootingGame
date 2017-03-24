#include "TitleCamera.h"

TitleCamera::TitleCamera(IWorld * world, const Vector3& position, const Vector3& target_):
	Actor(world, "TitleCamera", position, BoundingSphere(1.0)),
	target(target_)
{
}

void TitleCamera::OnUpdate(float deltaTime)
{
}

void TitleCamera::OnDraw() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		position.x, position.y, position.z,
		target.x, target.y, target.z,
		0.0f, 1.0f, 0.0f
		);
}
