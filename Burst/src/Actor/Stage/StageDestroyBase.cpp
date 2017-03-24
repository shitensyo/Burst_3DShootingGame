#include "StageDestroyBase.h"
#include "../../World/IWorld.h"
#include"../AssetID.h"

static const int MODEL_NUM = 10;

StageDestroyBase::StageDestroyBase(IWorld* world) :
	Actor(world, "StageDestroyBase", Vector3(0.0f, 0.0f, 0.0f), BoundingSphere(1.0)),
	scale(3.0f)
{

}

void StageDestroyBase::OnUpdate(float deltaTime)
{

}

void StageDestroyBase::OnDraw() const 
{
	glPushMatrix();
	glMultMatrixf(Matrix4::Scale(scale).ToGSmatrix4());
	gsDrawMesh(MODEL_ID::MOUNTAIN_MODEL);
	glPopMatrix();
}