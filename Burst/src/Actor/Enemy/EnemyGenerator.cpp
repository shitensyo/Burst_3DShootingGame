#include "EnemyGenerator.h"
#include "../Base/ActorGroup.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"

//最大難易度
static const int LEVEL_MAX = 4;
static const float LEVEL_1_END_TIME = 60.0f;
static const float LEVEL_2_END_TIME = 60.0f;
static const float LEVEL_3_END_TIME = 60.0f;

//waveTimer倍率
static const float WAVE_MAGNIFICATION = 10.0f;

EnemyGenerator::EnemyGenerator(IWorld * world):
	Actor(world, "EnemyGenerator", Vector3::Zero, BoundingSphere(0.0f)),
	gameLevel(1),
	gameLevelTimer(0.0f),
	createTimer(0.0f),
	createTime(1.0f),
	waveTimer(180.0f)
{
	gameLevelChangeTimes.clear();
	gameLevelChangeTimes.push_back(LEVEL_1_END_TIME);
	gameLevelChangeTimes.push_back(LEVEL_2_END_TIME);
	gameLevelChangeTimes.push_back(LEVEL_3_END_TIME);
}

EnemyGenerator::~EnemyGenerator()
{
}

void EnemyGenerator::OnUpdate(float deltaTime)
{
	//難易度上昇
	if (gameLevel != LEVEL_MAX)
	{
		//設定した時間に達したら難易度上昇
		gameLevelTimer += deltaTime;
		if (gameLevelTimer > gameLevelChangeTimes.at(gameLevel - 1))
		{
			gameLevelTimer = 0.0f;
			gameLevel++;
		}
	}

	//敵の生成
	waveTimer += deltaTime * WAVE_MAGNIFICATION;
	createTimer += deltaTime;
	if (createTimer > createTime)
	{
		createTimer = 0.0f;
		//難易度によって生成方法を切り替え
		switch (gameLevel)
		{
		case 1:Level1(deltaTime); break;
		case 2:Level2(deltaTime); break;
		case 3:Level3(deltaTime); break;
		case 4:Level4(deltaTime); break;
		default: break;
		}
	}
}

void EnemyGenerator::OnDraw() const
{
	////デバッグ文字描画
	//gsTextPos(0, 32);
	//gsDrawText("gameLevel : %d", gameLevel);
	//gsTextPos(0, 48);
	//gsDrawText("waveTimer * 60 : %f", Math::Sin(waveTimer));
}

void EnemyGenerator::CreateEnemy(const EnemyType& enemyType, const Vector3& pos)
{
	world->AddActor(ActorGroup::Enemy, std::make_shared<Enemy1>(world, pos));
}

void EnemyGenerator::Level1(float deltaTime)
{
	createTime = gsRandf(0.9f, 1.5f) - Math::Sin(waveTimer);
	world->AddActor(ActorGroup::Enemy, std::make_shared<Enemy1>(world,
		Vector3(gsRandf(-100.0f, 100.0f), gsRandf(-100.0f, 100.0f), 2000.0f)));
}

void EnemyGenerator::Level2(float deltaTime)
{
	createTime = gsRandf(0.9f, 1.5f) - Math::Sin(waveTimer);
	int a = gsRand(0, 1);
	if (a == 0)
		world->AddActor(ActorGroup::Enemy, std::make_shared<Enemy1>(world,
			Vector3(gsRandf(-100.0f, 100.0f), gsRandf(-100.0f, 100.0f), 2000.0f)));
	else if (a == 1)
		world->AddActor(ActorGroup::Enemy, std::make_shared<Enemy2>(world,
			Vector3(gsRandf(-100.0f, 100.0f), gsRandf(-100.0f, 100.0f), 2000.0f)));
}

void EnemyGenerator::Level3(float deltaTime)
{
	createTime = gsRandf(0.8f, 1.4f) - Math::Sin(waveTimer);
	int a = gsRand(0, 8);
	if (a <= 6)
		world->AddActor(ActorGroup::Enemy, std::make_shared<Enemy1>(world,
			Vector3(gsRandf(-100.0f, 100.0f), gsRandf(-100.0f, 100.0f), 2000.0f)));
	else if (a <= 7)
		world->AddActor(ActorGroup::Enemy, std::make_shared<Enemy2>(world,
			Vector3(gsRandf(-100.0f, 100.0f), gsRandf(-100.0f, 100.0f), 2000.0f)));
	else
		world->AddActor(ActorGroup::Enemy, std::make_shared<Enemy3>(world,
			Vector3(gsRandf(-100.0f, 100.0f), gsRandf(-100.0f, 100.0f), 2000.0f)));
}

void EnemyGenerator::Level4(float deltaTime)
{
	createTime = gsRandf(0.8f, 1.4f) - Math::Sin(waveTimer);
	int a = gsRand(0, 7);
	if (a <= 5)
		world->AddActor(ActorGroup::Enemy, std::make_shared<Enemy1>(world,
			Vector3(gsRandf(-100.0f, 100.0f), gsRandf(0.0f, 100.0f), 2000.0f)));
	else if (a <= 6)
		world->AddActor(ActorGroup::Enemy, std::make_shared<Enemy2>(world,
			Vector3(gsRandf(-100.0f, 100.0f), gsRandf(-100.0f, 100.0f), 2000.0f)));
	else
		world->AddActor(ActorGroup::Enemy, std::make_shared<Enemy3>(world,
			Vector3(gsRandf(-100.0f, 100.0f), gsRandf(-100.0f, 100.0f), 2000.0f)));
}
