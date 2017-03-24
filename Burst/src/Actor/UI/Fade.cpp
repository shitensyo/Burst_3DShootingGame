#include "Fade.h"
#include "../AssetID.h"
#include "../../../EventMessage.h"

static const float IN_SPEED = 2.0f;
static const float OUT_SPEED = 1.0f;

Fade::Fade(IWorld * world) :
	Actor(world, "Fade", Vector3::Zero, BoundingSphere()),
	isFadeIn(true),
	isFadeOut(false),
	alpha(1.0f)
{

}

void Fade::OnMessage(EventMessage event, void *)
{
	if (event == EventMessage::FadeIn)
		isFadeIn = true;
	else if (event == EventMessage::FadeOut)
		isFadeOut = true;
}

void Fade::OnUpdate(float deltaTime)
{
	if (isFadeIn)
	{
		alpha -= IN_SPEED * deltaTime;
		if (alpha <= 0.0f)
		{
			alpha = 0.0f;
			isFadeIn = false;
		}
	}	
	else if (isFadeOut)
	{
		alpha += OUT_SPEED * deltaTime;
		if (alpha >= 1.0f)
		{
			alpha = 1.0f;
			isFadeOut = false;
		}
	}
}

void Fade::OnDraw() const
{
	GScolor c(1.0f,1.0f,1.0f,alpha);
	gsDrawSprite2D(TEXTURE_ID::BLACK_TEX, NULL, NULL, NULL, &c, NULL, 0);

}
