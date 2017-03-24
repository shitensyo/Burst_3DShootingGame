#pragma once

#include <gslib.h>
#include "../Base/Actor.h"
#include "../../World/IWorld.h"
#include "../../Field/Field.h"
#include "../../Math/Ray.h"
#include "../Effect/Explosion.h"
#include "../Effect/Fire.h"
#include "../../../EventMessage.h"
#include"../Player/Player.h"

//アニメーション付き敵のひながたにしようとした（用済み）
class Enemy : public Actor {

public:
	enum MotionID
	{
		IDLE_MOTION = 0,
		DAMAGE_MOTION = 14,
	};

	enum State
	{
		IDLE,
		MOVE,
		DAMAGE,
	};

public:
	Enemy(IWorld* world, const Vector3&  position, const Vector3& velocity) :
		Actor(world, "Enemy", position, BoundingSphere(0.5)),
		timer(0.0f),
		flashTimer(0.0f),
		velocity(velocity),
		state(State::IDLE),
		motion(MotionID::IDLE_MOTION)
	{
		float dot = Vector3::Dot(velocity.Normalized(), rotate.GetFront());
		float angle = RAD_TO_DEG(atan2f(velocity_.x, velocity_.z));
		rotate.SetRotateY(angle);
	}
	virtual void OnUpdate(float deltaTime) override 
	{
		timer += deltaTime;

	}
	virtual void OnDraw() const override {

	}
	virtual void OnCollide(Actor& target) override
	{
		
	}
	virtual void OnMessage(EventMessage event, void*) override 
	{

	}

private:
	float timer;
	State state;
	MotionID motion;
	Vector3 velocity;
	float flashTimer;
	bool isDraw;

private:
	const float MOVE_SPEED = 0.1f;
	const float STATE_STOP_TIME = 60;
};