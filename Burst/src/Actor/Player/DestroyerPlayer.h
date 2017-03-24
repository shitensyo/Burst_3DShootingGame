#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//プレイヤー（基地破壊ステージで使用）
class DestroyerPlayer : public Actor {
public:
	DestroyerPlayer(IWorld* world, const Vector3& position);

	virtual void OnUpdate(float deltaTime) override;

	virtual void OnDraw() const override;

	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	//弾の発射
	void ShotBullet(float deltaTime);
	//移動
	void Move(float deltaTime);
	//ブースターの炎回転
	void BoosterRotate(float deltaTime);

private:
	float timer;

	//マシンガン発射間隔計測用
	float bulletTimer;
	//マシンガン発射位置の左右切り替え用
	int bulletChange;

	//現在の向き
	float angleX;
	float angleY;
	int angleZ;

	//回転速度加算用
	float addAngleZ;

	//ブースターの炎の回転
	float boosterAngle;
};