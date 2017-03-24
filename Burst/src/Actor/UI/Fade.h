#pragma once

#include "../Base/Actor.h"
#include "../../Def.h"

//�t�F�[�h�C���A�A�E�g���s��(EventMessage��ʂ��čs���B�ŏ��̃t�F�[�h�C���͏���ɍs���B)
class Fade : public Actor
{
public:
	Fade(IWorld* world);
private:
	virtual void OnMessage(EventMessage event, void*) override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	//�����甒
	bool isFadeIn;
	bool isFadeOut;
	float alpha;
};
