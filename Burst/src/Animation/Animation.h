#pragma once
#include<GSgame.h>
#include<array>

class Animation
{
public:
	using Matrices = std::array<GSmatrix4, 256>;
public:
	Animation(GSuint animation, GSuint motion) :
		animation_(animation),
		motion_(motion),
		motionTimer_(0.0f)
	{
		Update(0.0f);
	}

	void Update(float deltaTime)
	{
		motionTimer_ += deltaTime;
		lerpTimer_ = std::min(lerpTimer_ + deltaTime, LERP_TIME);
		gsCalculateAnimationLerp
			(animation_,prevMotion_,prevMotionTimer_,animation_
				, motion_, motionTimer_,lerpTimer_ / LERP_TIME,
				matrices_.data());
	}

	void changeMotion(GSuint motion)
	{
		if (motion == motion_) return;
		prevMotion_ = motion_;
		prevMotionTimer_ = motionTimer_;
		motion_ = motion;
		motionTimer_ = 0.0f;
		lerpTimer_ = 0.0f;
	}

	GSuint getMotion() const
	{
		return motion_;
	}

	GSuint getBoneCout() const
	{
		return gsGetAnimationNumBones(animation_, motion_);
	}

	GSuint getEndTimer() const
	{
		return gsGetEndAnimationTime(animation_, motion_);
	}

	const Animation::Matrices& getMatrices() const
	{
		return matrices_;
	}

private:
	const GSfloat LERP_TIME = 10.0f;
	GSuint animation_;
	GSuint motion_;
	GSfloat motionTimer_;
	GSfloat prevMotion_;
	GSfloat prevMotionTimer_;
	GSfloat lerpTimer_;
	Matrices matrices_;
};