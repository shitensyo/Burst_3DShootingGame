#include "Camera.h"
#include "../../World/IWorld.h"

//コンストラクタ
Camera::Camera(IWorld* world) :
	Actor(world, "Camera", { 0.0f, 0.0f, 0.0f }, BoundingSphere(1.0f)) {
}

//更新
void Camera::OnUpdate(float deltaTime) {
	(void)deltaTime;
	//プレーヤを検索
	auto player = world->FindActor("Player");
	//プレーヤがいない
	if (player == nullptr) return;

	//プレーヤの座標を取得
	position = player->GetPosition() + Vector3(0.0f, 0.0f, 0.0f);
	//プレーヤの回転（向き）を取得
	rotate = player->GetRotate();
}

//描画
void Camera::OnDraw() const {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(GetPose().ToGSmatrix4().convertViewRH());
}
