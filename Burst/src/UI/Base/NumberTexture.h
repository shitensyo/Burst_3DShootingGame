#pragma once

#include <gslib.h>
#include <string>
#include "../../Math/Vector2.h"

//数字テクスチャで数値を描画する　テストプログラム
class NumberTexture
{
public:
	//コンストラクタ(テクスチャID、１コマの横幅、縦幅)
	NumberTexture(GSint texture, int width_, int height_);
	//描画
	void Draw(const Vector2& position, int num, int digit, char fill = '0') const;
	//描画
	void Draw(const Vector2& position, int num) const;
	//描画
	void Draw(const Vector2& position, const std::string& num) const;

private:
	//テクスチャ
	GSint	texture;
	//幅
	int		width;
	//高さ
	int		height;
};

