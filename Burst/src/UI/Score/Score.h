#pragma once

#include <gslib.h>
#include "../../Math/Vector2.h"

//スコアクラス
class Score {
public:
	//コンストラクタ
	explicit Score(int score = 0);
	//スコアの加算
	void AddScore(int add);
	//スコアの描画
	void Draw() const;
	//スコアの取得
	int GetScore() const;
	//階級プレートの移動
	void SetPlateBasePos(const Vector2& pos);
	//階級プレートの基準初期座標取得
	GSvector2 GetInitPlateBasePos();

private:
	//スコア
	int score;
	//階級プレートの基準座標
	GSvector2 plateBasePos;
};