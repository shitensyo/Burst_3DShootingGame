#pragma once

#include "../Base/Actor.h"
#include <vector>

//ステージ（山）
class StageMountain : public Actor {
public:
	//コンストラクタ
	StageMountain(IWorld* world);
private:
	//更新
	virtual void OnUpdate(float deltaTime) override;
	//描画
	virtual void OnDraw() const override;

private:
	//座標
	std::vector<Vector3> positions;
	//スケール
	std::vector<Vector3> scales;
	//移動量
	Vector3 velocity;
	//移動速度
	float speed;
};