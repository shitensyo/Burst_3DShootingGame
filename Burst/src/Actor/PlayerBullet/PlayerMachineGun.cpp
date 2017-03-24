#include "PlayerMachineGun.h"
#include <gslib.h>
#include"../AssetID.h"
#include"../../../EventMessage.h"
#include<math.h>
#include "../Effect/MissileSmoke.h"
#include "../Base/ActorGroup.h"
#include "../Effect/Reflect.h"
#include "../Effect/Fire.h"

static const float MOVE_SPEED = 2000.0f;
static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(0.05f));
static const float ROTATE_SPEED = 900.0f;

PlayerMachineGun::PlayerMachineGun(IWorld* world_, const Vector3& position_, const Vector3& direction_) :
	Actor(world_, "PlayerMachineGun", position_, BoundingSphere(16.0f)),
	timer(0.0f),
	direction(direction_)
{
	rotate = Matrix4::RotateZ(gsRandf(0.0f, 180.0f));
}

PlayerMachineGun::PlayerMachineGun(IWorld * world_, const Vector3 & position_, const Matrix4 & playerRotate_, const Vector3 & direction_):
	Actor(world_, "PlayerMachineGun", position_, BoundingSphere(12.0f)),
	timer(0.0f),
	direction(direction_)
{
	rotate.SetFront(direction_);
	rotate.SetUp(playerRotate_.GetUp());
	Vector3 left = Vector3::Cross(rotate.GetUp(), rotate.GetFront());
	left.Normalize();
	rotate.SetLeft(left);
}

void PlayerMachineGun::OnUpdate(float deltaTime)
{
	timer += deltaTime;
	if (timer > 1.0f)
		Dead();
	position += direction * MOVE_SPEED * deltaTime;
}

void PlayerMachineGun::OnDraw() const
{
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::MACHINEGUN_MODEL);
	glPopMatrix();

	//body.Translate(position).Draw();
}

void PlayerMachineGun::OnCollide(Actor& other,const HitInfo& info)
{
	//ƒoƒŠƒA‚É“–‚½‚Á‚½‚Æ‚«
	if (other.GetName() == "BarrierSphere")
	{
		gsPlaySE(SOUND_ID::REFRECT_SE);
		world->AddActor(ActorGroup::Effect, std::make_shared<Reflect>(world, position, 15.0f));
		Dead();
	}
	//‚»‚êˆÈŠO‚Í¬”š”­
	else
	{
		gsPlaySE(SOUND_ID::HIT_SE);
		world->AddActor(ActorGroup::Effect, std::make_shared<Fire>(world, position, Vector3::Zero));
		Dead();
	}

}