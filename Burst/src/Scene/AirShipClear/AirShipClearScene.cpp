#include "AirShipClearScene.h"
#include <GSmusic.h>
#include "../Base/Scene.h"
#include "../../World/World.h"
#include "../../Actor/Light/Light.h"
#include "../../Actor/Camera/TpsCamera.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Player/AirClearPlayer.h"
#include "../../../EventMessage.h"
#include "../../Actor/AssetID.h"
#include "../../Actor/Stage/StageDestroyBase.h"
#include "../../Actor/Enemy/EnemyGenerator.h"
#include <GSeasing.h>
#include "../../Def.h"
#include "../../Actor/EnemyBoss/DeadAirShip.h"
#include "../../Actor/UI/Communication.h"
#include "../../Actor/UI/Fade.h"
#include "../../Actor/Camera/AirShipClearCamera.h"

AirShipClearScene::AirShipClearScene() :
	isEnd(false),
	world(nullptr),
	timer(0.0f),
	stageClearTimer(0.0f)
{
}

AirShipClearScene::~AirShipClearScene()
{
}

void AirShipClearScene::Start()
{
	isEnd = false;
	world = nullptr;
	timer = 0.0f;
	stageClearTimer = 0.0f;

	//リソースの読み込み
	//モデル
	gsLoadMesh(MODEL_ID::PLAYER_MODEL, "res/model/player/player.msh");
	gsLoadMesh(MODEL_ID::PLAYER_BOOSTER_MODEL, "res/model/player/booster.msh");
	gsLoadMesh(MODEL_ID::SKY_MODEL, "res/model/sky/stage5skybox.msh");
	gsLoadMesh(MODEL_ID::BOSS_AIR_SHIP, "res/model/bossenemy/flybattleship.msh");
	gsLoadMesh(MODEL_ID::BOSS_AIR_SHIP_MISSILE_SHOOTER, "res/model/bossenemy/flybattleship_mis.msh");
	gsLoadMesh(MODEL_ID::BOSS_AIR_SHIP_MACHINEGUN_SHOOTER, "res/model/bossenemy/flybattleship_gun.msh");

	//２Ｄ、３Ｄテクスチャ
	gsLoadTexture(TEXTURE_ID::FIRE_TEX, "res/texture/fire.bmp");
	gsLoadTexture(TEXTURE_ID::SMOKE_TEX, "res/texture/smoke.png");
	gsLoadTexture(TEXTURE_ID::BLACK_SMOKE_TEX, "res/texture/blacksmoke.png");
	gsLoadTexture(TEXTURE_ID::BLACK_BAR_TEX, "res/texture/blackbar.png");
	gsLoadTexture(TEXTURE_ID::BLACK_TEX, "res/texture/black.png");

	//音
	gsLoadSE(SOUND_ID::BOMB_SMOLL_SE, "res/sound/bomb_mini.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::BOMB_MIDDLE_SE, "res/sound/bomb_middle.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::BOMB_BIG_SE, "res/sound/bomb_big.wav", 1, GWAVE_DEFAULT);
	gsLoadSE(SOUND_ID::RECEPTION_SE, "res/sound/reception.wav", 1, GWAVE_DEFAULT);

	//ワールドの追加
	world = std::make_shared<World>();
	world->AddEventMessageListener([=](EventMessage msg, void* param) {HandleMessage(msg, param); });
	world->AddField(std::make_shared<Field>(MODEL_ID::SKY_MODEL));
	world->AddLight(std::make_shared<Light>(world.get(), Vector3(100.0f, 100.0f, 100.0f)));
	world->AddPlayer(std::make_shared<AirClearPlayer>(world.get()));
	world->AddActor(ActorGroup::UI, std::make_shared<Fade>(world.get()));
	world->AddActor(ActorGroup::Boss, std::make_shared<DeadAirShip>(world.get(), Vector3(0, 0, 0)));
	world->AddCamera(std::make_shared<AirShipClearCamera>(world.get()));

	world->AddActor(ActorGroup::UI, std::make_shared<Communication>(world.get(), nullptr, Vector2(0, 10), Communication::Phase::CLEAR));
}

void AirShipClearScene::Update(float deltaTime)
{
	world->Update(deltaTime);

	//ボスが死んだらステージクリア開始
	if (world->FindActor("DeadAirShip") == nullptr)
	{
		stageClearTimer += deltaTime;
		if (stageClearTimer > 3.0f)
			world->SendMessageW(EventMessage::FadeOut);
		if (stageClearTimer > 6.0f)
			isEnd = true;
	}
}

void AirShipClearScene::Draw() const
{
	//透視変換行列の設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, ASPECT, PERSPECTIVE_NEAR, PERSPECTIVE_FAR);
	world->Draw();
}

bool AirShipClearScene::IsEnd() const
{
	return isEnd;
}

Scene AirShipClearScene::Next() const {
	return Scene::Title;
}

void AirShipClearScene::End() {
	world = nullptr;

	gsDeleteMesh(MODEL_ID::PLAYER_MODEL);
	gsDeleteMesh(MODEL_ID::PLAYER_BOOSTER_MODEL);
	gsDeleteMesh(MODEL_ID::SKY_MODEL);
	gsDeleteMesh(MODEL_ID::BOSS_AIR_SHIP);
	gsDeleteMesh(MODEL_ID::BOSS_AIR_SHIP_MISSILE_SHOOTER);
	gsDeleteMesh(MODEL_ID::BOSS_AIR_SHIP_MACHINEGUN_SHOOTER);

	gsDeleteTexture(TEXTURE_ID::FIRE_TEX);
	gsDeleteTexture(TEXTURE_ID::SMOKE_TEX);
	gsDeleteTexture(TEXTURE_ID::BLACK_SMOKE_TEX);
	gsDeleteTexture(TEXTURE_ID::BLACK_BAR_TEX);
	gsDeleteTexture(TEXTURE_ID::BLACK_TEX);

	gsDeleteSE(SOUND_ID::BOMB_SMOLL_SE);
	gsDeleteSE(SOUND_ID::BOMB_MIDDLE_SE);
	gsDeleteSE(SOUND_ID::BOMB_BIG_SE);
	gsDeleteSE(SOUND_ID::RECEPTION_SE);
}

void AirShipClearScene::HandleMessage(EventMessage message, void* param) {

}

