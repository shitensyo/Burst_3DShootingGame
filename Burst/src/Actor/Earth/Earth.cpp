#include "Earth.h"
#include "../AssetID.h"

static const float SPEED_Y = 60.0f;
static const float SPEED_Z = 30.0f;
static const float MODEL_SCALE = 1.1f;

Earth::Earth(IWorld * world, const Vector3 & position) :
	Actor(world, "Earth", position, BoundingSphere(1.0f)),
	rotateY(90.0f),
	rotateZ(0.0f)
{
}

void Earth::OnUpdate(float deltaTime)
{
	//‰ñ“]
	rotateY += SPEED_Y * deltaTime;
	rotateZ += SPEED_Z * deltaTime;
	rotate = Matrix4::RotateZ(rotateZ) * Matrix4::RotateX(rotateY);
}

void Earth::OnDraw() const
{
	glPushMatrix();
	glMultMatrixf(Matrix4::Scale(Vector3(MODEL_SCALE)).ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::EARTH_MODEL);
	glPopMatrix();
}

void Earth::OnCollide(Actor & other, const HitInfo & info)
{
}
