#pragma once

#include "../Base/Actor.h"
#include <vector>

//ステージ（山）
class StageDestroyBase : public Actor {
public:
	//コンストラクタ
	StageDestroyBase(IWorld* world);
private:
	//更新
	virtual void OnUpdate(float deltaTime) override;
	//描画
	virtual void OnDraw() const override;

private:
	//スケール
	float scale;
};