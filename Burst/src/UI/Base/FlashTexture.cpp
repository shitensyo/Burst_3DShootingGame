#include "FlashTexture.h"
#include "../../Math/Math.h"

static const GScolor COLOR = GScolor(1.0f, 1.0f, 1.0f, 1.0f);
static const GScolor BLACK_COLOR = GScolor(0.1f,0.1f,0.1f, 1.0f);
static const GSvector2 BLACK_POS = GSvector2(6,6);

FlashTexture::FlashTexture(GSint texture):
	texture(texture),
	timer(0.0f),
	alpha(1.0f)
{

}

void FlashTexture::Update(float deltaTime)
{
	timer += 90.0f * deltaTime;
	alpha = Math::Abs(Math::Sin(timer));
}

void FlashTexture::draw(const GSvector2 pos) const
{
	GScolor c = BLACK_COLOR;
	c.a = alpha;
	gsDrawSprite2D(texture, &(pos + BLACK_POS), NULL, NULL, &c, NULL, 0);
	c = COLOR;
	c.a = alpha;
	gsDrawSprite2D(texture, &pos, NULL, NULL, &c, NULL, 0);
}
