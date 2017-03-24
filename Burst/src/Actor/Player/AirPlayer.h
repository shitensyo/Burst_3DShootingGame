#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//プレイヤー（空ステージで使用）
class AirPlayer : public Actor {
public:
	AirPlayer(IWorld* world, const Vector3& position);

	virtual void OnUpdate(float deltaTime) override;

	virtual void OnDraw() const override;

	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	//弾の発射
	void ShotBullet(float deltaTime);
	//移動
	void Move(float deltaTime);

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
	//ブースターの炎の拡大率
	Matrix4 boosterScale;
	//ブースターの炎の位置
	Vector3 boosterPos;
	
	//押し返し用　最終的な移動量を保持
	Vector3 finalVelocity;

	//ダッシュ中か？
	bool isDash;
	//ダッシュ経過時間
	float dashTimer;
	//ダッシュ時の白い線生成タイマー
	float dashLineTimer;

	float missileTimer;
};