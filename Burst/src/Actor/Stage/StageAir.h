#pragma once

#include "../Base/Actor.h"
#include <vector>

//ステージ（空）
class StageAir : public Actor {
public:
	//コンストラクタ
	StageAir(IWorld* world);
private:
	//更新
	virtual void OnUpdate(float deltaTime) override;
	//描画
	virtual void OnDraw() const override;

private:
	//スケール
	float scale;
};