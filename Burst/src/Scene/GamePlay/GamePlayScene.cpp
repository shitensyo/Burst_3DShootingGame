#include "GamePlayScene.h"
#include <GSmusic.h>
#include "../Base/Scene.h"
#include "../../World/World.h"
#include "../../Actor/Light/Light.h"
#include "../../Actor/Camera/TpsCamera.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Player/Player.h"
#include "../../../EventMessage.h"
#include "../../Actor/AssetID.h"
#include "../../Actor/Stage/StageMountain.h"
#include "../../Actor/Enemy/EnemyGenerator.h"
#include <GSeasing.h>
#include "../../Def.h"

GamePlayScene::GamePlayScene() : 
	isEnd(false),
	isResult(false),
	resultTimer(0.0f),
	plateTimer(0.0f),
	resultNumberTex(TEXTURE_ID::RESULT_NUM_TEX,64,128)
{
}

GamePlayScene::~GamePlayScene()
{
}

void GamePlayScene::Start() 
{
	isEnd = false;
	isResult = false;
	resultTimer = 0.0f;
	plateTimer = 0.0f;
	spaceTexture = FlashTexture(TEXTURE_ID::OSU_TEXTURE);

	//アセットの読み込み
	//モデル
	gsLoadMesh(MODEL_ID::PLAYER_MODEL, "res/model/player/player.msh");
	gsLoadMesh(MODEL_ID::PLAYER_BOOSTER_MODEL, "res/model/player/booster.msh");
	gsLoadMesh(MODEL_ID::SKY_MODEL, "res/model/sky/skydome.msh");
	gsLoadMesh(MODEL_ID::ENEMY_1_MODEL, "res/model/enemy/enemy1.msh");
	gsLoadMesh(MODEL_ID::ENEMY_2_MODEL, "res/model/enemy/enemy2.msh");
	gsLoadMesh(MODEL_ID::ENEMY_3_MODEL, "res/model/enemy/enemy3.msh");
	gsLoadMesh(MODEL_ID::ENEMY_3_PROPELLER_MODEL, "res/model/enemy/enemy3propeller.msh");
	gsLoadMesh(MODEL_ID::MOUNTAIN_MODEL, "res/model/mountain/mountain.msh");
	gsLoadMesh(MODEL_ID::MACHINEGUN_MODEL, "res/model/playerbullet/machinegun.msh");
	gsLoadMesh(MODEL_ID::ENEMY_MACHINEGUN_MODEL, "res/model/enemybullet/enemymachinegun.msh");
	gsLoadMesh(MODEL_ID::ENEMY_MISSILE_MODEL, "res/model/enemybullet/missile.msh");

	//２Ｄ、３Ｄテクスチャ
	gsLoadTexture(TEXTURE_ID::FIRE_TEX, "res/texture/fire.bmp");
	gsLoadTexture(TEXTURE_ID::SMOKE_TEX, "res/texture/smoke.png");
	gsLoadTexture(TEXTURE_ID::LOGO_TEX, "res/texture/logo.png");
	gsLoadTexture(TEXTURE_ID::HP_GAUGE_TEX, "res/texture/gauge.png");
	gsLoadTexture(TEXTURE_ID::HP_GAUGE_FRAME_TEX, "res/texture/gauge_frame.png");
	gsLoadTexture(TEXTURE_ID::STAR_TEX, "res/texture/star.png");
	gsLoadTexture(TEXTURE_ID::PLATE_BRONZ_TEX, "res/texture/bronz_plate.png");
	gsLoadTexture(TEXTURE_ID::PLATE_SILVER_TEX, "res/texture/silver_plate.png");
	gsLoadTexture(TEXTURE_ID::PLATE_GOLD_TEX, "res/texture/gold_plate.png");
	gsLoadTexture(TEXTURE_ID::CLASS_TEXT_TEX, "res/texture/class_text.png");
	gsLoadTexture(TEXTURE_ID::RESULT_NUM_TEX, "res/texture/result_number.png");
	gsLoadTexture(TEXTURE_ID::RESULT_SENKA_TEX, "res/texture/senka_text.png");
	gsLoadTexture(TEXTURE_ID::RESULT_GEKIHA_TEX, "res/texture/gekihasu_text.png");
	gsLoadTexture(TEXTURE_ID::OSU_TEXTURE, "res/texture/osu.png");

	//音
	gsLoadMusic(SOUND_ID::GAME_BGM, "res/sound/gameplay.mp3", GS_TRUE);
	gsLoadSE(SOUND_ID::BOMB_SMOLL_SE, "res/sound/bomb_mini.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::BOMB_MIDDLE_SE, "res/sound/bomb_middle.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::BOMB_BIG_SE, "res/sound/bomb_big.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::DAMAGE_SE, "res/sound/damage.wav", 1, GWAVE_DEFAULT);

	//ワールドの追加
	world = std::make_shared<World>();
	world->AddEventMessageListener([=](EventMessage msg, void* param) {HandleMessage(msg, param);}	);

	//ワールドに追加
	world->AddField(std::make_shared<Field>(MODEL_ID::SKY_MODEL));
	world->AddCamera(std::make_shared<TpsCamera>(world.get(),5.0f,80.0f));
	world->AddLight(std::make_shared<Light>(world.get(), Vector3(100.0f, 100.0f, 100.0f)));
	player = std::make_shared<Player>(world.get(), Vector3(0.0f, 0.0f, 0.0f));
	world->AddPlayer(player);
	world->AddActor(ActorGroup::Stage, std::make_shared<StageMountain>(world.get()));
	world->AddActor(ActorGroup::EnemyGenerator, std::make_shared<EnemyGenerator>(world.get()));
	//撃破スコア初期化
	score = Score(0);

	//BGMを再生
	gsBindMusic(SOUND_ID::GAME_BGM);
	gsPlayMusic();
	gsSetMusicVolume(1.0f);
}

void GamePlayScene::Update(float deltaTime) {
	//プレイヤーが死んだらリザルト処理を開始
	if (player->IsDead())
		Result(deltaTime);
	else
		world->Update(deltaTime);
}

void GamePlayScene::Draw() const
{
	//透視変換行列の設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, ASPECT, PERSPECTIVE_NEAR, PERSPECTIVE_FAR);
	world->Draw();

	score.Draw();
	if (isResult)
	{
		if(resultTimer > 7.0f)
			gsDrawSprite2D(TEXTURE_ID::RESULT_SENKA_TEX, &GSvector2(250, 20), &GSrect(0, 0, 320, 128), NULL, NULL, &GSvector2(1, 1), 0);
		if (resultTimer > 7.3f)
			gsDrawSprite2D(TEXTURE_ID::RESULT_GEKIHA_TEX, &GSvector2(100, 350), &GSrect(0, 0, 320, 128), NULL, NULL, &GSvector2(1, 1), 0);
		if (resultTimer > 7.6f)
			resultNumberTex.Draw(Vector2(450, 350), score.GetScore());
		if (resultTimer > 8.0f)
			spaceTexture.draw(GSvector2(160, 500));
	}
}

bool GamePlayScene::IsEnd() const
{
	return isEnd;
}

Scene GamePlayScene::Next() const {
	return Scene::Title;
}

void GamePlayScene::End() {
	world = nullptr;

	gsDeleteMesh(MODEL_ID::PLAYER_MODEL);
	gsDeleteMesh(MODEL_ID::PLAYER_BOOSTER_MODEL);
	gsDeleteMesh(MODEL_ID::SKY_MODEL);
	gsDeleteMesh(MODEL_ID::ENEMY_1_MODEL);
	gsDeleteMesh(MODEL_ID::ENEMY_2_MODEL);
	gsDeleteMesh(MODEL_ID::ENEMY_3_MODEL);
	gsDeleteMesh(MODEL_ID::ENEMY_3_PROPELLER_MODEL);
	gsDeleteMesh(MODEL_ID::MOUNTAIN_MODEL);
	gsDeleteMesh(MODEL_ID::MACHINEGUN_MODEL);
	gsDeleteMesh(MODEL_ID::ENEMY_MACHINEGUN_MODEL);
	gsDeleteMesh(MODEL_ID::ENEMY_MISSILE_MODEL);

	gsDeleteTexture(TEXTURE_ID::FIRE_TEX);
	gsDeleteTexture(TEXTURE_ID::SMOKE_TEX);
	gsDeleteTexture(TEXTURE_ID::LOGO_TEX);
	gsDeleteTexture(TEXTURE_ID::HP_GAUGE_TEX);
	gsDeleteTexture(TEXTURE_ID::HP_GAUGE_FRAME_TEX);
	gsDeleteTexture(TEXTURE_ID::STAR_TEX);
	gsDeleteTexture(TEXTURE_ID::PLATE_BRONZ_TEX);
	gsDeleteTexture(TEXTURE_ID::PLATE_SILVER_TEX);
	gsDeleteTexture(TEXTURE_ID::PLATE_GOLD_TEX);
	gsDeleteTexture(TEXTURE_ID::CLASS_TEXT_TEX);
	gsDeleteTexture(TEXTURE_ID::RESULT_NUM_TEX);
	gsDeleteTexture(TEXTURE_ID::RESULT_SENKA_TEX);
	gsDeleteTexture(TEXTURE_ID::RESULT_GEKIHA_TEX);
	gsDeleteTexture(TEXTURE_ID::OSU_TEXTURE);

	gsDeleteMusic(SOUND_ID::GAME_BGM);
	gsDeleteSE(SOUND_ID::BOMB_SMOLL_SE);
	gsDeleteSE(SOUND_ID::BOMB_MIDDLE_SE);
	gsDeleteSE(SOUND_ID::BOMB_BIG_SE);
	gsDeleteSE(SOUND_ID::DAMAGE_SE);
}

void GamePlayScene::HandleMessage(EventMessage message, void* param) {
	switch (message) {
	case EventMessage::AddScore:
		int* s = (int*)param;
		score.AddScore(*s);
		break;
	}
}

void GamePlayScene::Result(float deltaTime)
{
	isResult = true;
	resultTimer += deltaTime;
	spaceTexture.Update(deltaTime);

	//２秒間はスロー再生
	if (resultTimer < 2.0f)
		world->Update(deltaTime / 2);
	else
		world->Update(deltaTime);

	//5秒超えたらリザルト開始
	if (resultTimer > 5.0f)
	{
		//階級プレートを動かす
		plateTimer += deltaTime;
		Vector2 start = score.GetInitPlateBasePos();
		Vector2 end = Vector2(300, 200);
		static const float END_TIME = 1.4f;
		score.SetPlateBasePos(Vector2::Lerp(start, end, gsEasingOutExpo(plateTimer / END_TIME)));
	}
	if (resultTimer > 8.0f)
	{
		//スペースキーで終了
		if (gsGetKeyTrigger(GKEY_SPACE) == GS_TRUE) {
			isEnd = true;
		}
	}
}
