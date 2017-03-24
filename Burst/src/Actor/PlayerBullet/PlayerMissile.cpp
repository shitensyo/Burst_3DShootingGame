#include "PlayerMissile.h"
#include <gslib.h>
#include"../AssetID.h"
#include"../../../EventMessage.h"
#include<math.h>
#include "../Effect/MissileSmoke.h"
#include "../Base/ActorGroup.h"
#include "../Effect/Explosion.h"
#include "../Effect/Reflect.h"

static const float MOVE_SPEED_INC = 400.0f;
static const float ROTATE_SPEED = 900.0f;
static const float SMOKE_INTERVAL = 0.5f;
static const float SMOKE_SPEED = 20.0f;
static const float SMOKE_END_TIME = 0.1f;

//ホーミング開始時間
static const float HOMING_START_TIME = 0.5f;
//索敵範囲　自身の前方向と敵方向の内積がこれを超えた場合は、ホーミングする
static const float DOT_LIMIT = 0.8f;
//ホーミング補完値
static const float HOMING_LERP_VALUE = 0.2f;


PlayerMissile::PlayerMissile(IWorld* world_, const Vector3& position_, const Matrix4& playerRotate_, const Vector3& direction_) :
	Actor(world_, "PlayerMissile", position_, BoundingSphere(12.0f)),
	timer(0.0f),
	direction(direction_),
	speed(200.0f),
	smokeTimer(0.0f),
	scale(Matrix4::Scale(Vector3(3.0f)))
{
	rotate.SetFront(direction_);
	rotate.SetUp(playerRotate_.GetUp());
	Vector3 left = Vector3::Cross(rotate.GetUp(), rotate.GetFront());
	left.Normalize();
	rotate.SetLeft(left);
}

PlayerMissile::PlayerMissile(IWorld* world_, const Vector3& position_, const Matrix4& playerRotate_, const Vector3& direction_, float modelScale):
	Actor(world_, "PlayerMissile", position_, BoundingSphere(12.0f)),
	timer(0.0f),
	direction(direction_),
	speed(200.0f),
	smokeTimer(0.0f),
	scale(Matrix4::Scale(Vector3(modelScale)))
{
	rotate.SetFront(direction_);
	rotate.SetUp(playerRotate_.GetUp());
	Vector3 left = Vector3::Cross(rotate.GetUp(), rotate.GetFront());
	left.Normalize();
	rotate.SetLeft(left);
}

void PlayerMissile::OnUpdate(float deltaTime)
{
	timer += deltaTime;
	if (timer > 3.0f)
		Dead();

	//移動
	position += direction * speed * deltaTime;
	speed += MOVE_SPEED_INC * deltaTime;

	//進行方向とは逆方向に煙エフェクトを発射
	smokeTimer += deltaTime;
	if (timer > SMOKE_INTERVAL)
	{
		smokeTimer = 0.0f;
		world->AddActor(ActorGroup::Effect, std::make_shared<MissileSmoke>(world, position, -direction, SMOKE_END_TIME));
	}

	//指定秒数を超えたらホーミング開始
	if (timer < HOMING_START_TIME) return;

	//索敵範囲内の敵の座標取得
	enemyPositions.clear();
	ActorPtr enemys = world->GetGroup(ActorGroup::Enemy);
	enemys->EachChildren([&](Actor& child)
	{
		Vector3 pos = child.GetPosition();

		//前後判定
		Vector3 toEnemy = pos - position;
		toEnemy.Normalize();
		float dot = Vector3::Dot(GetRotate().GetFront(), toEnemy);
		//敵が索敵範囲にいるなら
		if (dot > DOT_LIMIT)
		{
			//敵の座標に追加
			enemyPositions.push_back(pos);
		}
	});

	//一番近い敵を探す
	float length = 999999.0f;
	int nearIndex = -1;
	int size = enemyPositions.size();
	for (int i = 0; i < size; i++)
	{
		//距離
		float l = Vector3::Length(enemyPositions.at(i) - GetPosition());
		//距離が近い場合は更新
		if (l < length)
		{
			length = l;
			nearIndex = i;
		}
	}

	//敵がいるなら
	if (nearIndex != -1)
	{
		//ホーミング
		Vector3 toEnemy = enemyPositions.at(nearIndex) - GetPosition();
		toEnemy.Normalize();
		targetDirection = toEnemy;
		direction = Vector3::Lerp(direction, targetDirection, HOMING_LERP_VALUE);
	}

	//向きを修正
	Quaternion q = Quaternion::RotateAxis(Vector3::Cross(Vector3(0, 0, 1), direction).Normalized(), Vector3::Inner(Vector3(0, 0, 1), direction));
	rotate = Quaternion::Rotate(q);
}

void PlayerMissile::OnDraw() const
{
	glPushMatrix();
	glMultMatrixf(scale.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::MISSILE_MODEL);
	glPopMatrix();

	//body.Translate(position).Draw();
}

void PlayerMissile::OnCollide(Actor& other,const HitInfo& info)
{
	if (other.GetName() == "BarrierSphere")
	{
		gsPlaySE(SOUND_ID::REFRECT_SE);
		world->AddActor(ActorGroup::Effect, std::make_shared<Reflect>(world, position, 30.0f));
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position, Vector3::Zero));
		Dead();
	}
	else
	{
		gsPlaySE(SOUND_ID::BOMB_MIDDLE_SE);
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position, Vector3::Zero));
		Dead();
	}
}