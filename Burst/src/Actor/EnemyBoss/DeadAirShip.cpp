#include "DeadAirShip.h"
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

//モデル追加乗算スケール()
static const float MODEL_MUL_SCALE = 3.0f;
//モデル基本スケール
static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(15.0f * MODEL_MUL_SCALE));

//発射間隔
static const float BULLET_INTERVAL = 1.0f;
//弾初速
static const float BULLET_SPEED = 150.0f;

//戦闘機生成間隔初期値
static const float FIGHTER_CREATE_INIT_INTERVAL = 60.0f;
//戦闘機生成間隔増分
static const float FIGHTER_CREATE_INC = 15.0f;
//戦闘機同時生成数
static const int FIGHTER_CREATE_NUM = 3;

//煙放出間隔
static const float SMOKE_INTERVAL = 0.1f;
//煙基本速度
static const float SMOKE_SPEED = 60.0f;
//煙を放出する高さ
static const float SMOKE_POSITION_HEIGHT = 50.0f;

static const float LIFE_TIME = 8.0f;


DeadAirShip::DeadAirShip(IWorld * world_, const Vector3 & position_) :
	Actor(world_, "DeadAirShip", position_, 100),
	timer(0.0f),
	bombTime(gsRandf(0.3f,0.6f)),
	velocity(Vector3::Backward),
	speed(100.0f),
	angleX(0.0f),
	angleY(gsRandf(160.0f, 200.0f)),
	angleZ(gsRandf(0.0f, 360.0f)),
	smokeTimer(0.0f),
	lifeTimer(0.0f)
{
	rotate.SetFront(Vector3::Backward);
	rotate.SetUp(Vector3::Up);
	rotate.SetLeft(Vector3::Left);

	//ミサイル砲台を追加
	ActorPtr child = std::make_shared<AirShipMissileShooter>(world, position + Vector3(0, 34, -200) * MODEL_MUL_SCALE, rotate, false);
	AddChild(child);
	child = std::make_shared<AirShipMissileShooter>(world, position + Vector3(0, 40, -100) * MODEL_MUL_SCALE, rotate, false);
	AddChild(child);
	child = std::make_shared<AirShipMissileShooter>(world, position + Vector3(0, 50, -30) * MODEL_MUL_SCALE, rotate, false);
	AddChild(child);

	Matrix4 rot;
	rot.SetUp(rotate.GetUp());
	rot.SetFront(-rotate.GetFront());
	rot.SetLeft(-rotate.GetLeft());
	child = std::make_shared<AirShipMissileShooter>(world, position + Vector3(0, 48, 160) * MODEL_MUL_SCALE, rot, false);
	AddChild(child);
	child = std::make_shared<AirShipMissileShooter>(world, position + Vector3(0, 34, 230) * MODEL_MUL_SCALE, rot, false);
	AddChild(child);

	//マシンガン砲台を追加
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(10, 46, 40)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, 90.0f, 0.0f), false);
	AddChild(child);
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(-10, 46, 40)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, -90.0f, 0.0f), false);
	AddChild(child);
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(20, 34, -50)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, 90.0f, 0.0f), false);
	AddChild(child);
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(-20, 34, -50)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, -90.0f, 0.0f), false);
	AddChild(child);
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(34, -23, -30)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, 90.0f, 180.0f), false);
	AddChild(child);
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(-34, -23, -30)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, -90.0f, 180.0f), false);
	AddChild(child);
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(34, -23, 10)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, 90.0f, 180.0f), false);
	AddChild(child);
	child = std::make_shared<AirShipMachinegunShooter>(world, position + Vector3(-34, -23, 10)	 * MODEL_MUL_SCALE, Matrix4::CreateMatrix(Vector3::One, 0.0f, -90.0f, 180.0f), false);
	AddChild(child);

	smokePositions.push_back(position + Vector3(10, 30, -150) * MODEL_MUL_SCALE);
	smokePositions.push_back(position + Vector3(-10, 90, 110) * MODEL_MUL_SCALE);
	smokePositions.push_back(position + Vector3(0, 30, 200) * MODEL_MUL_SCALE);

	smokePositions.push_back(position + Vector3(-5, 20, -305)	* MODEL_MUL_SCALE);
	smokePositions.push_back(position + Vector3(-7, 30, -160)	* MODEL_MUL_SCALE);
	smokePositions.push_back(position + Vector3(7, 20, -90)		* MODEL_MUL_SCALE);
	smokePositions.push_back(position + Vector3(10, 20, 250)		* MODEL_MUL_SCALE);
}

void DeadAirShip::OnUpdate(float deltaTime)
{
	//爆発
	timer += deltaTime;
	if (timer > bombTime)
	{
		timer = 0.0f;
		bombTime = gsRandf(0.08f, 0.2f);
		Vector3 pos = Vector3(gsRandf(-200.0f, 200.0f), gsRandf(-200.0f, 200.0f), gsRandf(-500.0f, 500.0f));
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, pos, Vector3::Zero, 30, 1.0f, 800.0f, 0.88f, 20.0f));
		if(gsRand(0,10) == 0)
			gsPlaySE(SOUND_ID::BOMB_MIDDLE_SE);
		else
			gsPlaySE(SOUND_ID::BOMB_SMOLL_SE);
	}


	//煙を吹く
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

	//死亡
	lifeTimer += deltaTime;
	if (lifeTimer > LIFE_TIME)
	{
		Dead();
		gsPlaySE(SOUND_ID::BOMB_BIG_SE);
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position, Vector3::Zero, 80, 4.0f, 1600.0f, 0.98f, 80.0f));
	}
}

void DeadAirShip::OnDraw() const
{
	//モデルの描画
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::BOSS_AIR_SHIP);
	glPopMatrix();
}

void DeadAirShip::OnCollide(Actor & other, const HitInfo& info)
{

}
