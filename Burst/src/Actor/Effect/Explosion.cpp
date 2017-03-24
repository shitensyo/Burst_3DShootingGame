#include "Explosion.h"
#include "../Base/ActorGroup.h"
#include "Fire.h"

//âŒÇÃêîÅ@äÓñ{
const int FIRE_MAX = 20;

Explosion::Explosion(IWorld* world_, const Vector3& position_, const Vector3& velocity_) :
	Actor(world_, "Explosion", position_, BoundingSphere(0.0f)),
	fireNum(FIRE_MAX),
	lifetime(0.5f),
	velocity(velocity_),
	power(280.0f),
	attenuation(0.8f),
	scale(5.0f)
{
	
}
Explosion::Explosion(IWorld* world_, const Vector3& position_, const Vector3& velocity_, int fireNum_) :
	Actor(world_, "Explosion", position_, BoundingSphere(0.0f)),
	fireNum(fireNum_),
	lifetime(0.5f),
	velocity(velocity_),
	power(280.0f),
	attenuation(0.8f),
	scale(5.0f)
{

}

Explosion::Explosion(IWorld * world_, const Vector3 & position_, const Vector3 & velocity_, int fireNum_, float lifetime_, float power_, float attenuation_, float scale_) :
	Actor(world_, "Explosion", position_, BoundingSphere(0.0f)),
	fireNum(fireNum_),
	velocity(velocity_),
	lifetime(lifetime_),
	power(power_),
	attenuation(attenuation_),
	scale(scale_)
{
}

void Explosion::OnUpdate(float deltaTime) 
{
	//âäÇê∂ê¨Ç∑ÇÈ
	for (int i = 0; i < fireNum; ++i) {
		world->AddActor(ActorGroup::Effect, std::make_shared<Fire>(world, position, velocity, lifetime, power, attenuation, scale));
	}
	Dead();
}
