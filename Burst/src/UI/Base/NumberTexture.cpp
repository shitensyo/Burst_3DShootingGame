#include "NumberTexture.h"
#include <sstream>
#include <iomanip>


NumberTexture::NumberTexture(GSint texture, int width_, int height_) :
	texture(texture),
	width(width_),
	height(height_)
{
}

void NumberTexture::Draw(const Vector2 & position, int num, int digit, char fill) const {
	std::stringstream ss;
	ss << std::setw(digit) << std::setfill(fill) << num;
	Draw(position, ss.str());
}

void NumberTexture::Draw(const Vector2 & position, int num) const {
	Draw(position, std::to_string(num));
}

void NumberTexture::Draw(const Vector2 & position, const std::string & num) const {
	for (int i = 0; i < (int)num.size(); ++i)
	{
		if (num[i] == ' ') continue;
		const int n = num[i] - '0';
		const GSrect rect(n * width, 0.0f, (n * width) + width, height);
		const GSvector2 pos(position.x + i * width, position.y);
		gsDrawSprite2D(texture, &pos, &rect, NULL, NULL, NULL, 0);
	}
}
