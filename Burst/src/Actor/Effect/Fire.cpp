#include "Fire.h"
#include "../AssetID.h"

static const float FIRE_END_TIME = 0.5f;

Fire::Fire(IWorld* world_, const Vector3& position_, const Vector3& velocity_) :
	Actor(world_, "Fire", position_, BoundingSphere(0.0f)),
	rotation(gsRandf(0.0f, 360.0f)),
	flyVelocity(velocity_),
	velocity(Vector3::Zero),
	timer(0.0f),
	lifetime(FIRE_END_TIME),
	power(0.0f),
	attenuation(0.8f),
	scale(5.0f)
{
	float pitch = gsRandf(0.0f, 360.0f);
	float yaw   = gsRandf(0.0f, 360.0f);
	velocity = Vector3::CreateFromPitchYaw(pitch, yaw) * gsRandf(160.2f, 280.2f);
}

Fire::Fire(IWorld * world_, const Vector3 & position_, const Vector3 & velocity_, float power_) :
	Actor(world_, "Fire", position_, BoundingSphere(0.0f)),
	rotation(gsRandf(0.0f, 360.0f)),
	flyVelocity(velocity_),
	velocity(Vector3::Zero),
	timer(0.0f),
	lifetime(FIRE_END_TIME),
	power(power_),
	attenuation(0.8f),
	scale(5.0f)
{
	float pitch = gsRandf(0.0f, 360.0f);
	float yaw = gsRandf(0.0f, 360.0f);
	velocity = Vector3::CreateFromPitchYaw(pitch, yaw) * gsRandf(power * 0.4f, power);
}

Fire::Fire(IWorld * world_, const Vector3 & position_, const Vector3 & velocity_, float lifetime_, float power_, float attenuation_, float scale_) :
	Actor(world_, "Fire", position_, BoundingSphere(0.0f)),
	rotation(gsRandf(0.0f, 360.0f)),
	flyVelocity(velocity_),
	velocity(Vector3::Zero),
	timer(0.0f),
	lifetime(lifetime_),
	power(power_),
	attenuation(attenuation_),
	scale(gsRandf(scale_ * 0.6f,scale_))
{
	float pitch = gsRandf(0.0f, 360.0f);
	float yaw = gsRandf(0.0f, 360.0f);
	velocity = Vector3::CreateFromPitchYaw(pitch, yaw) * gsRandf(power * 0.4f, power);
}


void Fire::OnUpdate(float deltaTime)
{
	position += (flyVelocity + velocity) * deltaTime;
	flyVelocity *= 0.8f;
	velocity *= attenuation;

	timer += deltaTime;
	if (timer >= lifetime)
		Dead();
}

void Fire::OnDraw() const 
{
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);
	//加算+アルファ合成(saiでいうスクリーンレイヤー)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	static const GSrect body(-4.0f, 4.0f, 4.0f, -4.0f);
	GScolor color(1.0f, 1.0f, 1.0f, (lifetime - timer) / lifetime);
	gsDrawSprite3D(TEXTURE_ID::FIRE_TEX, &position.ToGSvector3(), &body, NULL, &color, &GSvector2(scale, scale), rotation);
	glPopAttrib();
}
