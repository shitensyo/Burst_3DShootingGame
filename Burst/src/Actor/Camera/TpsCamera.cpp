#include "TpsCamera.h"
#include "../../World/IWorld.h"

TpsCamera::TpsCamera(IWorld* world, float targetLengthY_, float targetLengthZ_) :
	Actor(world, "Camera", {0.0f, 0.0f, 0.0f}, BoundingSphere(1.0)),
	player(nullptr),
	target(Vector3::Zero),
	velocity(Vector3::Zero),
	targetLengthY(targetLengthY_),
	targetLengthZ(targetLengthZ_)
{

}

TpsCamera::TpsCamera(IWorld * world, const Vector3 & position) :
	Actor(world, "Camera", position, BoundingSphere(1.0)),
	player(nullptr),
	target(Vector3::Zero),
	velocity(Vector3::Zero),
	lookat(Matrix4::Identity),
	targetLengthY(10.0f),
	targetLengthZ(50.0f)
{
	player = world->GetPlayer();
}

void TpsCamera::OnUpdate(float) 
{
	player = world->GetPlayer();
	if (player == nullptr) return;
	Vector3 position = Vector3(0.0f, targetLengthY, -targetLengthZ) * player->GetPose();
	target = player->GetPosition() + player->GetRotate().GetFront() * 10.0f;
	Move(position, 0.5f, 0.1f, 0.8f);

	lookat = Matrix4::LookAt(position, target, Vector3::Up);
	world->SetLookAt(lookat);
}

void TpsCamera::OnDraw() const 
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		position.x, position.y, position.z,
		target.x, target.y, target.z,
		0.0f, 1.0f, 0.0f
	);
}

Matrix4 TpsCamera::GetLookAt()
{
	return lookat;
}

void TpsCamera::Move(
	const Vector3& restPosition,
	float stiffness,
	float friction,
	float mass)
{
	//バネの伸び具合を計算
	Vector3 stretch = position - restPosition;
	//バネの力を計算
	Vector3 force = -stiffness * stretch;
	//加速度を計算
	Vector3 acceleration = force / mass;
	//移動量を計算
	velocity = friction * (velocity + acceleration);
	//座標の更新
	position += velocity;
}
