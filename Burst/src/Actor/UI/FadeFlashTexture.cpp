#include "FadeFlashTexture.h"

FadeFlashTexture::FadeFlashTexture(IWorld * world, int texID_,const Vector2& position_) :
	Actor(world, "FadeFlashTexture", { position_.x, position_.y, 0.0f }, BoundingSphere(0.0f)),
	texID(texID_),
	alpha(0.0f),
	timer(0.0f)
{
}

void FadeFlashTexture::OnMessage(EventMessage event, void *)
{
}

void FadeFlashTexture::OnUpdate(float deltaTime)
{
	timer += 90.0f * deltaTime;
	alpha = Math::Abs(Math::Sin(timer));
}

void FadeFlashTexture::OnDraw() const
{
	//‰e—p‚Ì‰æ‘œ‚ð•`‰æ
	gsDrawSprite2D(texID, &(GSvector2(position.x, position.y) + GSvector2(6,6)), NULL, NULL, &GScolor(0.1f, 0.1f, 0.1f, alpha), NULL, 0);
	gsDrawSprite2D(texID, &GSvector2(position.x, position.y), NULL, NULL, &GScolor(1.0f, 1.0f, 1.0f, alpha), NULL, 0);
}
