#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include "../AssetID.h"

//任意方向にパーティクルを飛ばす（アルファブレンド）
class BasicParticle : public Actor
{
public:
	BasicParticle(IWorld* world_,const TEXTURE_ID& texID_ , const Vector3& position_,const Vector3& velocity_,float scale_ = 1.0f, float lifeTime_ = 1.0f);

private:
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	//描画するテクスチャ
	TEXTURE_ID texID;
	//進行方向×移動量
	Vector3 velocity;
	//寿命
	float lifeTime;
	//寿命計測タイマー
	float lifeTimer;
	//テクスチャスケール
	float scale;
	//回転
	float angle;
};
