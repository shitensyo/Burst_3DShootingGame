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

//�z�[�~���O�J�n����
static const float HOMING_START_TIME = 0.5f;
//���G�͈́@���g�̑O�����ƓG�����̓��ς�����𒴂����ꍇ�́A�z�[�~���O����
static const float DOT_LIMIT = 0.8f;
//�z�[�~���O�⊮�l
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

	//�ړ�
	position += direction * speed * deltaTime;
	speed += MOVE_SPEED_INC * deltaTime;

	//�i�s�����Ƃ͋t�����ɉ��G�t�F�N�g�𔭎�
	smokeTimer += deltaTime;
	if (timer > SMOKE_INTERVAL)
	{
		smokeTimer = 0.0f;
		world->AddActor(ActorGroup::Effect, std::make_shared<MissileSmoke>(world, position, -direction, SMOKE_END_TIME));
	}

	//�w��b���𒴂�����z�[�~���O�J�n
	if (timer < HOMING_START_TIME) return;

	//���G�͈͓��̓G�̍��W�擾
	enemyPositions.clear();
	ActorPtr enemys = world->GetGroup(ActorGroup::Enemy);
	enemys->EachChildren([&](Actor& child)
	{
		Vector3 pos = child.GetPosition();

		//�O�㔻��
		Vector3 toEnemy = pos - position;
		toEnemy.Normalize();
		float dot = Vector3::Dot(GetRotate().GetFront(), toEnemy);
		//�G�����G�͈͂ɂ���Ȃ�
		if (dot > DOT_LIMIT)
		{
			//�G�̍��W�ɒǉ�
			enemyPositions.push_back(pos);
		}
	});

	//��ԋ߂��G��T��
	float length = 999999.0f;
	int nearIndex = -1;
	int size = enemyPositions.size();
	for (int i = 0; i < size; i++)
	{
		//����
		float l = Vector3::Length(enemyPositions.at(i) - GetPosition());
		//�������߂��ꍇ�͍X�V
		if (l < length)
		{
			length = l;
			nearIndex = i;
		}
	}

	//�G������Ȃ�
	if (nearIndex != -1)
	{
		//�z�[�~���O
		Vector3 toEnemy = enemyPositions.at(nearIndex) - GetPosition();
		toEnemy.Normalize();
		targetDirection = toEnemy;
		direction = Vector3::Lerp(direction, targetDirection, HOMING_LERP_VALUE);
	}

	//�������C��
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