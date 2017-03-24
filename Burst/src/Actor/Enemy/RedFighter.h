#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//空中戦艦から出てくる赤い戦闘機
class RedFighter : public Actor {
public:
	RedFighter(IWorld* world_, const Vector3& position_ , const Matrix4& rotate_ = Matrix4::Identity);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other, const HitInfo& info) override;

	//回転計算
	void PlayerLookingRotation(float deltaTime);
	//攻撃
	void Attack(float deltaTime);

private:
	ActorPtr player;
	float timer;
	Matrix4 initRotate;

	//移動方向
	Vector3 velocity;
	//移動速度
	float speed;
	int bulletChange;

	Vector3 front;
	//プレイヤーの方向
	Vector3 toPlayer;
	float dot;

	Matrix4 prevRotate;
	float boosterAngle;

	//離脱中か？
	bool isBreakaway;
	float breakawayTimer;
};