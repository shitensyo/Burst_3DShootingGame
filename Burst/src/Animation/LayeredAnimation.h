#pragma once
#include<vector>
#include<memory>
#include"Animation.h"

class  LayeredAnimation
{
public:
	using Matrices = std::array<GSmatrix4, 256>;
public:
	LayeredAnimation(GSuint animation, GSuint motion, GSuint layer)
	{
		for (GSuint i = 0; i < layer; ++i)
		{
			layer_.push_back(std::make_shared<Animation>(animation, motion));
		}
		indices_.fill(0);
		matrices_.fill(GSmatrix4().identity());
	}

	void Update(float deltaTime)
	{
		for (const auto& animation : layer_)
		{
			animation->Update(deltaTime);
		}
		conbineLayer();
	}

	void changeMotion(GSuint motion, GSuint layer = 0)
	{
		layer_[layer]->changeMotion(motion);
	}

	GSuint getMotion(GSuint layer = 0) const
	{
		return layer_[layer]->getMotion();
	}

	GSuint getEndTime(GSuint layer = 0) const
	{
		return layer_[layer]->getEndTimer();
	}

	const LayeredAnimation::Matrices& getMatrices() const
	{
		return matrices_;
	}

	void setLayerIndex(GSuint boneID, GSuint layer)
	{
		indices_[boneID] = layer;
	}

private:
	void conbineLayer()
	{
		for (GSuint i = 0; i < layer_[0]->getBoneCout(); ++i)
		{
			matrices_[i] = layer_[indices_[i]]->getMatrices().at(i);
		}
	}

private:
	using AnimationLayers = std::vector<std::shared_ptr<Animation>>;
	using Indices = std::array<int, 256>;
	AnimationLayers layer_;
	Indices indices_;
	Matrices matrices_;
};
