#pragma once

#include "../Base/Actor.h"
#include "../../Def.h"
#include <vector>

//�v���C���[�ւ̎w�����s���ʐMUI
class Communication : public Actor
{
public:
	//�e�L�X�g�i�s�i�K
	enum class Phase
	{
		START = 0,
		TUTORIAL,
		BARRIER,
		CONTAINER,
		SHIP,

		DEAD,
		CLEAR,
	};

public:
	Communication(IWorld* world, ActorPtr boss_, const Vector2& position_ = Vector2::Zero, const Phase& phase_=Phase::START);
private:
	virtual void OnMessage(EventMessage event, void*) override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

	void StartPhase(float deltaTime);
	void TutorialPhase(float deltaTime);
	void BarrierPhase(float deltaTime);
	void ContainerPhase(float deltaTime);
	void ShipPhase(float deltaTime);
	void DeadPhase(float deltaTime);
	void ClearPhase(float deltaTime);


private:
	float timer;
	float textWaitTimer;
	//�e�L�X�g�i�s�ԍ�
	int textNum;
	//�e�L�X�g�i�s�i�K
	Phase phase;
	//�e�L�X�g��`�悷�邩�H
	bool isTextDraw;

	std::vector<std::string> texts;
	//������ʒu
	Vector2 initPosition;
	//�e�L�X�g�ʒu
	Vector2 textPosition;
};
