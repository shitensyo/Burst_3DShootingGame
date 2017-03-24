#pragma once

#include "../Base/Actor.h"

//�e���o���A�ɂ͂����ꂽ�Ƃ��̃G�t�F�N�g
class Reflect : public Actor 
{
public:
	Reflect(IWorld* world_, const Vector3& position_,float finalScale_);
private:
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	//���Ń^�C�}�[
	float timer;
	float scale;
	//�ŏI�I�ȃX�P�[��
	float finalScale;
};