#pragma once

#include <gslib.h>
#include <string>

//�_�ł���e�N�X�`���@�e�X�g�v���O����
class FlashTexture
{
public:
	explicit FlashTexture(GSint texture = 0);
	void Update(float deltaTime);
	void draw(const GSvector2 pos) const;

private:
	GSint	texture;
	float timer;
	float alpha;
};
