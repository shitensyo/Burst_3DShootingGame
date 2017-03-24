#include "BarrierSphere.h"
#include "../AssetID.h"
#include "../../World/IWorld.h"

static const float MODEL_SCALE_MIN = 10.0f;
static const float MODEL_SCALE_MAX = 10.1f;

BarrierSphere::BarrierSphere(IWorld * world, const Vector3 & position) :
	Actor(world, "BarrierSphere", position, BoundingSphere(1030.0f))
{
}

void BarrierSphere::OnUpdate(float deltaTime)
{
	//バリア発生装置が全滅したら自身も死亡
	if (world->FindActor("BarrierGenerator") == nullptr)
	{
		Dead();
	}
}

void BarrierSphere::OnDraw() const
{
	glPushMatrix();
	glMultMatrixf(Matrix4::Scale(Vector3(gsRandf(MODEL_SCALE_MIN, MODEL_SCALE_MAX))).ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::BARRIER_SPHERE);
	glPopMatrix();
}

void BarrierSphere::OnCollide(Actor & other, const HitInfo & info)
{

}
