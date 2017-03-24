#include "Camera.h"
#include "../../World/IWorld.h"

//�R���X�g���N�^
Camera::Camera(IWorld* world) :
	Actor(world, "Camera", { 0.0f, 0.0f, 0.0f }, BoundingSphere(1.0f)) {
}

//�X�V
void Camera::OnUpdate(float deltaTime) {
	(void)deltaTime;
	//�v���[��������
	auto player = world->FindActor("Player");
	//�v���[�������Ȃ�
	if (player == nullptr) return;

	//�v���[���̍��W���擾
	position = player->GetPosition() + Vector3(0.0f, 0.0f, 0.0f);
	//�v���[���̉�]�i�����j���擾
	rotate = player->GetRotate();
}

//�`��
void Camera::OnDraw() const {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(GetPose().ToGSmatrix4().convertViewRH());
}
