#include "BasicParticle.h"

BasicParticle::BasicParticle(IWorld* world_, const TEXTURE_ID& texID_, const Vector3& position_, const Vector3& velocity_, float scale_, float lifeTime_):
	Actor(world_, "BasicParticle", position_, BoundingSphere(0.0f)),
	texID(texID_),
	velocity(velocity_),
	lifeTime(lifeTime_),
	lifeTimer(0.0f),
	scale(scale_),
	angle(gsRandf(0.0f,360.0f))
{

}

void BasicParticle::OnUpdate(float deltaTime)
{
	//寿命
	if (lifeTimer >= lifeTime)
	{
		Dead();
		return;
	}
	lifeTimer += deltaTime;
		
	//移動
	position += velocity * deltaTime;
}

void BasicParticle::OnDraw() const
{
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);
	//アルファブレンド
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	static const GSrect body(-4.0f, 4.0f, 4.0f, -4.0f);
	GScolor color(1.0f, 1.0f, 1.0f, (lifeTime - lifeTimer) / lifeTime);
	gsDrawSprite3D(texID, &position.ToGSvector3(), &body, NULL, &color, &GSvector2(scale, scale), angle);
	glPopAttrib();
}
