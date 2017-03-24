#include "TitleScene.h"
#include "../../Def.h"
#include "../Base/Scene.h"
#include <gslib.h>
#include "../../Actor/AssetID.h"
#include<GSmusic.h>
#include "../../World/World.h"
#include "../../../EventMessage.h"
#include "../../Actor/Light/Light.h"
#include "../../Field/Field.h"
#include "../../Actor/Base/ActorGroup.h"
#include "../../Actor/Camera/TitleCamera.h"
#include "../../Actor/Earth/Earth.h"
#include "../../Actor/UI/Fade.h"
#include "../../Actor/Player/TitlePlayer.h"
#include "../../Actor/UI/BasicTexture.h"
#include "../../Actor/UI/FadeFlashTexture.h"

TitleScene::TitleScene() :
	isEnd(false),
	isToEnd(false),
	timer(0.0f)
{
}

TitleScene::~TitleScene() 
{
}

void TitleScene::Start() 
{
	isEnd = false;
	isToEnd = false;
	timer = 0.0f;

	gsLoadMesh(MODEL_ID::PLAYER_MODEL, "res/model/player/player.msh");
	gsLoadMesh(MODEL_ID::PLAYER_BOOSTER_MODEL, "res/model/player/booster.msh");
	gsLoadMesh(MODEL_ID::EARTH_MODEL, "res/model/earth/earth.msh");
	gsLoadMesh(MODEL_ID::SKY_MODEL, "res/model/sky/soraskybox.msh");

	gsLoadTexture(TEXTURE_ID::TITLE_TEXTURE, "res/texture/title.bmp"); 
	gsLoadTexture(TEXTURE_ID::OSU_TEXTURE, "res/texture/osu.png");
	gsLoadTexture(TEXTURE_ID::LOGO_TEX, "res/texture/logo.png");
	gsLoadTexture(TEXTURE_ID::TITLE_LOGO_TEX, "res/texture/titlelogo.png");
	gsLoadTexture(TEXTURE_ID::BLACK_TEX, "res/texture/black.png");

	gsLoadMusic(SOUND_ID::TITLE_BGM, "res/sound/title.mp3", GS_TRUE);
	gsLoadSE(SOUND_ID::START_SE, "res/sound/start.wav", 1, GWAVE_DEFAULT);

	//ワールドの追加
	world = std::make_shared<World>();

	world->AddEventMessageListener([=](EventMessage msg, void* param) {HandleMessage(msg, param); });
	world->AddField(std::make_shared<Field>(MODEL_ID::SKY_MODEL));
	world->AddLight(std::make_shared<Light>(world.get(), Vector3(100.0f, 100.0f, 100.0f)));

	world->AddActor(ActorGroup::UI, std::make_shared<Fade>(world.get()));
	world->AddActor(ActorGroup::UI, std::make_shared<BasicTexture>(world.get(),TEXTURE_ID::TITLE_LOGO_TEX,Vector2(74, 60)));
	world->AddActor(ActorGroup::UI, std::make_shared<FadeFlashTexture>(world.get(), TEXTURE_ID::OSU_TEXTURE, Vector2(160, 500)));

	world->AddActor(ActorGroup::Enemy,std::make_shared<Earth>(world.get(),Vector3(0,-100,00)));
	world->AddPlayer(std::make_shared<TitlePlayer>(world.get(), Vector3(0, 13, 13)));
	world->AddCamera(std::make_shared<TitleCamera>(world.get(),Vector3(0,20,60), Vector3(0,10,0)));

	//BGMを再生
	gsBindMusic(SOUND_ID::TITLE_BGM);
	gsPlayMusic();
	gsSetMusicVolume(0.9f);
}

void TitleScene::Update(float deltaTime)
{
	world->Update(deltaTime);

	if (!isToEnd && gsGetKeyTrigger(GKEY_SPACE) == GS_TRUE)
	{
		isToEnd = true;
		gsPlaySE(SOUND_ID::START_SE);
		world->SendMessageW(EventMessage::FadeOut);
	}

	if (isToEnd)
	{
		timer += deltaTime;
		if (timer > 2.0f)
		{
			gsStopMusic();
			isEnd = true; 
		}
	}

}

void TitleScene::Draw() const 
{
	//透視変換行列の設定
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, ASPECT, PERSPECTIVE_NEAR, PERSPECTIVE_FAR);
	world->Draw();

	if (isToEnd) return;
}

bool TitleScene::IsEnd() const 
{
	return isEnd;
}

Scene TitleScene::Next() const 
{
	//おまけのミニゲームがあそべる
	if (gsGetKeyState(GKEY_O) == GS_TRUE) return Scene::GamePlay;
	return Scene::AirShipStageScene;
}

void TitleScene::End() 
{
	gsDeleteMesh(MODEL_ID::PLAYER_MODEL);
	gsDeleteMesh(MODEL_ID::PLAYER_BOOSTER_MODEL);
	gsDeleteMesh(MODEL_ID::EARTH_MODEL);
	gsDeleteMesh(MODEL_ID::SKY_MODEL);

	gsDeleteTexture(TEXTURE_ID::TITLE_TEXTURE);
	gsDeleteTexture(TEXTURE_ID::OSU_TEXTURE);
	gsDeleteTexture(TEXTURE_ID::LOGO_TEX);
	gsDeleteTexture(TEXTURE_ID::TITLE_LOGO_TEX);
	gsDeleteTexture(TEXTURE_ID::BLACK_TEX);

	gsDeleteMusic(SOUND_ID::TITLE_BGM);
	gsDeleteSE(SOUND_ID::START_SE);
}


void TitleScene::HandleMessage(EventMessage message, void* param) {

}