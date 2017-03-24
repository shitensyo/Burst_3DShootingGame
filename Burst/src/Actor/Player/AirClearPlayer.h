#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//プレイヤー（空ステージクリア時）
class AirClearPlayer : public Actor {
public:
	AirClearPlayer(IWorld* world);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other, const HitInfo& info) override;

private:
	//ブースターの炎回転
	void BoosterRotate(float deltaTime);

private:
	float timer;

	//現在の向き
	float angleX;
	float angleY;
	int angleZ;

	//ブースターの炎の回転
	float boosterAngle;
	Vector3 velocity;
};