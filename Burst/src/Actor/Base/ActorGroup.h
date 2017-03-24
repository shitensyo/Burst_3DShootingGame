#pragma once

enum class ActorGroup {
	Player,				//プレーヤ
	Enemy,				//敵
	EnemyGenerator,		//敵生成
	Boss,				//敵ボス
	PlayerBullet,		//プレーヤ弾
	EnemyBullet,		//敵弾
	Effect,				//エフェクト
	Stage,				//ステージ
	Barrier,			//バリア（球体）
	UI,					//ユーザーインターフェース（２Ｄ）
};
