#include "DashLine.h"
#include "../AssetID.h"

static const float LIFE_TIME = 0.5f;

DashLine::DashLine(IWorld * world, const Vector2 & position_, float speed_):
	Actor(world, "DashLine", Vector3::Zero, BoundingSphere(0.0)),
	timer(0.0f),
	spritePosition(position_),
	angle(gsRandf(0.0f,360.0f)),
	alpha(0.0f)
{
	//Šp“x‚©‚çis•ûŒü‚ðŒvŽZ
	velocity = Vector2(Math::Cos(angle), Math::Sin(angle)) * speed_;
}

void DashLine::OnUpdate(float deltaTime)
{
	timer += deltaTime;
	alpha += deltaTime / LIFE_TIME;
	if (timer > LIFE_TIME)
		Dead();

	spritePosition += velocity * deltaTime;
}

void DashLine::OnDraw() const
{
	gsDrawSprite2D(TEXTURE_ID::DASH_LINE_TEXTURE, &spritePosition.ToGSvector2(), &GSrect(0, 0, 256, 16), NULL, &GScolor(1,1,1, alpha), &GSvector2(1.0f, 1.0f), angle);
}
