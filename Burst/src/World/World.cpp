#include "World.h"
#include "../Field/Field.h"
#include "../Actor/Base/ActorPtr.h"
#include "../Actor/Base/ActorGroup.h"

World::World() :
	listener([](EventMessage, void*) {}),
	lookat(Matrix4::Identity)
{
	actors.SetWorld(this);
}

void World::Update(float deltaTime)
{
	actors.Update(deltaTime);
	camera->Update(deltaTime);
	light->Update(deltaTime);
}

void World::Draw() const 
{
	//camera->Draw();
	//light->Draw();
	//field->Draw();
	actors.Draw();
}

void World::HandleMessage(EventMessage message, void* param)
{
	//ワールドのメッセージ処理
	listener(message, param);
	//アクターのメッセージ処理
	actors.HandleMessage(message, param);
	camera->HandleMessage(message, param);
	light->HandleMessage(message, param);
}

void World::AddField(const FieldPtr& field_) {
	field = field_;
}

void World::AddCamera(const ActorPtr& camera_) {
	camera = camera_;
}

void World::AddLight(const ActorPtr& light_) {
	light = light_;
}

void World::AddActor(ActorGroup group, const ActorPtr& actor) {
	actors.AddActor(group, actor);
}

void World::AddPlayer(const ActorPtr & actor)
{
	actors.AddPlayer(actor);
}

ActorPtr World::FindActor(const std::string& name) {
	return actors.FindActor(name);
}

ActorPtr World::GetPlayer(){
	return actors.GetPlayer();
}

void World::SendMessage(EventMessage message, void* param) {
	HandleMessage(message, param);
}

void World::AddEventMessageListener(std::function<void(EventMessage, void*)> listener_){
	listener = listener_;
}

FieldPtr World::GetField() const {
	return field;
}

ActorPtr World::GetLight() const {
	return light;
}

ActorPtr World::GetCamera()const {
	return camera;
}

void World::SetLookAt(const Matrix4 & lookat_)
{
	lookat = lookat_;
}

Matrix4 World::GetLookAt() const
{
	return lookat;
}

ActorPtr World::GetGroup(const ActorGroup& group)
{
	return actors.GetGroupActor(group);
}

