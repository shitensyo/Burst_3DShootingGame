#include "EnemyMissile.h"
#include <gslib.h>
#include "../AssetID.h"
#include "../../../EventMessage.h"
#include "../Base/ActorGroup.h"
#include "../Effect/MissileSmoke.h"

static const float SMOKE_INTERVAL = 0.01f;
static const float SMOKE_SPEED = 10.0f;
static const float LIFE_TIME = 3.0f;

EnemyMissile::EnemyMissile(IWorld * world_, const Vector3 & position_, const Vector3& velocity_) :
	Actor(world_, "EnemyMissile", position_, BoundingSphere(20.0f)),
	timer(0.0f),
	velocityNormal(velocity_.Normalized()),
	speed(velocity_.Length()),
	lifeTimer(0.0f)
{
	Vector3 front = velocityNormal.Normalized();
	Vector3 left = Vector3::Normalize(Vector3::Cross(Vector3::Up, front));
	rotate.SetFront(front);
	rotate.SetLeft(left);
	rotate.SetUp(Vector3::Normalize(Vector3::Cross(front, left)));
	scale = Matrix4::Scale(Vector3(1.0f));
}

EnemyMissile::EnemyMissile(IWorld * world_, const Vector3 & position_, const Vector3& velocity_, float modelScale) :
	Actor(world_, "EnemyMissile", position_, BoundingSphere(5.0f)),
	timer(0.0f),
	velocityNormal(velocity_.Normalized()),
	speed(velocity_.Length()),
	lifeTimer(0.0f)
{
	Vector3 front = velocityNormal.Normalized();
	Vector3 left = Vector3::Normalize(Vector3::Cross(Vector3::Up, front));
	rotate.SetFront(front);
	rotate.SetLeft(left);
	rotate.SetUp(Vector3::Normalize(Vector3::Cross(front, left)));
	scale = Matrix4::Scale(Vector3(modelScale));
}


void EnemyMissile::OnUpdate(float deltaTime)
{
	//移動
	position += velocityNormal * speed * deltaTime;
	speed *= 1.02f;
	lifeTimer += deltaTime;
	if (lifeTimer > LIFE_TIME)
		Dead();

	//進行方向とは逆方向に煙エフェクトを発射
	timer += deltaTime;
	if (timer > SMOKE_INTERVAL)
	{
		timer = 0.0f;
		world->AddActor(ActorGroup::Effect, std::make_shared<MissileSmoke>(world, position, -velocityNormal * SMOKE_SPEED));
	}

}

void EnemyMissile::OnDraw() const
{
	glPushMatrix();
	glMultMatrixf(scale.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::ENEMY_MISSILE_MODEL);
	glPopMatrix();

	//body.Translate(position).Draw();
}

void EnemyMissile::OnCollide(Actor& other,const HitInfo& info)
{
	Dead();
}
