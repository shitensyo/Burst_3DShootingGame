#include "AirShipContainer.h"
#include "../AssetID.h"
#include "../Effect/Explosion.h"
#include "../Base/ActorGroup.h"
#include "../../../EventMessage.h"
#include "../../Def.h"

//���f����{�X�P�[��
static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(0.5f,0.6f,0.8f));


//�J�[�\���X�P�[��
static const float CURSOR_SCALE = 0.2f;
//�J�[�\����]��
static const float CURSOR_ANGLE_ADD = 30.0f;

AirShipContainer::AirShipContainer(IWorld * world_, ActorPtr boss_, const Vector3 & position_):
	Actor(world_,"AirShipContainer",position_,BoundingSphere(120.0f),150),
	boss(boss_),
	cursorAngle(0.0f),
	isCursorDraw(false)
{
}

void AirShipContainer::OnMessage(EventMessage event, void *)
{
	if (event == EventMessage::ContainerPhase)
	{
		isCursorDraw = true;
	}
}

void AirShipContainer::OnUpdate(float deltaTime)
{
	cursorAngle += CURSOR_ANGLE_ADD * deltaTime;
}

void AirShipContainer::OnDraw() const
{	
	//���f���̕`��
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::CONTAINER_MODEL);
	glPopMatrix();

	//�J�[�\���̕`��
	if (!isCursorDraw) return;
	GSvector3 cameraPos = world->GetCamera()->GetPosition().ToGSvector3();
	GSvector3 playerPos = world->GetPlayer()->GetPosition().ToGSvector3();
	GSvector3 cameraToPlayer = playerPos - cameraPos;
	cameraToPlayer.normalize();
	GSvector3 cameraToGenerator = position.ToGSvector3() - cameraPos;
	cameraToGenerator.normalize();
	//�J�����̔w�ʂɂ���ꍇ�͌v�Z����ѕ`������Ȃ�
	if (cameraToPlayer.dot(cameraToGenerator) < 0.0f) return;
	GSmatrix4 wmat, vmat, pmat, smat;
	wmat.identity();//���[���h�ϊ��s��
	vmat.identity();//�r���[�i�����j�ϊ��s��
	pmat.identity();//�ˉe�ϊ��s��
	smat.identity();//�X�N���[���ϊ��s��

	wmat.setPosition(position.ToGSvector3());
	vmat.setLookAtRH(cameraPos, playerPos, GSvector3(0, 1, 0));
	pmat.setPerspectiveRH(FOV, ASPECT, PERSPECTIVE_NEAR, PERSPECTIVE_FAR);
	smat = Matrix4::Screen(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT).ToGSmatrix4();
	GSmatrix4 wvp = wmat * vmat * pmat;
	float w = wvp.m[3][3];
	GSvector3 projpos = wvp.getPosition() / w;
	GSmatrix4 drawmat;
	drawmat.identity();
	drawmat.setPosition(projpos);
	drawmat *= smat;
	//�`����W�����o��
	GSvector2 drowPos = GSvector2(drawmat.getPosition().x, drawmat.getPosition().y);
	drowPos += GSvector2(0, 2);
	//�J�[�\���̑傫��
	GSvector2 s;
	gsDrawSprite2D(TEXTURE_ID::LOCKON_CURSOR_TEX, &drowPos, &GSrect(0, 0, 256, 256), &(GSvector2(320, 320) * CURSOR_SCALE * 2), NULL, &GSvector2(CURSOR_SCALE, CURSOR_SCALE), cursorAngle);
}

void AirShipContainer::OnCollide(Actor & other, const HitInfo & info)
{
	if (other.GetName() == "Player") return;

	hp--;
	if (hp <= 0)
	{
		if (isDead) return;

		//�{�X�̗̑͂�����Ď��S
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position, Vector3::Zero, 80, 3.0f, 600.0f, 0.98f, 50.0f));
		gsPlaySE(SOUND_ID::BOMB_BIG_SE);
		Dead();
		boss->AddHP(-3500);
	}
}
