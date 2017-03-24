#include "AirPlayer.h"
#include <gslib.h>
#include "../AssetID.h"
#include "../../../EventMessage.h"
#include "../Base/ActorGroup.h"
#include "../PlayerBullet/PlayerMachineGun.h"
#include "../PlayerBullet/PlayerMissile.h"
#include "../Effect/Explosion.h"
#include "../Effect/HitSmoke.h"
#include <GSmusic.h>
#include "../UI/DashLine.h"
#include "../../../EventMessage.h"

//�ϋv�l
static const int HP_MAX = 10;

//�ړ����x
static const float MOVE_SPEED_Z = 200.0f;
//�ړ����x�i�_�b�V���j
static const float DASH_SPEED_Z = 600.0f;
//��]���x
static const float ANGLE_SPEED_X = 160.0f;
static const float ANGLE_SPEED_Y = 160.0f;
static const float ANGLE_SPEED_Z = 30.0f;

//�}�V���K�����ˈʒu�̕�
static const float MACHINEGUN_SHOT_WIDTH = 6.0f;
//�}�V���K�����ˈʒu�̑O������ 
static const float MACHINEGUN_SHOT_FRONT = 12.0f;

//�~�T�C�����ˈʒu�̕������l(4�񃋁[�v����)
static const float MISSILE_SHOT_WIDTH_INIT = -9.0f;
//�~�T�C�����ˈʒu�̕�����
static const float MISSILE_SHOT_WIDTH_INC = 6.0f;
//�~�T�C�����ˈʒu�̑O������ 
static const float MISSILE_SHOT_FRONT = 12.0f;

static const Matrix4 PLAYER_MODEL_SCALE = Matrix4::Scale(Vector3(0.2f));

//�_�b�V�����̃u�[�X�^�[�̉��̃X�P�[��
static const Matrix4 DASH_BOOST_SCALE = Matrix4::Scale(Vector3(0.4f));
//���̈ʒu
static const Vector3 BOOST_POS = Vector3(0.0f, 1.2f, -28.0f);
static const Vector3 DASH_BOOST_POS = Vector3(0.0f, 1.2f, -42.0f);

//�㉟���Ԃ��{��
static const float PUSH_BACK_MUL = 4.5f;
//�㉺�����Ԃ��{��
static const float PUSH_UP_DOWN_MUL = 5.0f;

//�~�T�C�����ˉ\����
static const float MISSILE_INTERVAL_TIME = 3.0f;

AirPlayer::AirPlayer(IWorld* world, const Vector3& position) :
	Actor(world, "Player", position, BoundingSphere(8.0f),HP_MAX),
	timer(0.0f),
	bulletTimer(0.0f),
	bulletChange(-1),
	angleX(0.0f),
	angleY(0.0f),
	angleZ(0.0f),
	addAngleZ(0.0f),
	boosterAngle(0.0f),
	boosterScale(PLAYER_MODEL_SCALE),
	boosterPos(BOOST_POS),
	finalVelocity(Vector3::Zero),
	isDash(false),
	dashTimer(0.0f),
	dashLineTimer(0.0f),
	missileTimer(0.0f)
{
	
}

void AirPlayer::OnUpdate(float deltaTime)
{
	timer += deltaTime;

	ShotBullet(deltaTime);
	Move(deltaTime);
}

void AirPlayer::OnDraw() const
{
	//���f���̕`��
	glPushMatrix();
	glMultMatrixf(PLAYER_MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::PLAYER_MODEL);
	glPopMatrix();

	//�u�[�X�^�[�̉��̕`��
	glPushMatrix();
	Matrix4 mat =
		boosterScale *
		Matrix4::RotateZ(boosterAngle) *Matrix4::Translate(boosterPos) *
		GetPose();
	glMultMatrixf(mat.ToGSmatrix4());
	gsDrawMesh(MODEL_ID::PLAYER_BOOSTER_MODEL);
	glPopMatrix();

	//�~�T�C���Q�[�W�̕`��
	GSrect missileFrameRect(0.0f, 0.0f, 200.0f, 50.0f);
	GSrect missileRect(0.0f, 0.0f, 180 * missileTimer / MISSILE_INTERVAL_TIME, 50.0f);
	GSvector2 missilescale = GSvector2(0.8f, 0.8f);
	GSvector2 missilepos = GSvector2(214, 570);
	gsDrawSprite2D(TEXTURE_ID::MISSILE_GAUGE_FRAME_TEX, &missilepos, &missileFrameRect, NULL, NULL, &missilescale, 0);
	gsDrawSprite2D(TEXTURE_ID::MISSILE_GAUGE_TEX, &(missilepos + GSvector2(10, 0)), &missileRect, NULL, NULL, &missilescale, 0);
	if (missileTimer < MISSILE_INTERVAL_TIME)
	{
		GScolor col(1.0f,1.0f,1.0f,0.8f);
		gsDrawSprite2D(TEXTURE_ID::MISSILE_GAUGE_BLACK_TEX, &missilepos, &missileFrameRect, NULL, &col, &missilescale, 0);
	}

	//�@�̃��S�̕`��
	gsDrawSprite2D(TEXTURE_ID::LOGO_TEX, &GSvector2(0,600-128), &GSrect(0,0,256,256), NULL, NULL, &GSvector2(0.5f,0.5f), 0);
	//HP�o�[�̕`��
	GSrect frameRect(0.0f, 0.0f, 96.0f, 32.0f);
	GSrect gaugeRect(0.0f, 0.0f, 96.0f * hp / HP_MAX, 32.0f);
	GSvector2 pos(60, 556);
	GSvector2 scale(2, 2);
	gsDrawSprite2D(TEXTURE_ID::HP_GAUGE_FRAME_TEX, &pos, &frameRect, NULL, NULL, &scale, 0);
	gsDrawSprite2D(TEXTURE_ID::HP_GAUGE_TEX, &pos, &gaugeRect, NULL, NULL, &scale, 0);



//
//	//�f�o�b�O�����`��
//	gsTextPos(0, 0);
//	gsDrawText("��]Z : %d", angleZ);
//	gsTextPos(0, 16);
//	gsDrawText("�f�o�b�O : %f", timer);
}

void AirPlayer::OnCollide(Actor& other,const HitInfo& info)
{
	//�ȉ��̂��̂Ƃ̐ڐG���͉����Ԃ�
	if (other.GetName() == "EnemyAirShip" || other.GetName() == "BarrierSphere" )
	{
		//���Α��։����Ԃ�
		Vector3 v = position - info.point;
		v.Normalize();
		
		if (!isDash)
			position += v * PUSH_BACK_MUL;
		else
			position += v * PUSH_BACK_MUL * (DASH_SPEED_Z / MOVE_SPEED_Z);

	}
	//�ȉ��̂��̂ƏՓ˂����Ƃ��͉������Ȃ�
	else if(other.GetName() == "BarrierGenerator" || other.GetName() == "RedFighter" || other.GetName() == "AirShipContainer")
	{

	}
	//����ȊO(�G�A�G�e)
	else
	{
		//�{�X��|�����疳�G
		if (world->FindActor("EnemyAirShip")->GetHP() <= 0) return;

		gsPlaySE(SOUND_ID::DAMAGE_SE);
		hp--;
		//������
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position + Vector3(0.0f, 2.0f, 0.0f), Vector3::Zero, 5));
		//��
		world->AddActor(ActorGroup::Effect, std::make_shared<HitSmoke>(world, position + Vector3(0.0f, 2.0f, 0.0f)));
		if (hp <= 0)
		{
			//�����̃G�t�F�N�g�𐶐����Ď��S
			world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position + Vector3(0.0f, 2.0f, 0.0f), Vector3::Zero));
			Dead();
			gsPlaySE(SOUND_ID::BOMB_BIG_SE);
			//�a�f�l����~
			gsStopMusic();
		}
	}


}

void AirPlayer::ShotBullet(float deltaTime)
{	
	//�}�V���K��
	bulletTimer += deltaTime;
	if (bulletTimer > 0.05f)
	{
		bulletTimer = 0.0f;
		//���ˈʒu�̌v�Z
		Vector3 pos =
			position +
			GetRotate().GetFront() * MACHINEGUN_SHOT_FRONT +
			GetRotate().GetLeft() * MACHINEGUN_SHOT_WIDTH * bulletChange;
		world->AddActor(ActorGroup::PlayerBullet, std::make_shared<PlayerMachineGun>(world, pos,rotate, rotate.GetFront()));
		//���ˈʒu�̍��E�؂�ւ�
		bulletChange *= -1;
	}

	//�~�T�C��
	missileTimer += deltaTime;
	missileTimer = Math::Clamp(missileTimer, 0.0f, MISSILE_INTERVAL_TIME);
	if (missileTimer >= MISSILE_INTERVAL_TIME && gsGetKeyTrigger(GKEY_SPACE) == GS_TRUE)
	{
		gsPlaySE(SOUND_ID::MISSILE_SE);
		missileTimer = 0.0f;
		for (int i = 0; i < 4; i++)
		{
			//���ˈʒu�̌v�Z
			Vector3 pos =
				position +
				GetRotate().GetFront() * MISSILE_SHOT_FRONT +
				GetRotate().GetLeft() * (MISSILE_SHOT_WIDTH_INIT + MISSILE_SHOT_WIDTH_INC * i);

			//�΂߂ɔ��
			float angle = -9.0f + i * 6.0f;
			Matrix4 dir = GetRotate() * Quaternion::RotateAxis(GetRotate().GetUp(), angle);
			world->AddActor(ActorGroup::PlayerBullet, std::make_shared<PlayerMissile>(world, pos, GetRotate(), dir.GetFront()));
		}
	}
}

void AirPlayer::Move(float deltaTime)
{
	//�㉺������
	if (gsGetKeyState(GKEY_UP) == GS_TRUE || gsGetKeyState(GKEY_W) == GS_TRUE) {
		angleX -= ANGLE_SPEED_X * deltaTime;
	}
	if (gsGetKeyState(GKEY_DOWN) == GS_TRUE || gsGetKeyState(GKEY_S) == GS_TRUE) {
		angleX += ANGLE_SPEED_X * deltaTime;
	}
	//�p�x����
	angleX = Math::Clamp(angleX, -80.0f, 80.0f);

	//���E���͒��͓��͕����������o�������[��
	if (gsGetKeyState(GKEY_LEFT) == GS_TRUE || gsGetKeyState(GKEY_A) == GS_TRUE) 
	{
		angleY += ANGLE_SPEED_Y * deltaTime;
		if (addAngleZ > 0)addAngleZ /= 2.0f;
			addAngleZ -= ANGLE_SPEED_Z * deltaTime;
		angleZ += (int)addAngleZ;
	}
	else if (gsGetKeyState(GKEY_RIGHT) == GS_TRUE || gsGetKeyState(GKEY_D) == GS_TRUE)
	{
		angleY -= ANGLE_SPEED_Y * deltaTime;
		if (addAngleZ < 0)addAngleZ /= 2.0f;
			addAngleZ += ANGLE_SPEED_Z * deltaTime;
		angleZ += (int)addAngleZ;
	}
	//���E�����͂̂Ƃ�
	else
	{
		//���[�����Ă����ԂȂ����������
		int abs = Math::Abs(angleZ);
		if (abs >= 5)
		{
			angleZ *= 0.95f;
		}
		addAngleZ *= 0.95f;
	}
	//�p�x����
	addAngleZ = Math::Clamp(addAngleZ, -10.0f, 10.0f);
	//360�x����������
	angleZ %= 360;

	//�_�b�V���{�^���������Ă���Ȃ�X�s�[�h�A�b�v
	isDash = gsGetKeyState(GKEY_LSHIFT);
	if (isDash)
	{
		finalVelocity = rotate.GetFront() * DASH_SPEED_Z * deltaTime;
		//�_�b�V���̔��������o��
		dashLineTimer += deltaTime;
		if (dashLineTimer > 0.05f)
		{
			dashLineTimer = 0.0f;
			world->AddActor(ActorGroup::Effect, std::make_shared<DashLine>(world));
		}

		dashTimer += deltaTime;
	}
	else
	{
		finalVelocity = rotate.GetFront() * MOVE_SPEED_Z * deltaTime;
		dashTimer -= deltaTime;
	}

	dashTimer = Math::Clamp(dashTimer, 0.0f, 1.0f);
	//�u�[�X�^�[�̉��̃X�P�[����ύX
	boosterScale = Matrix4::Lerp(PLAYER_MODEL_SCALE, DASH_BOOST_SCALE, dashTimer);
	//�u�[�X�^�[�̉��̈ʒu�ύX
	boosterPos = Vector3::Lerp(BOOST_POS, DASH_BOOST_POS, dashTimer);
	//�u�[�X�^�[�̉��̉�]
	boosterAngle += 2000.0f * deltaTime;

	//��]
	rotate = Matrix4::RotateZ(angleZ) * Matrix4::RotateX(angleX) * Matrix4::RotateY(angleY);
	//�ړ�
	position += finalVelocity;
}