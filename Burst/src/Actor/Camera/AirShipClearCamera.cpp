#include "AirShipClearCamera.h"
#include "../../World/IWorld.h"

static const float CHANGE_TIME = 2.0f;
static const float MOVE_SPEED = 180.0f;

AirShipClearCamera::AirShipClearCamera(IWorld* world) :
	Actor(world, "AirShipClearCamera", Vector3::Zero, BoundingSphere(1.0)),
	timer(0.0f),
	target(Vector3::Zero),
	positionNum(0)
{
	positions.push_back(Vector3(-200, 200, -900));
	positions.push_back(Vector3(250, 300, 800));
	positions.push_back(Vector3(300, 200, -800));

	position = positions.at(0);
}

void AirShipClearCamera::OnUpdate(float deltaTime)
{
	if (positionNum < positions.size() - 1)
	{
		timer += deltaTime;
		if (timer > CHANGE_TIME)
		{
			timer = 0.0f;
			positionNum++;
			position = positions.at(positionNum);
		}
	}

	if (positionNum != 2) return;
	position += Vector3::Normalize(position) * MOVE_SPEED * deltaTime;
}

void AirShipClearCamera::OnDraw() const 
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		position.x, position.y, position.z,
		target.x, target.y, target.z,
		0.0f, 1.0f, 0.0f
	);
}
