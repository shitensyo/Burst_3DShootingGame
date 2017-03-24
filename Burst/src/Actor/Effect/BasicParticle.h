#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include "../AssetID.h"

//�C�ӕ����Ƀp�[�e�B�N�����΂��i�A���t�@�u�����h�j
class BasicParticle : public Actor
{
public:
	BasicParticle(IWorld* world_,const TEXTURE_ID& texID_ , const Vector3& position_,const Vector3& velocity_,float scale_ = 1.0f, float lifeTime_ = 1.0f);

private:
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	//�`�悷��e�N�X�`��
	TEXTURE_ID texID;
	//�i�s�����~�ړ���
	Vector3 velocity;
	//����
	float lifeTime;
	//�����v���^�C�}�[
	float lifeTimer;
	//�e�N�X�`���X�P�[��
	float scale;
	//��]
	float angle;
};
