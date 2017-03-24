#include "TitlePlayer.h"
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

static const Matrix4 PLAYER_MODEL_SCALE = Matrix4::Scale(Vector3(0.1f));


TitlePlayer::TitlePlayer(IWorld* world, const Vector3& position) :
	Actor(world, "TitlePlayer", position, BoundingSphere(), 1),
	timer(0.9f),
	boosterAngle(0.0f),
	angleY(0.0f),
	addAngleY(10.0f),
	add(0.0f),
	sign(1.0f)
{
	rotate.SetFront(Vector3::Backward);
	rotate.SetUp(Vector3::Up);
	rotate.SetLeft(Vector3::Left);
	initRotate = rotate;
}

void TitlePlayer::OnUpdate(float deltaTime)
{
	boosterAngle += 2000.0f * deltaTime;
	timer += deltaTime;
	if (timer > 3.0f)
	{
		timer = 0.0f;
		sign *= -1;
	}
	//add += 10.0f * sign * deltaTime;
	//addAngleY += add * deltaTime;

	angleY += addAngleY * ( 3.0f - timer) * sign * deltaTime;

	Quaternion q = Quaternion::RotateAxis(Vector3::Up, angleY);
	rotate = Quaternion::Rotate(Quaternion(initRotate) * q);
}

void TitlePlayer::OnDraw() const
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
		Matrix4::RotateZ(boosterAngle) *Matrix4::Translate(Vector3(0.0f, 0.3f, -14.0f)) *
		GetPose();
	glMultMatrixf(mat.ToGSmatrix4());
	gsDrawMesh(MODEL_ID::PLAYER_BOOSTER_MODEL);
	glPopMatrix();
}

void TitlePlayer::OnCollide(Actor& other, const HitInfo& info)
{

}
