#include "AirClearPlayer.h"
#include <gslib.h>
#include "../AssetID.h"
#include "../../../EventMessage.h"
#include "../Base/ActorGroup.h"
#include "../PlayerBullet/PlayerMachineGun.h"
#include "../PlayerBullet/PlayerMissile.h"
#include "../Effect/Explosion.h"
#include "../Effect/HitSmoke.h"
#include <GSmusic.h>
#include "../UI/DashLine.h"
#include "../../../EventMessage.h"

//移動速度
static const float MOVE_SPEED_Z = 350.0f;

static const Matrix4 PLAYER_MODEL_SCALE = Matrix4::Scale(Vector3(0.2f));


AirClearPlayer::AirClearPlayer(IWorld* world) :
	Actor(world, "Player", Vector3(0,-200,0), BoundingSphere(),1),
	timer(0.0f),
	angleX(0.0f),
	angleY(0.0f),
	angleZ(0.0f),
	boosterAngle(0.0f)
{
	Vector3 target = Vector3(910, 700, -2400);
	Vector3 v = target - position;
	v.Normalize();
	velocity = v * MOVE_SPEED_Z;

	rotate.SetFront(v);
	Vector3 l = Vector3::Cross(Vector3::Up, v);
	rotate.SetLeft(l);
	rotate.SetUp(Vector3::Cross(v, l));
}

void AirClearPlayer::OnUpdate(float deltaTime)
{
	BoosterRotate(deltaTime);

	timer += deltaTime;
	if (timer < 4.0f) return;

	position += velocity * deltaTime;
}

void AirClearPlayer::OnDraw() const
{
	//モデルの描画
	glPushMatrix();
	glMultMatrixf(PLAYER_MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::PLAYER_MODEL);
	glPopMatrix();

	//ブースターの炎の描画
	glPushMatrix();
	Matrix4 mat =
		PLAYER_MODEL_SCALE *
		Matrix4::RotateZ(boosterAngle) *Matrix4::Translate(Vector3(0.0f, 0.6f, -28.0f)) *
		GetPose();
	glMultMatrixf(mat.ToGSmatrix4());
	gsDrawMesh(MODEL_ID::PLAYER_BOOSTER_MODEL);
	glPopMatrix();
}

void AirClearPlayer::OnCollide(Actor& other,const HitInfo& info)
{

}

void AirClearPlayer::BoosterRotate(float deltaTime)
{
	boosterAngle += 2000.0f * deltaTime;
}