#include "EnemyMachineGun.h"
#include <gslib.h>
#include "../AssetID.h"
#include "../../../EventMessage.h"
#include "../Effect/Explosion.h"
#include "../Base/ActorGroup.h"

static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(0.07f));
//寿命デフォルト値
static const float LIFE_TIME = 1.0f;


EnemyMachineGun::EnemyMachineGun(IWorld * world_, const Vector3 & position_, const Vector3& velocity_) :
	Actor(world_, "EnemyMachineGun", position_, BoundingSphere(8.0f)),
	velocity(velocity_),
	lifeTime(LIFE_TIME),
	lifeTimer(0.0f)
{
	//進行方向を向く
	Vector3 dir = velocity.Normalized();
	Quaternion q = Quaternion::RotateAxis(Vector3::Cross(Vector3(0, 0, 1), dir).Normalized(), Vector3::Inner(Vector3(0, 0, 1), dir));
	rotate = Quaternion::Rotate(q);
}

EnemyMachineGun::EnemyMachineGun(IWorld* world_, const Vector3& position_, const Vector3& velocity_, float lifeTime_) :
	Actor(world_, "EnemyMachineGun", position_, BoundingSphere(4.0f)),
	velocity(velocity_),
	lifeTime(lifeTime_),
	lifeTimer(0.0f)
{
	//進行方向を向く
	Vector3 dir = velocity.Normalized();
	Quaternion q = Quaternion::RotateAxis(Vector3::Cross(Vector3(0, 0, 1), dir).Normalized(), Vector3::Inner(Vector3(0, 0, 1), dir));
	rotate = Quaternion::Rotate(q);
}

void EnemyMachineGun::OnUpdate(float deltaTime)
{
	//死亡判定
	lifeTimer += deltaTime;
	if (lifeTimer > lifeTime)
		Dead();

	//移動
	position += velocity * deltaTime;
}

void EnemyMachineGun::OnDraw() const
{
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::ENEMY_MACHINEGUN_MODEL);
	glPopMatrix();

	//body.Translate(position).Draw();
}

void EnemyMachineGun::OnCollide(Actor& other,const HitInfo& info)
{
	Dead();
}
