#pragma once
#include"Animation.h"
#include"LayeredAnimation.h"

class AnimatiedMesh
{
public:
	using Matrices = std::array<GSmatrix4, 256>;
public:
	AnimatiedMesh(GSuint mesh, GSuint skeleton, GSuint animation, GSuint motion = 0):
		mesh_(mesh),
		skelton_(skeleton),
		animation_(animation,0)
	{

	}

	void Update(float deltaTime)
	{
		animation_.Update(deltaTime);
	}

	void Draw() const
	{
		gsDisable(GS_CALC_SKELETON);
		gsEnable(GS_SKIN_MESH);
		gsBindSkeleton(skelton_);
		gsSetMatrixSkeleton(matrices_.data());
		gsDrawMesh(mesh_);
	}

	void changeMotion(GSuint motion, GSuint layer =0)
	{
		animation_.changeMotion(motion);
	}

	void calculate(const GSmatrix4& world)
	{
		gsBindSkeleton(skelton_);
		gsCalculateSkeleton(&world, animation_.getMatrices().data(), matrices_.data());
	}

	const AnimatiedMesh::Matrices& getMatrices() const
	{
		return matrices_;
	}

	void setAnimationLayerIndex(GSuint boneID, GSuint layer)
	{
		//animation_.setLayerIndex(boneID, layer);
	}

	GSuint getMotionEndTimer(GSuint layer = 0) const
	{
		return animation_.getEndTimer();
	}


private:
	GSuint mesh_;
	GSuint skelton_;
	Animation animation_;
	Matrices matrices_;
};
