#include "AirShipStageScene.h"
#include <GSmusic.h>
#include "../Base/Scene.h"
#include "../../World/World.h"
#include "../../Actor/Light/Light.h"
#include "../../Actor/Camera/TpsCamera.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Player/AirPlayer.h"
#include "../../../EventMessage.h"
#include "../../Actor/AssetID.h"
#include "../../Actor/Stage/StageDestroyBase.h"
#include "../../Actor/Enemy/EnemyGenerator.h"
#include <GSeasing.h>
#include "../../Def.h"
#include "../../Actor/EnemyBoss/EnemyAirShip.h"
#include "../../Actor/Barrier/BarrierSphere.h"
#include "../../Actor/Barrier/BarrierGenerator.h"
#include "../../Actor/Enemy/RedFighter.h"
#include "../../Actor/UI/BossHPGauge.h"
#include "../../Actor/EnemyBoss/AirShipContainer.h"
#include "../../Actor/Effect/Explosion.h"
#include "../../Actor/UI/Communication.h"
#include "../../Actor/UI/BasicTexture.h"
#include "../../Actor/UI/Fade.h"
#include "../../Actor/UI/FadeFlashTexture.h"
#include "../../Actor/EnemyBoss/DeadAirShip.h"

static const float TO_TITLE_TIME = 5.0f;

AirShipStageScene::AirShipStageScene() :
	isEnd(false),
	isResult(false),
	resultTimer(0.0f),
	plateTimer(0.0f),
	//resultNumberTex(TEXTURE_ID::RESULT_NUM_TEX, 64, 128),
	player(nullptr),
	boss(nullptr),
	stageClearTimer(0.0f),
	isToTitleWaiting(false),
	isToTitle(false),
	isPause(false),
	pauseTimer(0.0f)
{
}

AirShipStageScene::~AirShipStageScene()
{
}

void AirShipStageScene::Start()
{
	isEnd = false;
	isResult = false;
	resultTimer = 0.0f;
	plateTimer = 0.0f;
	//spaceTexture = FlashTexture(TEXTURE_ID::OSU_TEXTURE);
	stageClearTimer = 0.0f;
	isToTitleWaiting = false;
	isToTitle = false;
	isPause = false;
	pauseTimer = 0.0f;


	//リソースの読み込み
	//モデル
	gsLoadMesh(MODEL_ID::PLAYER_MODEL, "res/model/player/player.msh");
	gsLoadMesh(MODEL_ID::PLAYER_BOOSTER_MODEL, "res/model/player/booster.msh");
	gsLoadMesh(MODEL_ID::SKY_MODEL, "res/model/sky/stage5skybox.msh");
	gsLoadMesh(MODEL_ID::ENEMY_1_MODEL, "res/model/enemy/enemy1.msh");
	gsLoadMesh(MODEL_ID::ENEMY_2_MODEL, "res/model/enemy/enemy2.msh");
	gsLoadMesh(MODEL_ID::ENEMY_3_MODEL, "res/model/enemy/enemy3.msh");
	gsLoadMesh(MODEL_ID::ENEMY_3_PROPELLER_MODEL, "res/model/enemy/enemy3propeller.msh");
	gsLoadMesh(MODEL_ID::MOUNTAIN_MODEL, "res/model/mountain/mountain.msh");
	gsLoadMesh(MODEL_ID::MACHINEGUN_MODEL, "res/model/playerbullet/machinegun.msh");
	gsLoadMesh(MODEL_ID::MISSILE_MODEL, "res/model/playerbullet/playermissile.msh");
	gsLoadMesh(MODEL_ID::ENEMY_MACHINEGUN_MODEL, "res/model/enemybullet/enemymachinegun.msh");
	gsLoadMesh(MODEL_ID::ENEMY_MISSILE_MODEL, "res/model/enemybullet/missile.msh");
	gsLoadMesh(MODEL_ID::BOSS_AIR_SHIP, "res/model/bossenemy/flybattleship.msh");
	gsLoadMesh(MODEL_ID::BOSS_AIR_SHIP_MISSILE_SHOOTER, "res/model/bossenemy/flybattleship_mis.msh");
	gsLoadMesh(MODEL_ID::BOSS_AIR_SHIP_MACHINEGUN_SHOOTER, "res/model/bossenemy/flybattleship_gun.msh");
	gsLoadMesh(MODEL_ID::BARRIER_SPHERE, "res/model/barrier/barriersphere.msh");
	gsLoadMesh(MODEL_ID::BARRIER_POLE, "res/model/barrier/barrierpole.msh");
	gsLoadMesh(MODEL_ID::BARRIER_GENERATOR, "res/model/barrier/barriergenerator.msh");
	gsLoadMesh(MODEL_ID::RED_FIGHTER_MODEL, "res/model/enemy/redfighter.msh");
	gsLoadMesh(MODEL_ID::CONTAINER_MODEL, "res/model/enemy/container.msh");

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
	gsLoadTexture(TEXTURE_ID::REFLECT_TEXTURE, "res/texture/reflect.png");
	gsLoadTexture(TEXTURE_ID::BLACK_SMOKE_TEX, "res/texture/blacksmoke.png");
	gsLoadTexture(TEXTURE_ID::DASH_LINE_TEXTURE, "res/texture/speedLine.png");
	gsLoadTexture(TEXTURE_ID::LOCKON_CURSOR_TEX, "res/texture/cursor.png");
	gsLoadTexture(TEXTURE_ID::BOSS_GAUGE_FRAME_TEX, "res/texture/bossgaugeframe.png");
	gsLoadTexture(TEXTURE_ID::BOSS_GAUGE_TEX, "res/texture/bossgauge.png");
	gsLoadTexture(TEXTURE_ID::BLACK_BAR_TEX, "res/texture/blackbar.png");
	gsLoadTexture(TEXTURE_ID::MISSILE_GAUGE_FRAME_TEX, "res/texture/missileframe.png");
	gsLoadTexture(TEXTURE_ID::MISSILE_GAUGE_TEX, "res/texture/missile.png");
	gsLoadTexture(TEXTURE_ID::MISSILE_GAUGE_BLACK_TEX, "res/texture/missileblack.png");
	gsLoadTexture(TEXTURE_ID::BLACK_TEX, "res/texture/black.png");
	gsLoadTexture(TEXTURE_ID::MISS_TEX, "res/texture/miss.png");
	gsLoadTexture(TEXTURE_ID::TUTORIAL_TEX, "res/texture/tutorial.png");


	//音
	gsLoadMusic(SOUND_ID::GAME_BGM, "res/sound/PureSprint.wma", GS_TRUE);
	gsLoadSE(SOUND_ID::BOMB_SMOLL_SE, "res/sound/bomb_mini.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::BOMB_MIDDLE_SE, "res/sound/bomb_middle.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::BOMB_BIG_SE, "res/sound/bomb_big.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::DAMAGE_SE, "res/sound/damage.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::HIT_SE, "res/sound/hit.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::RECEPTION_SE, "res/sound/reception.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::REFRECT_SE, "res/sound/refrect.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::MISSILE_SE, "res/sound/missile.wav", 1, GWAVE_DEFAULT);

	//ワールドの追加
	world = std::make_shared<World>();
	world->AddEventMessageListener([=](EventMessage msg, void* param) {HandleMessage(msg, param); });

	//ワールドに追加
	world->AddField(std::make_shared<Field>(MODEL_ID::SKY_MODEL));
	world->AddLight(std::make_shared<Light>(world.get(), Vector3(100.0f, 100.0f, 100.0f)));
	world->AddActor(ActorGroup::UI, std::make_shared<Fade>(world.get()));
	player = std::make_shared<AirPlayer>(world.get(), Vector3(0.0f, 0.0f, -20000.0f));
	world->AddPlayer(player);
	boss = std::make_shared<EnemyAirShip>(world.get(), Vector3(0, 0, 0));
	world->AddActor(ActorGroup::Boss, boss);
	world->AddActor(ActorGroup::UI, std::make_shared<BossHPGauge>(world.get(), boss));
	world->AddActor(ActorGroup::Enemy, std::make_shared<AirShipContainer>(world.get(), boss, Vector3(0, -120, -40)));

	world->AddActor(ActorGroup::Barrier, std::make_shared<BarrierSphere>(world.get(), Vector3(0, 0, 0)));
	world->AddActor(ActorGroup::Enemy, std::make_shared<BarrierGenerator>(world.get(), Vector3(-1500, 0, 0)));
	world->AddActor(ActorGroup::Enemy, std::make_shared<BarrierGenerator>(world.get(), Vector3(1500, 0, 0)));

	world->AddCamera(std::make_shared<TpsCamera>(world.get(), Vector3(0.0f, 0.0f, -14200.0f)));

	world->AddActor(ActorGroup::UI, std::make_shared<Communication>(world.get(), boss, Vector2(0, 10)));


	//撃破スコア初期化
	score = Score(0);

	//BGMを再生
	gsBindMusic(SOUND_ID::GAME_BGM);
	gsPlayMusic();
	gsSetMusicVolume(1.0f);
}

void AirShipStageScene::Update(float deltaTime) 
{
	//ポーズ中はワールドの更新を行わない
	if (gsGetKeyTrigger(GKEY_RETURN)) isPause = !isPause;
	if (isPause)
	{
		pauseTimer += deltaTime;
		return;
	}
		
	//プレイヤーが死んだらリザルト処理を開始
	if (player->IsDead())
		Result(deltaTime);
	else
		//ワールドの更新
		world->Update(deltaTime);

	//ボスが死んだらステージクリア開始
	if (boss->GetHP() <= 0)
	{
		//フェードアウト
		world->SendMessageW(EventMessage::FadeOut);
		stageClearTimer += deltaTime;
		if (stageClearTimer > 5.0f)
			isEnd = true;
	}
}

void AirShipStageScene::Draw() const
{
	//透視変換行列の設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, ASPECT, PERSPECTIVE_NEAR, PERSPECTIVE_FAR);
	world->Draw();

	//ポーズ画面の描画
	if (isPause && !isResult)
	{
		gsDrawSprite2D(TEXTURE_ID::BLACK_TEX, NULL, NULL, NULL, &GScolor(1.0f,1.0f,1.0f,0.6f), NULL, 0);
		gsDrawSprite2D(TEXTURE_ID::TUTORIAL_TEX, NULL, NULL, NULL, NULL, NULL, 0);
		//ポーズテキスト
		std::string text = "ポーズ中";
		for (int i = 0; i < (int)(pauseTimer * 4.0f) % 4; i++){			
			text += ".";
		}
		gsTextPos(5,42);
		gsDrawText("");
		gsTextDraw(GS_FONT_NORMAL, 48, "メイリオ", text.c_str());
	}
}

bool AirShipStageScene::IsEnd() const
{
	return isEnd;
}

Scene AirShipStageScene::Next() const {
	if(boss->GetHP() <= 0)
		return Scene::AirShipClearScene;

	return Scene::Title;
}

void AirShipStageScene::End() {
	world = nullptr;
	player = nullptr;
	boss = nullptr;

	gsDeleteMesh(MODEL_ID::PLAYER_MODEL);
	gsDeleteMesh(MODEL_ID::PLAYER_BOOSTER_MODEL);
	gsDeleteMesh(MODEL_ID::SKY_MODEL);
	gsDeleteMesh(MODEL_ID::ENEMY_1_MODEL);
	gsDeleteMesh(MODEL_ID::ENEMY_2_MODEL);
	gsDeleteMesh(MODEL_ID::ENEMY_3_MODEL);
	gsDeleteMesh(MODEL_ID::ENEMY_3_PROPELLER_MODEL);
	gsDeleteMesh(MODEL_ID::MOUNTAIN_MODEL);
	gsDeleteMesh(MODEL_ID::MACHINEGUN_MODEL);
	gsDeleteMesh(MODEL_ID::MISSILE_MODEL);
	gsDeleteMesh(MODEL_ID::ENEMY_MACHINEGUN_MODEL);
	gsDeleteMesh(MODEL_ID::ENEMY_MISSILE_MODEL);
	gsDeleteMesh(MODEL_ID::BOSS_AIR_SHIP);
	gsDeleteMesh(MODEL_ID::BOSS_AIR_SHIP_MISSILE_SHOOTER);
	gsDeleteMesh(MODEL_ID::BOSS_AIR_SHIP_MACHINEGUN_SHOOTER);
	gsDeleteMesh(MODEL_ID::BARRIER_SPHERE);
	gsDeleteMesh(MODEL_ID::BARRIER_POLE);
	gsDeleteMesh(MODEL_ID::BARRIER_GENERATOR);
	gsDeleteMesh(MODEL_ID::RED_FIGHTER_MODEL);
	gsDeleteMesh(MODEL_ID::CONTAINER_MODEL);

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
	gsDeleteTexture(TEXTURE_ID::REFLECT_TEXTURE);
	gsDeleteTexture(TEXTURE_ID::BLACK_SMOKE_TEX);
	gsDeleteTexture(TEXTURE_ID::DASH_LINE_TEXTURE);
	gsDeleteTexture(TEXTURE_ID::LOCKON_CURSOR_TEX);
	gsDeleteTexture(TEXTURE_ID::BOSS_GAUGE_FRAME_TEX);
	gsDeleteTexture(TEXTURE_ID::BOSS_GAUGE_TEX);
	gsDeleteTexture(TEXTURE_ID::BLACK_BAR_TEX);
	gsDeleteTexture(TEXTURE_ID::MISSILE_GAUGE_FRAME_TEX);
	gsDeleteTexture(TEXTURE_ID::MISSILE_GAUGE_TEX);
	gsDeleteTexture(TEXTURE_ID::MISSILE_GAUGE_BLACK_TEX);
	gsDeleteTexture(TEXTURE_ID::BLACK_TEX);
	gsDeleteTexture(TEXTURE_ID::MISS_TEX);

	gsDeleteMusic(SOUND_ID::GAME_BGM);
	gsDeleteSE(SOUND_ID::BOMB_SMOLL_SE);
	gsDeleteSE(SOUND_ID::BOMB_MIDDLE_SE);
	gsDeleteSE(SOUND_ID::BOMB_BIG_SE);
	gsDeleteSE(SOUND_ID::DAMAGE_SE);
	gsDeleteSE(SOUND_ID::HIT_SE);
	gsDeleteSE(SOUND_ID::RECEPTION_SE);
	gsDeleteSE(SOUND_ID::REFRECT_SE);
	gsDeleteSE(SOUND_ID::MISSILE_SE);
}

void AirShipStageScene::HandleMessage(EventMessage message, void* param) {
	//switch (message) {
	//スコア増加
	//case EventMessage::AddScore:
	//	int* s = (int*)param;
	//	score.AddScore(*s);
	//	break;
	//}
}

void AirShipStageScene::Result(float deltaTime)
{
	isResult = true;
	resultTimer += deltaTime;

	//２秒間はスロー再生
	if (resultTimer < 2.0f)
		world->Update(deltaTime / 2);
	else
		world->Update(deltaTime);

	if (resultTimer > 6.0f)
	{
		if (!isToTitleWaiting)
		{
			world->AddActor(ActorGroup::UI, std::make_shared<FadeFlashTexture>(world.get(), TEXTURE_ID::OSU_TEXTURE, Vector2(160, 500)));
			world->AddActor(ActorGroup::UI, std::make_shared<BasicTexture>(world.get(), TEXTURE_ID::MISS_TEX, Vector2(250, 100)));
		}
		isToTitleWaiting = true;

		//スペースキーで終了
		if (!isToTitle && gsGetKeyTrigger(GKEY_SPACE) == GS_TRUE)
		{
			isToTitle = true;
			//フェードアウト
			world->SendMessageW(EventMessage::FadeOut);
		}
	}

	if (isToTitle)
	{
		stageClearTimer += deltaTime;
		if (stageClearTimer > TO_TITLE_TIME)
			isEnd = true;
	}
}
