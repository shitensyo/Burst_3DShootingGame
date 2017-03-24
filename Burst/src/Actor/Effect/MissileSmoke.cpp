#include "MissileSmoke.h"
#include "../AssetID.h"

MissileSmoke::MissileSmoke(IWorld* world_, const Vector3& position_, const Vector3& velocity_) :
	Actor(world_, "MissileSmoke", position_, BoundingSphere(0.0f)),
	angle(gsRandf(0.0f,360.0f)),
	velocity(velocity_),
	timer(0.0f),
	endTime(0.4f)
{

}

MissileSmoke::MissileSmoke(IWorld* world_, const Vector3& position_, const Vector3& velocity_, float endTime_) :
	Actor(world_, "MissileSmoke", position_, BoundingSphere(0.0f)),
	angle(gsRandf(0.0f, 360.0f)),
	velocity(velocity_),
	timer(0.0f),
	endTime(endTime_)
{

}

void MissileSmoke::OnUpdate(float deltaTime)
{
	position += velocity * deltaTime;

	if (timer >= endTime)
		Dead();
	timer += deltaTime;
}

void MissileSmoke::OnDraw() const
{
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);
	//アルファブレンド
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	static const GSrect body(-4.0f, 4.0f, 4.0f, -4.0f);
	GScolor color(1.0f, 1.0f, 1.0f, (endTime - timer) / endTime);
	gsDrawSprite3D(TEXTURE_ID::SMOKE_TEX, &position.ToGSvector3(), &body, NULL, &color, &GSvector2(2.0f, 2.0f), angle);
	glPopAttrib();
}
