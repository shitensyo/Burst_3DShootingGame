#pragma once

#include "../Base/Actor.h"
#include "../../World/IWorld.h"

//�󒆐�̓}�V���K�����ˑ�
class AirShipMachinegunShooter : public Actor 
{
public:
	AirShipMachinegunShooter(IWorld* world_, const Vector3& position_, const Matrix4& initRotate_, bool isShot_ = true);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;
	virtual void OnCollide(Actor& other,const HitInfo& info) override;

private:
	//��]����
	void Rotation();
private:
	float timer;

	//������]�s��
	Matrix4 initRotate;
	//���˕���
	Vector3 targetVec;
	//��]��
	float angleY;
	//���˕����A��]�ʐ؂�ւ��^�C�}�[
	float rotateTimer;

	bool isShot;
};