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
	//��Փx�i���Ԍo�߂ŏ㏸�A�����l1�j
	int gameLevel;
	//��Փx�㏸�p�^�C�}�[
	float gameLevelTimer;
	//��Փx�㏸�^�C���i�[�p
	std::vector<float> gameLevelChangeTimes;
	//�����Ɏg�p����^�C�}�[
	float createTimer;
	float createTime;

	//�����ɔg�𔭐�������^�C�}�[
	float waveTimer;

};