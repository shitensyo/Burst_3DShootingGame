#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include <vector>

//プレイヤーのミサイル
class PlayerMissile : public Actor {
public:
	PlayerMissile(IWorld* world_, const Vector3& position_,const Matrix4& playerRotate_,const Vector3& direction_);
	PlayerMissile(IWorld* world_, const Vector3& position_, const Matrix4& playerRotate_, const Vector3& direction_,float modelScale);

	virtual void OnUpdate(float deltaTime) override;

	virtual void OnDraw() const override;

	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	float timer;
	Matrix4 scale;
	//現在の移動方向
	Vector3 direction;
	//ターゲットへの方向
	Vector3 targetDirection;
	float speed;
	float smokeTimer;
	//正面にいる敵の座標をここに格納
	std::vector<Vector3> enemyPositions;
};