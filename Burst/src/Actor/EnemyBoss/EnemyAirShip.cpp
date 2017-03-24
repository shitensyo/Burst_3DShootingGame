#include "EnemyAirShip.h"
#include <gslib.h>
#include "../AssetID.h"
#include "../../../EventMessage.h"
#include "../Effect/Explosion.h"
#include "../Base/ActorGroup.h"
#include "../EnemyBullet/EnemyMissile.h"
#include "AirShipMissileShooter.h"
#include "AirShipMachinegunShooter.h"
#include "../Enemy/RedFighter.h"
#include "AirShipContainer.h"
#include "../Effect/BasicParticle.h"
#include <GSmusic.h>

//���f���ǉ���Z�X�P�[��()
static const float MODEL_MUL_SCALE = 3.0f;
//���f����{�X�P�[��
static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(15.0f * MODEL_MUL_SCALE));

//���ˊԊu
static const float BULLET_INTERVAL = 1.0f;
//�e����
static const float BULLET_SPEED = 150.0f;

//�퓬�@�����Ԋu�����l
static const float FIGHTER_CREATE_INIT_INTERVAL = 60.0f;
//�퓬�@�����Ԋu����
static const float FIGHTER_CREATE_INC = 15.0f;
//�퓬�@����������
static const int FIGHTER_CREATE_NUM = 3;

//�����o�Ԋu
static const float SMOKE_INTERVAL = 0.15f;
//����{���x
static const float SMOKE_SPEED = 60.0f;
//������o���鍂��
static const float SMOKE_POSITION_HEIGHT = 50.0f;

EnemyAirShip::EnemyAirShip(IWorld * world_, const Vector3 & position_) :
	Actor(world_, "EnemyAirShip", position_,4000),
	timer(0.0f),
	target(nullptr),
	velocity(Vector3::Backward),
	speed(100.0f),
	angleX(0.0f),
	angleY(gsRandf(160.0f, 200.0f)),
	angleZ(gsRandf(0.0f, 360.0f)),
	addAngleZ(260.0f),
	fighterCreateTime(FIGHTER_CREATE_INIT_INTERVAL),
	fighterCreateTimer(0.0f),
	smokeTimer(0.0f)
{
	rotate.SetFront(Vector3::Backward);
	rotate.SetUp(Vector3::Up);
	rotate.SetLeft(Vector3::Left);

	player = world->FindActor("Player");
	if (player == nullptr) return;
	target = player->GetPositionPtr();

	//���苅��ǉ�
	AddBodySphere(BoundingSphere(Vector3(0, 0, -305)	* MODEL_MUL_SCALE, 30.0f * MODEL_MUL_SCALE));
	AddBodySphere(BoundingSphere(Vector3(0, 0, -275)	* MODEL_MUL_SCALE, 30.0f * MODEL_MUL_SCALE));
	AddBodySphere(BoundingSphere(Vector3(0, 0, -220)	* MODEL_MUL_SCALE, 50.0f * MODEL_MUL_SCALE));
	AddBodySphere(BoundingSphere(Vector3(0, 6, -160)	* MODEL_MUL_SCALE, 70.0f * MODEL_MUL_SCALE));

	AddBodySphere(BoundingSphere(Vector3(0, 90, -110)	* MODEL_MUL_SCALE, 40.0f * MODEL_MUL_SCALE));
	AddBodySphere(BoundingSphere(Vector3(0, 0, -80)		* MODEL_MUL_SCALE, 70.0f * MODEL_MUL_SCALE));
	AddBodySphere(BoundingSphere(Vector3(0, 16, -20)	* MODEL_MUL_SCALE, 56.0f * MODEL_MUL_SCALE));
	AddBodySphere(BoundingSphere(Vector3(0, 16, 40)		* MODEL_MUL_SCALE, 56.0f * MODEL_MUL_SCALE));
	AddBodySphere(BoundingSphere(Vector3(0, 0, 140)		* MODEL_MUL_SCALE, 60.0f * MODEL_MUL_SCALE));
	AddBodySphere(BoundingSphere(Vector3(0, 0, 220)		* MODEL_MUL_SCALE, 55.0f * MODEL_MUL_SCALE));
	AddBodySphere(BoundingSphere(Vector3(0, 0, 250)		* MODEL_MUL_SCALE, 38.0f * MODEL_MUL_SCALE));

	//�~�T�C���C���ǉ�
	ActorPtr child = std::make_shared<AirShipMissileShooter>(world, position + Vector3(0, 34, -200) * MODEL_MUL_SCALE, rotate);
	AddChild(child);
	child = std::make_shared<AirShipMissileShooter>(world, position + Vector3(0, 40, -100) * MODEL_MUL_SCALE, rotate);
	AddChild(child);
	child = std::make_shared<AirShipMissileShooter>(world, position + Vector3(0, 50, -30) * MODEL_MUL_SCALE, rotate);
	AddChild(child);

	Matrix4 rot;
	rot.SetUp(rotate.GetUp());
	rot.SetFront(-rotate.GetFront());
	rot.SetLeft(-rotate.GetLeft());
	child = std::make_shared<AirShipMissileShooter>(world, position + Vector3(0, 48, 160) * MODEL_MUL_SCALE, rot);
	AddChild(child);
	child = std::make_shared<AirShipMissileShooter>(world, position + Vector3(0, 34, 230) * MODEL_MUL_SCALE, rot);
	AddChild(child);

	//�}�V���K���C���ǉ�
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(10, 46, 40)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, 90.0f, 0.0f));
	AddChild(child);																			 
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(-10, 46, 40)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, -90.0f, 0.0f));
	AddChild(child);																			
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(20, 34, -50)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, 90.0f, 0.0f));
	AddChild(child);																			
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(-20, 34, -50)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, -90.0f, 0.0f));
	AddChild(child);																			
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(34, -23, -30)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, 90.0f, 180.0f));
	AddChild(child);																			 
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(-34, -23, -30)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, -90.0f, 180.0f));
	AddChild(child);																			
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(34, -23, 10)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, 90.0f, 180.0f));
	AddChild(child);														 					
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(-34, -23, 10)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, -90.0f, 180.0f));
	AddChild(child);

	//1�@�����퓬�@�𐶐�
	world->AddActor(ActorGroup::Enemy, std::make_shared<RedFighter>(world, Vector3(0,0,5000)));

	smokePositions.push_back(position + Vector3(10, 30, -150) * MODEL_MUL_SCALE);
	smokePositions.push_back(position + Vector3(-10, 90, 110) * MODEL_MUL_SCALE);
	smokePositions.push_back(position + Vector3(0, 30, 200) * MODEL_MUL_SCALE);

	smokePositions.push_back(position + Vector3(-5, 20, -305)	* MODEL_MUL_SCALE);
	smokePositions.push_back(position + Vector3(-7, 30, -160)	* MODEL_MUL_SCALE);
	smokePositions.push_back(position + Vector3(7, 20, -90)		* MODEL_MUL_SCALE);
	smokePositions.push_back(position + Vector3(10, 20, 250)		* MODEL_MUL_SCALE);

}

void EnemyAirShip::OnUpdate(float deltaTime)
{
	////�f�o�b�O�p �����Ǝ���
	//if (gsGetKeyTrigger(GKEY_P))
	//{
	//	hp = -1;
	//	//�����蔻�������
	//	BodySpheresClear();
	//	//�����̃G�t�F�N�g�𐶐�
	//	world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position, Vector3::Zero, 80, 3.0f, 600.0f, 0.98f, 50.0f));
	//	gsPlaySE(SOUND_ID::BOMB_BIG_SE);
	//	//�t�F�[�h�A�E�g
	//	world->SendMessageW(EventMessage::FadeOut);
	//	//�a�f�l����~
	//	gsStopMusic();
	//}


	//�퓬�@�𐶐�
	fighterCreateTimer += deltaTime;
	if (fighterCreateTimer > fighterCreateTime)
	{
		fighterCreateTimer = 0.0f;
		fighterCreateTime += FIGHTER_CREATE_INC;
		for (int i = 0; i < FIGHTER_CREATE_NUM; i++)
		{
			world->AddActor(ActorGroup::Enemy, std::make_shared<RedFighter>(world, 
				Vector3(
					gsRandf(-1000.0f,1000.0f),
					gsRandf(-1000.0f, 1000.0f),
					gsRandf(4500.0f, 5000.0f))));
		}
	}


	//�ϋv�l�ɉ����ĉ��𐁂�
	if (hp < 500)
	{
		smokeTimer += deltaTime;
		if (smokeTimer > SMOKE_INTERVAL)
		{
			smokeTimer = gsRandf(-0.1f, 0.0f);
			Vector3 dir = Vector3(gsRandf(0.0f, 0.2f), gsRandf(0.6f, 1.0f), gsRandf(0.0f, 0.2f));
			dir.Normalize();
			float speed = SMOKE_SPEED * gsRandf(0.9f, 3.1f);
			for (int i = 0; i < smokePositions.size(); i++)
			{
				Vector3 pos = smokePositions.at(i);
				world->AddActor(ActorGroup::Effect, std::make_shared<BasicParticle>(world, TEXTURE_ID::BLACK_SMOKE_TEX, pos, dir * speed, 12.0f, 2.0f));
			}
		}
	}
}

void EnemyAirShip::OnDraw() const
{
	//���f���̕`��
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::BOSS_AIR_SHIP);
	glPopMatrix();

	//body.Translate(position).Draw();

	//���苅��`��
	//BodySpheresDraw();
}

void EnemyAirShip::OnCollide(Actor & other,const HitInfo& info)
{
	//�v���C���[�ƏՓ˂����Ƃ��͉������Ȃ�
	if (other.GetName() == "Player") return;
	//hp���O�ɂȂ�����P�x����
	if (hp <= 0) return;

	hp--;
	if (hp <= 0)
	{
		//�����蔻�������
		BodySpheresClear();
		//�����̃G�t�F�N�g�𐶐�
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position, Vector3::Zero, 80, 3.0f, 600.0f, 0.98f, 50.0f));
		gsPlaySE(SOUND_ID::BOMB_BIG_SE);
		//�a�f�l����~
		gsStopMusic();
	}
}
