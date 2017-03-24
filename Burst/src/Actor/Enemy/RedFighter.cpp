#include "RedFighter.h"
#include <gslib.h>
#include "../AssetID.h"
#include "../../../EventMessage.h"
#include "../Effect/Explosion.h"
#include "../Base/ActorGroup.h"
#include "../EnemyBullet/EnemyMachineGun.h"

static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(0.5f));
//�e���΂�����
static const Vector3 BULLET_VELOCITY = Vector3(0.0f, -1.0f, -10.0f).Normalized();
//���ˊԊu
static const float BULLET_INTERVAL = 0.2f;
//�e��
static const float BULLET_SPEED = 800.0f;
//�����ړ����x
static const float MOVE_SPEED_INIT = 200.0f;
//�����ړ����x
static const float MOVE_SPEED_DASH = 400.0f;

//�����������ɂ�����]���x
static const float ANGLE_SPEED_PITCH = 180.0f;
//����������ɂ�����]���x
static const float ANGLE_SPEED_YAW = 360.0f;

//�}�V���K�����ˈʒu�̕�
static const float MACHINEGUN_SHOT_WIDTH = 6.0f;
//�}�V���K�����ˈʒu�̑O������ 
static const float MACHINEGUN_SHOT_FRONT = 12.0f;

static const Matrix4 FIRE_SCALE = Matrix4::Scale(Vector3(0.3f, 0.3f, 0.6f));

RedFighter::RedFighter(IWorld * world_, const Vector3 & position_, const Matrix4 & rotate_):
	Actor(world_,"RedFighter", position_,BoundingSphere(10.0f),4),
	timer(0.0f),
	initRotate(rotate_),
	speed(MOVE_SPEED_INIT),
	bulletChange(1),
	front(Vector3::Zero),
	toPlayer(Vector3::Zero),
	dot(0.0f),
	boosterAngle(0.0f),
	prevRotate(rotate_),
	isBreakaway(false),
	breakawayTimer(0.0f)
{
	player = world->GetPlayer();
	rotate = rotate_;
}

void RedFighter::OnUpdate(float deltaTime)
{

	//�ړ�
	front = rotate.GetFront();
	velocity = front * speed * deltaTime;
	position += velocity;
	boosterAngle += 200.0f * deltaTime;

	player = world->GetPlayer();
	if (player == nullptr) return;

	//�v���C���[�̕���
	toPlayer = player->GetPosition() - position;
	toPlayer.Normalize();

	//�O�㔻��
	dot = Vector3::Dot(front, toPlayer);

	//�ʏ펞�̓v���C���[��ǂ�������
	if (!isBreakaway)
	{	
		//�v���C���[���w�ʂɂ��āA���������߂��ꍇ�͗��E���[�h�ֈڍs
		if (dot <= 0.1f && Vector3::Length(player->GetPosition() - position) < 800)
			isBreakaway = true;
		//����ȊO�̓v���C���[�Ɍ������ēːi
		else
		{
			speed = MOVE_SPEED_INIT;
			PlayerLookingRotation(deltaTime);
		}
	}
	//���E���͍����ړ����ăv���C���[���狗����u��
	else
	{
		breakawayTimer += deltaTime;
		speed = MOVE_SPEED_DASH;
		if (breakawayTimer > 4.0f && Vector3::Length(player->GetPosition() - position) > 1000)
		{
			breakawayTimer = 0.0f;
			isBreakaway = false;
		}
	}



	Attack(deltaTime);
}

void RedFighter::OnDraw() const
{
	//�@��
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::RED_FIGHTER_MODEL);
	glPopMatrix();

	//��
	glPushMatrix();
	Matrix4 mat =
		FIRE_SCALE *
		Matrix4::RotateZ(boosterAngle) *Matrix4::Translate(Vector3(5.6f, 0.4f, -72.0f)) *
		GetPose();
	glMultMatrixf(mat.ToGSmatrix4());
	gsDrawMesh(MODEL_ID::PLAYER_BOOSTER_MODEL);
	glPopMatrix();
	glPushMatrix();
	mat =
		FIRE_SCALE *
		Matrix4::RotateZ(boosterAngle) *Matrix4::Translate(Vector3(-5.6f, 0.4f, -72.0f)) *
		GetPose();
	glMultMatrixf(mat.ToGSmatrix4());
	gsDrawMesh(MODEL_ID::PLAYER_BOOSTER_MODEL);
	glPopMatrix();

	//gsTextPos(0, 64);
	//gsDrawText("anglepitch : %f", anglePitch);
}

void RedFighter::OnCollide(Actor & other, const HitInfo & info)
{
	hp--;
	if (hp <= 0 && isDead == false)
	{
		//�����̃G�t�F�N�g�𐶐����Ď��S
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position + Vector3(0.0f, 2.0f, 0.0f), velocity * speed));
		Dead();
		static const int addscore = 1;
		world->SendMessage(EventMessage::AddScore, (void*)&addscore);
		gsPlaySE(SOUND_ID::BOMB_SMOLL_SE);
	}
}


void RedFighter::PlayerLookingRotation(float deltaTime)
{
	////�s�b�`�����̃v���C���[�܂ł̊p�x
	//float anglePitch = Vector3::Inner(
	//	Vector3(0.0f, front.y, front.z).Normalized(),
	//	Vector3(0.0f, toPlayer.y, toPlayer.z).Normalized());
	////���[�����̃v���C���[�܂ł̊p�x
	//float angleYaw = Vector3::Inner(
	//	Vector3(front.x, 0.0f, front.z).Normalized(),
	//	Vector3(toPlayer.x, 0.0f, toPlayer.z).Normalized());


	//�v���C���[�̂ق�������
	//�p�x�␳�l
	float angleCorrection = Vector3::Inner(front, toPlayer) / 100.0f;

	float inputPitch = 1.0f * angleCorrection;
	//�㉺����
	if (front.y < toPlayer.y)
		inputPitch = -inputPitch;

	float inputYaw = 1.0f * angleCorrection;
	//���E����
	Vector3 cross = Vector3::Cross(front, toPlayer);
	//���E�ǂ���ɋȂ��邩������
	if (cross.y < 0)
		inputYaw = -inputYaw;

	inputPitch = Math::Clamp(inputPitch, -1.0f, 1.0f);
	inputYaw = Math::Clamp(inputYaw, -1.0f, 1.0f);


	//��]
	prevRotate = rotate;
	Matrix4 currentRotaet = rotate;
	currentRotaet *= Quaternion::RotateAxis(rotate.GetUp(), inputYaw * ANGLE_SPEED_YAW * deltaTime);
	currentRotaet *= Quaternion::RotateAxis(rotate.GetLeft(), inputPitch* ANGLE_SPEED_PITCH * deltaTime);
	rotate = Matrix4::Slerp(prevRotate, currentRotaet, 0.8f);
}

void RedFighter::Attack(float deltaTime)
{
	timer += deltaTime;
	if (timer > BULLET_INTERVAL)
	{
		//�v���C���[�����ʂɂ��Ȃ��ꍇ�͑ł��Ȃ�
		if (dot < 0) return;
		timer = 0.0f;
		//���ˈʒu�̌v�Z
		Vector3 pos =
			position +
			GetRotate().GetFront() * MACHINEGUN_SHOT_FRONT +
			GetRotate().GetLeft() * MACHINEGUN_SHOT_WIDTH * bulletChange;
		world->AddActor(ActorGroup::EnemyBullet, std::make_shared<EnemyMachineGun>(world, pos, rotate.GetFront() * BULLET_SPEED, 2.0f));
		//���ˈʒu�̍��E�؂�ւ�
		bulletChange *= -1;
	}
}