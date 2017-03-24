#include "Game.h"
#include "../Scene/Base/SceneManager.h"
#include "../Scene/Base/Scene.h"
#include "../Scene/Title/TitleScene.h"
#include "../Scene/GamePlay/GamePlayScene.h"
#include "../Scene/AirShipStage/AirShipStageScene.h"
#include "../Scene/AirShipClear/AirShipClearScene.h"
#include "../Def.h"

Game::Game() : 
	gslib::Game(WINDOW_WIDTH, WINDOW_HEIGHT,false) 
{
	//ビューポートの設定
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	//透視射影の変換行列を設定する
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		45.0f,
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
		0.3f,
		2000.0f
		);
	//モデルビューモードにする
	glMatrixMode(GL_MODELVIEW);
}

void Game::start()
{
	sceneManager.add(Scene::Title, std::make_shared<TitleScene>());
	sceneManager.add(Scene::GamePlay, std::make_shared<GamePlayScene>());
	sceneManager.add(Scene::AirShipStageScene, std::make_shared<AirShipStageScene>());
	sceneManager.add(Scene::AirShipClearScene, std::make_shared<AirShipClearScene>());
	sceneManager.change(Scene::Title);
}

void Game::update(float deltaFrame)
{
	sceneManager.Update(deltaFrame / 60.0f);
}

void Game::draw() 
{
	sceneManager.Draw();
}

void Game::end() 
{
	sceneManager.End();
}
