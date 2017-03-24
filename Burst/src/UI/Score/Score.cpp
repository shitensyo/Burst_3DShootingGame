#include "Score.h"
#include"../Base/NumberTexture.h"
#include <algorithm>
#include "../../Actor/AssetID.h"
#include "../../Math/Math.h"

//何点取ると階級が上がるか
static const int CLASS_UP_SCORE = 30;
//階級プレート初期座標
static const GSvector2 INIT_PLATE_BASE_POS = GSvector2(590.0f, 495.0f);

Score::Score(int score) : 
	score(score),
	plateBasePos(INIT_PLATE_BASE_POS)
{
}

void Score::AddScore(int add)
{
	score = std::min(score + add, 999);
}

void Score::Draw() const {
	////スコアの数字のデバッグ描画
	//gsTextPos(0, 200);
	//gsDrawText("score : %d", score);

	//プレートの描画
	TEXTURE_ID plate = TEXTURE_ID::PLATE_BRONZ_TEX;
	if(score > CLASS_UP_SCORE * 3 + CLASS_UP_SCORE - 1) plate = TEXTURE_ID::PLATE_SILVER_TEX;
	if (score > CLASS_UP_SCORE * 6 + CLASS_UP_SCORE - 1) plate = TEXTURE_ID::PLATE_GOLD_TEX;

	gsDrawSprite2D(plate, &plateBasePos, &GSrect(0, 0, 640, 320), NULL, NULL, &GSvector2(0.32f, 0.32f), 0);

	//星の描画
	//ちっちゃいほう
	int digit = score % 10;
	for (int i = 0; i < digit;i++)
	{
		GSvector2 pos(160 - i * 10,65);
		gsDrawSprite2D(TEXTURE_ID::STAR_TEX, &(plateBasePos + pos), &GSrect(0, 0, 256, 256), NULL, NULL, &GSvector2(0.12f, 0.12f), 0);
	}
	//でっかいほう
	int tennum = (score - digit) / 10;
	tennum %= CLASS_UP_SCORE / 10;
	for (int i = 0; i < tennum; i++)
	{
		GSvector2 pos(30 - i * 10, 45);
		gsDrawSprite2D(TEXTURE_ID::STAR_TEX, &(plateBasePos + pos), &GSrect(0, 0, 256, 256), NULL, NULL, &GSvector2(0.2f, 0.2f), 0);
	}

	//文字の描画
	int scoreClass = score / CLASS_UP_SCORE;
	scoreClass = Math::Clamp(scoreClass, 0, 9);
	gsDrawSprite2D(TEXTURE_ID::CLASS_TEXT_TEX, &(plateBasePos + GSvector2(70, 5)), &GSrect(0, 64 * scoreClass - 64, 128, 64 * scoreClass), NULL, NULL, &GSvector2(1.0f, 1.0f), 0);
}

int Score::GetScore() const {
	return score;
}

void Score::SetPlateBasePos(const Vector2& pos)
{
	plateBasePos = pos.ToGSvector2();
}

GSvector2 Score::GetInitPlateBasePos()
{
	return INIT_PLATE_BASE_POS;
}
