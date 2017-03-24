#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//�󒆐�̓~�T�C�����ˑ�
class AirShipMissileShooter : public Actor 
{
public:
	AirShipMissileShooter(IWorld* world_, const Vector3& position_, const Matrix4& initRotate_, bool isShot_ = true);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	float timer;

	//������]�s��
	Matrix4 initRotate;
	//�U���ڕW
	ActorPtr player;
	//��]��
	float angleY;
	//1�t���[���O�̉�]��
	Matrix4 prevRotate;
	//���݂̉�]��
	Matrix4 currentRotate;
	
	bool isShot;
};