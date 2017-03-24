#include "ActorManager.h"
#include "ActorGroup.h"
#include "../../Def.h"
#include "../Camera/TpsCamera.h"
#include "../Light/Light.h"
#include "../../Field/FieldPtr.h"
#include "../../Field/Field.h"

ActorManager::ActorManager():
	player(nullptr)
{
	Initialize();
}

void ActorManager::Initialize()
{
	//�O���[�v�A�N�^�[�̐���
	actors[ActorGroup::Enemy] = std::make_shared<Actor>();
	actors[ActorGroup::EnemyGenerator] = std::make_shared<Actor>();
	actors[ActorGroup::EnemyBullet] = std::make_shared<Actor>();
	actors[ActorGroup::Effect] = std::make_shared<Actor>();
	actors[ActorGroup::Stage] = std::make_shared<Actor>();
	actors[ActorGroup::Player] = std::make_shared<Actor>();
	actors[ActorGroup::PlayerBullet] = std::make_shared<Actor>();
	actors[ActorGroup::Boss] = std::make_shared<Actor>();
	actors[ActorGroup::Barrier] = std::make_shared<Actor>();
	actors[ActorGroup::UI] = std::make_shared<Actor>();

	normalActor.ClearChildren();
	bloomActor.ClearChildren();
	uiActor.ClearChildren();
	//������Ƌ��������Ǖ`�揇�͂����Ō��߂�
	//��
	uiActor.AddChild(actors[ActorGroup::UI]);

	bloomActor.AddChild(actors[ActorGroup::Player]);
	bloomActor.AddChild(actors[ActorGroup::Effect]);
	bloomActor.AddChild(actors[ActorGroup::Barrier]);
	bloomActor.AddChild(actors[ActorGroup::Boss]);
	bloomActor.AddChild(actors[ActorGroup::Enemy]);

	normalActor.AddChild(actors[ActorGroup::PlayerBullet]);
	normalActor.AddChild(actors[ActorGroup::EnemyBullet]);
	normalActor.AddChild(actors[ActorGroup::Stage]);
	normalActor.AddChild(actors[ActorGroup::EnemyGenerator]);
	//��

	//�`��̐ݒ�
	normalDraw = new RenderTarget(WINDOW_WIDTH, WINDOW_HEIGHT);
	//�u���[���`��̐ݒ�
	bloomEffect = new Effect("res/shader/bloom.fx");
	bloomBase = new RenderTarget(WINDOW_WIDTH, WINDOW_HEIGHT);
	extract = new RenderTarget(BLOOM_WIDTH, BLOOM_HEIGHT);
	blurV = new RenderTarget(BLOOM_WIDTH, BLOOM_HEIGHT);
	blurH = new RenderTarget(BLOOM_WIDTH, BLOOM_HEIGHT);
	conbine = new RenderTarget(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void ActorManager::Update(float deltaTime) 
{
	normalActor.Update(deltaTime);
	bloomActor.Update(deltaTime);
	uiActor.Update(deltaTime);
	Collide();
	normalActor.RemoveChildren();
	bloomActor.RemoveChildren();
	uiActor.RemoveChildren();
}

void ActorManager::Draw() const
{

	//�ʏ�`��J�n
	normalDraw->begin();
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//�J�����̕`��
		world->GetCamera()->Draw();
		//���C�g�̕`��
		world->GetLight()->Draw();
		//�t�B�[���h�̕`��i�X�J�C�{�b�N�X�Ȃǁj
		world->GetField()->Draw();
		//�A�N�^�[�̕`��
		normalActor.Draw();
		bloomActor.Draw();
	normalDraw->end();

	//normalActor.Draw();
	//bloomActor.Draw();

	//�u���[���`��J�n
	bloomBase->begin();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	bloomActor.Draw();
	bloomBase->end();

	//�P�x���o�`��
	extract->begin();
	glViewport(0, 0, BLOOM_WIDTH, BLOOM_HEIGHT);
	bloomEffect->setTechnique("BloomExtract");
	bloomEffect->setTexture("g_RenderTarget", bloomBase->colorBuffer());
	bloomEffect->begin();
	extract->draw();
	bloomEffect->end();
	extract->end();

	//�P�x�ɑ΂��ďc�Ɖ��Ƀu���[��������
	blurV->begin();
	glViewport(0, 0, BLOOM_WIDTH, BLOOM_HEIGHT);
	bloomEffect->setTechnique("GaussianBlurV");
	bloomEffect->setTexture("g_RenderTarget", extract->colorBuffer());
	bloomEffect->begin();
	blurV->draw();
	bloomEffect->end();
	blurV->end();
	blurH->begin();
	glViewport(0, 0, BLOOM_WIDTH, BLOOM_HEIGHT);
	bloomEffect->setTechnique("GaussianBlurH");
	bloomEffect->setTexture("g_RenderTarget", blurV->colorBuffer());
	bloomEffect->begin();
	blurH->draw();
	bloomEffect->end();
	blurH->end();

	//�ʏ�`��ƃu���[���`�������
	conbine->begin();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	bloomEffect->setTechnique("BloomConbine");
	bloomEffect->setTexture("g_BackGroundTexture", normalDraw->colorBuffer());
	bloomEffect->setTexture("g_BloomTexture", blurH->colorBuffer());
	bloomEffect->begin();
	conbine->draw();
	bloomEffect->end();
	conbine->end();

	//���̂������̂�`��
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glBindTexture(GL_TEXTURE_2D, conbine->colorBuffer());
	glEnable(GL_TEXTURE_2D);
	conbine->draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	//UI��`��
	uiActor.Draw();
}

void ActorManager::SetWorld(IWorld * world_){
	world = world_;
}

void ActorManager::AddActor(ActorGroup group, const ActorPtr& actor) {
	actors[group]->AddChild(actor);
}

void ActorManager::AddPlayer(const ActorPtr & actor)
{
	player = actor;
	actors[ActorGroup::Player]->AddChild(actor);
}

ActorPtr ActorManager::FindActor(const std::string& name) {
	ActorPtr p = FindNormalActor(name);
	if(p == nullptr)
		p = FindBloomActor(name);
	return p;
}

ActorPtr ActorManager::FindNormalActor(const std::string& name) {
	return normalActor.FindChildren(name);
}

ActorPtr ActorManager::FindBloomActor(const std::string& name) {
	return bloomActor.FindChildren(name);
}

ActorPtr ActorManager::GetPlayer(){
	return player;
}

void ActorManager::HandleMessage(EventMessage message, void* param) {
	normalActor.HandleMessage(message, param);
	bloomActor.HandleMessage(message, param);
	uiActor.HandleMessage(message, param);
}

ActorPtr ActorManager::GetGroupActor(const ActorGroup& group)
{
	return actors[group];
}

void ActorManager::Collide()
{
	actors[ActorGroup::Player]->CollideChildren(*actors[ActorGroup::Enemy]);
	actors[ActorGroup::Player]->CollideChildren(*actors[ActorGroup::EnemyBullet]);
	actors[ActorGroup::Barrier]->CollideChildren(*actors[ActorGroup::Player]);
	actors[ActorGroup::PlayerBullet]->CollideChildren(*actors[ActorGroup::Barrier]);
	actors[ActorGroup::PlayerBullet]->CollideChildren(*actors[ActorGroup::Enemy]);
	actors[ActorGroup::Boss]->CollideChildren(*actors[ActorGroup::PlayerBullet]);
	actors[ActorGroup::Boss]->CollideChildren(*actors[ActorGroup::Player]);
}
