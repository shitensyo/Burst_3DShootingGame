#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//��e���̉�
class HitSmoke : public Actor
{
public:
	HitSmoke(IWorld* world_, const Vector3& position_);

private:
	virtual void OnUpdate(float deltaTime) override;

private:
	//���̐�����
	int smokeNum;
};
