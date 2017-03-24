#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include <vector>

//敵ボス空中戦艦
class EnemyAirShip : public Actor
{
public:
	EnemyAirShip(IWorld* world_, const Vector3& position_);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	float timer;

	//攻撃目標
	ActorPtr player;
	Vector3* target;
	//移動方向
	Vector3 velocity;
	//移動速度
	float speed;
	//現在の向き
	float angleX;
	float angleY;
	float angleZ;

	float addAngleZ;
	float fighterCreateTime;
	float fighterCreateTimer;
	float smokeTimer;
	//煙放出地点
	std::vector<Vector3> smokePositions;
};