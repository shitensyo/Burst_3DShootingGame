#include "AirShipMissileShooter.h"
#include "../AssetID.h"
#include "../../Math/Math.h"
#include "../Base/ActorGroup.h"
#include "../EnemyBullet/EnemyMissile.h"
#include "../Effect/Explosion.h"

//���f���ǉ���Z�X�P�[��
static const float MODEL_MUL_SCALE = 3.0f;
//���f����{�X�P�[��
static const Matrix4 MODEL_SCALE = Matrix4::Scale(Vector3(15.0f * MODEL_MUL_SCALE));
//���ˊԊu
static const float BULLET_INTERVAL = 3.0f;
//�e����
static const float BULLET_SPEED = 250.0f;
//��]���E��
static const float ANGLE_Y_LIMIT = 100.0f;

//�~�T�C���X�P�[��
static const float MISSILE_SCALE = 4.0f;

AirShipMissileShooter::AirShipMissileShooter(IWorld * world_, const Vector3 & position_, const Matrix4& initRotate_, bool isShot_) :
	Actor(world_, "AirShipMissileShooter", position_, BoundingSphere()),
	timer(gsRandf(0.0f, 2.0f)),
	initRotate(initRotate_),
	angleY(0.0f),
	prevRotate(initRotate_),
	currentRotate(initRotate_),
	isShot(isShot_)
{
	rotate = initRotate;
	player = world->GetPlayer();
}

void AirShipMissileShooter::OnUpdate(float deltaTime)
{
	if (!isShot) return;

	player = world->GetPlayer();
	//�v���C���[�����Ȃ��ꍇ�͎��s���Ȃ�
	if (player == nullptr) return;

	//�v���C���[�������ꍇ�͎��s���Ȃ�
	if (Vector3::Length(player->GetPosition() - position) > 8000.0f) return;


	//�v���C���[�̂ق�������
	Vector3 toPlayer = player->GetPosition() - position;
	toPlayer.Normalize();

	//�v���C���[�܂ł̊p�x���w�y���ʏ�Ōv�Z
	Vector3 f = initRotate.GetFront();
	f = Vector3(f.x, 0.0f, f.z);
	f.Normalize();
	Vector3 toP = Vector3(toPlayer.x, 0.0f, toPlayer.z);
	toP.Normalize();
	angleY = Vector3::Inner(f, toP);
	angleY = Math::Clamp(angleY, -ANGLE_Y_LIMIT, ANGLE_Y_LIMIT);

	//���E����
	Vector3 cross = Vector3::Cross(initRotate.GetFront(), toPlayer);
	if (cross.y < 0)
		angleY = -angleY;

	//��]
	prevRotate = currentRotate;
	currentRotate = Quaternion::RotateAxis(rotate.GetUp(), angleY);
	//�⊮���ĂȂ߂炩��
	currentRotate = Matrix4::Slerp(prevRotate, currentRotate, 0.1f);
	rotate = initRotate * currentRotate;

	//�U��
	timer += deltaTime;
	if (timer > BULLET_INTERVAL)
	{
		timer = gsRandf(0.0f, 5.5f);
		//��]�ʂ����E�Ȃ甭�˂��Ȃ�
		if (Math::Abs(angleY) >= ANGLE_Y_LIMIT) return;
		//���ˈʒu�̌v�Z
		int x = gsRand(-1, 1);
		Vector3 shotPos = rotate.GetLeft() * 30.0f * x + rotate.GetUp() * 30.0f + rotate.GetFront() * 200.0f;
		//���˕����̌v�Z�i�����_���ő����΂������j
		Vector3 toTarget = toPlayer;
		toTarget.x += gsRandf(-0.3f, 0.3f);
		toTarget.y += gsRandf(-0.3f, 0.3f);
		toTarget.z += gsRandf(-0.1f, 0.1f);
		//����
		world->AddActor(ActorGroup::EnemyBullet, std::make_shared<EnemyMissile>(world, position + shotPos, toTarget * BULLET_SPEED, MISSILE_SCALE));
		//�G�t�F�N�g
		world->AddActor(ActorGroup::Effect, std::make_shared<Explosion>(world, position + shotPos, Vector3::Zero,2));
	}
}

void AirShipMissileShooter::OnDraw() const
{	
	//���f���̕`��
	glPushMatrix();
	glMultMatrixf(MODEL_SCALE.ToGSmatrix4() * GetPose().ToGSmatrix4());
	gsDrawMesh(MODEL_ID::BOSS_AIR_SHIP_MISSILE_SHOOTER);
	glPopMatrix();
}

void AirShipMissileShooter::OnCollide(Actor& other,const HitInfo& info)
{
}
