#include "StageMountain.h"
#include "../../World/IWorld.h"
#include"../AssetID.h"

static const int MODEL_NUM = 10;

StageMountain::StageMountain(IWorld* world) :
	Actor(world, "StageMountain", Vector3(0.0f, 0.0f, 0.0f), BoundingSphere(1.0)),
	velocity(Vector3::Backward),
	speed(400.0f)
{
	positions.clear();
	scales.clear();
	for (int i = 0; i < MODEL_NUM; i++)
	{
		positions.push_back(Vector3(-gsRand(260, 300), -100, i*400));
		scales.push_back(Vector3(1.8f, 5.0f, 1.0f));
		positions.push_back(Vector3(gsRand(380, 420), -100, i*400));
		scales.push_back(Vector3(1.8f, 5.0f, 1.0f));
	}
}

void StageMountain::OnUpdate(float deltaTime)
{
	for (int i = 0; i < MODEL_NUM * 2; i++)
	{
		positions.at(i) += velocity * speed * deltaTime;
		if (positions.at(i).z < -300.0f)
			positions.at(i).z = 3000.0f;
	}
}

void StageMountain::OnDraw() const
{
	for (int i = 0; i < MODEL_NUM * 2; i++)
	{
		glPushMatrix();
		glMultMatrixf(
			Matrix4::Scale(scales.at(i)).ToGSmatrix4() * 
			Matrix4::Translate(positions.at(i)).ToGSmatrix4());
		gsDrawMesh(MODEL_ID::MOUNTAIN_MODEL);
		glPopMatrix();
	}

}