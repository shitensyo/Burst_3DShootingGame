#include "BasicTexture.h"

BasicTexture::BasicTexture(IWorld * world, int texID_, const Vector2& position_, float alpha_):
	Actor(world, "Texture", { position_.x, position_.y, 0.0f }, BoundingSphere(0.0f)),
	texID(texID_),
	alpha(alpha_)
{
}

void BasicTexture::OnMessage(EventMessage event, void *)
{
}

void BasicTexture::OnUpdate(float deltaTime)
{
}

void BasicTexture::OnDraw() const
{
	gsDrawSprite2D(texID, &GSvector2(position.x,position.y), NULL, NULL, &GScolor(1.0f,1.0f,1.0f, alpha), NULL, 0);
}
