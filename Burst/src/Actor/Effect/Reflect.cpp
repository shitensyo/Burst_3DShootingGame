#include "Reflect.h"
#include "../AssetID.h"

//寿命
static const float LIFE_TIME = 1.0f;
static const float INIT_SCALE = 1.0f;

Reflect::Reflect(IWorld * world_, const Vector3 & position_, float finalScale_):
	Actor(world_, "Reflect", position_, BoundingSphere(0.0f)),
	timer(0.0f),
	scale(INIT_SCALE),
	finalScale(finalScale_)
{

}

void Reflect::OnUpdate(float deltaTime)
{
	if (timer >= LIFE_TIME)
		Dead();
	timer += deltaTime;

	//徐々に大きくなる
	scale = Math::Lerp(INIT_SCALE, finalScale, timer / LIFE_TIME);
}

void Reflect::OnDraw() const
{
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glDepthMask(GL_FALSE);
	//加算+アルファ合成(saiでいうスクリーンレイヤー)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	static const GSrect body(-4.0f, 4.0f, 4.0f, -4.0f);
	GScolor color(1.0f, 1.0f, 1.0f, (LIFE_TIME - timer) / LIFE_TIME);
	gsDrawSprite3D(TEXTURE_ID::REFLECT_TEXTURE, &position.ToGSvector3(), &body, NULL, &color, &GSvector2(scale, scale), 0.0f);
	glPopAttrib();
}
