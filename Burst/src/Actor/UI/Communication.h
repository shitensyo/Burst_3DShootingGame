#pragma once

#include "../Base/Actor.h"
#include "../../Def.h"
#include <vector>

//プレイヤーへの指示を行う通信UI
class Communication : public Actor
{
public:
	//テキスト進行段階
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
	//テキスト進行番号
	int textNum;
	//テキスト進行段階
	Phase phase;
	//テキストを描画するか？
	bool isTextDraw;

	std::vector<std::string> texts;
	//基準初期位置
	Vector2 initPosition;
	//テキスト位置
	Vector2 textPosition;
};
