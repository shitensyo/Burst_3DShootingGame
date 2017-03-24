#include "HitSmoke.h"
#include "../Base/ActorGroup.h"
#include "MissileSmoke.h"

const int SMOKE_MAX = 5;

HitSmoke::HitSmoke(IWorld* world_, const Vector3& position_) :
	Actor(world_, "Explosion", position_, BoundingSphere(0.0f)),
	smokeNum(SMOKE_MAX)
{

}

void HitSmoke::OnUpdate(float deltaTime)
{
	//ê∂ê¨
	for (int i = 0; i < smokeNum; ++i) {
		//î≠éÀï˚å¸ÇåvéZ
		auto pitch = gsRandf(180.0f, 360.0f);
		auto yaw = gsRandf(0.0f, 360.0f);
		Vector3 velocity = Vector3::CreateFromPitchYaw(pitch, yaw) * gsRandf(80.0f, 100.0f);
		world->AddActor(ActorGroup::Effect, std::make_shared<MissileSmoke>(world, position, velocity));
	}
	Dead();
}
