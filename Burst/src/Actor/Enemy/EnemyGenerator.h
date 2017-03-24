#pragma once

#include"../Base/Actor.h"
#include "../../World/IWorld.h"
#include <vector>

class EnemyGenerator : public Actor
{
	enum EnemyType
	{
		ENEMY_1,
		ENEMY_2,
		BOSS,
	};

public:
	EnemyGenerator(IWorld* world);
	~EnemyGenerator();
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDraw() const override;

private:
	void CreateEnemy(const EnemyType& enemyType,const Vector3& pos);
	void Level1(float deltaTime);
	void Level2(float deltaTime);
	void Level3(float deltaTime);
	void Level4(float deltaTime);

private:
	//難易度（時間経過で上昇、初期値1）
	int gameLevel;
	//難易度上昇用タイマー
	float gameLevelTimer;
	//難易度上昇タイム格納用
	std::vector<float> gameLevelChangeTimes;
	//生成に使用するタイマー
	float createTimer;
	float createTime;

	//生成に波を発生させるタイマー
	float waveTimer;

};