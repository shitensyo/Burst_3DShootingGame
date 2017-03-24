#include "AirShipMachinegunShooter.h"
#include "../AssetID.h"
#include "../../Math/Math.h"
#include "../Base/ActorGroup.h"
#include "../EnemyBullet/EnemyMachineGun.h"

//���f���ǉ���Z�X�P�[��
static const float MODEL_MUL_SCALE = 3.0f;
//���f����{�X�P�[��
static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(15.0f * MODEL_MUL_SCALE));
//���ˊԊu
static const float BULLET_INTERVAL = 0.15f;
//�e����
static const float BULLET_SPEED = 1200.0f;
//�e����
static const float BULLET_LIFE_TIME = 1.6f;
//��]���E��
static const float ANGLE_Y_LIMIT = 100.0f;
//���˕����A��]�ʂ�ς���Ԋu
static const float ANGLE_CHANGE_INTERVAL = 5.0f;

//���ʂƔ��肷��Ƃ��̓��ϒl�@����𒴂����琳�ʂɂ���Ƃ���
static const float DOT_LIMIT = 0.2f;

AirShipMachinegunShooter::AirShipMachinegunShooter(IWorld * world_, const Vector3 & position_, const Matrix4& initRotate_, bool isShot_) :
	Actor(world_, "AirShipMachinegunShooter", position_, BoundingSphere()),
	timer(gsRandf(0.0f, 2.0f)),
	initRotate(initRotate_),
	targetVec(initRotate_.GetFront()),
	angleY(0.0f),
	rotateTimer(0.0f),
	isShot(isShot_)
{
	rotate = initRotate;
}

void AirShipMachinegunShooter::OnUpdate(float deltaTime)
{
	if (!isShot) return;

	//�v���C���[�ƑO�㔻��
	ActorPtr player = world->GetPlayer();
	if (player == nullptr) return;

	Vector3 toPlayer = player->GetPosition() - position;
	toPlayer.Normalize();
	float dot = Vector3::Dot(initRotate.GetFront(), toPlayer);
	//�v���C���[�����ʂɂ���Ȃ�
	if (dot > DOT_LIMIT)
	{
		targetVec = toPlayer;
		Rotation();
	}
	else
	{
		//���˕�����ς���
		rotateTimer += deltaTime;
		if (rotateTimer > ANGLE_CHANGE_INTERVAL)
		{
			rotateTimer = 0.0f;
			//�K���Ɍ��߂��x�N�g���̂ق�������
			targetVec = initRotate.GetLeft() * gsRandf(-1.0f, 1.0f) + initRotate.GetFront() * gsRandf(1.0f, 1.5f) + initRotate.GetUp() * gsRandf(0.0f, 1.0f);
			targetVec.Normalize();
			Rotation();
		}
	}
	
	//�U��
	timer += deltaTime;
	if (timer > BULLET_INTERVAL)
	{
		timer = 0.0f;
		//���ˈʒu�̌v�Z
		Vector3 shotPos = rotate.GetUp() * 10.0f + rotate.GetFront() * 40.0f;
		//���˕����̌v�Z�i�����_���ő����΂������j
		Vector3 toTarget = targetVec;
		toTarget.x += gsRandf(-0.06f, 0.06f);
		toTarget.y += gsRandf(-0.06f, 0.06f);
		toTarget.z += gsRandf(-0.06f, 0.06f);
		//����
		world->AddActor(ActorGroup::EnemyBullet, std::make_shared<EnemyMachineGun>(world, position + shotPos, toTarget * BULLET_SPEED, BULLET_LIFE_TIME));
	}
}

void AirShipMachinegunShooter::OnDraw() const
{
	//���f���̕`��
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::BOSS_AIR_SHIP_MACHINEGUN_SHOOTER);
	glPopMatrix();
}

void AirShipMachinegunShooter::OnCollide(Actor& other,const HitInfo& info)
{
}


void AirShipMachinegunShooter::Rotation()
{
	//�C�g�������ׂ��p�x���w�y���ʏ�Ōv�Z
	Vector3 f = initRotate.GetFront();
	f = Vector3(f.x, 0.0f, f.z);
	f.Normalize();
	Vector3 to = Vector3(targetVec.x, 0.0f, targetVec.z);
	to.Normalize();
	angleY = Vector3::Inner(f, to);

	//���E����
	Vector3 cross = Vector3::Cross(initRotate.GetFront(), to);
	if (cross.y < 0)
		angleY = -angleY;

	//�t���ɕt���Ă���C��͌������]
	if (initRotate.GetUp().y < 0)
		angleY = -angleY;

	//��]
	Matrix4 rot = Quaternion::RotateAxis(rotate.GetUp(), angleY);
	rotate = initRotate * rot;

}