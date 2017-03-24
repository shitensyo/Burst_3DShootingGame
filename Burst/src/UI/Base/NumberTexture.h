#pragma once

#include <gslib.h>
#include <string>
#include "../../Math/Vector2.h"

//�����e�N�X�`���Ő��l��`�悷��@�e�X�g�v���O����
class NumberTexture
{
public:
	//�R���X�g���N�^(�e�N�X�`��ID�A�P�R�}�̉����A�c��)
	NumberTexture(GSint texture, int width_, int height_);
	//�`��
	void Draw(const Vector2& position, int num, int digit, char fill = '0') const;
	//�`��
	void Draw(const Vector2& position, int num) const;
	//�`��
	void Draw(const Vector2& position, const std::string& num) const;

private:
	//�e�N�X�`��
	GSint	texture;
	//��
	int		width;
	//����
	int		height;
};

