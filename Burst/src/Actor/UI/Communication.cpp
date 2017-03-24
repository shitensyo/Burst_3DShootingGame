#include "Communication.h"
#include "../AssetID.h"
#include "../../World/IWorld.h"
#include "../../../EventMessage.h"

//�������ăe�L�X�g���o��܂ł̑҂�����
static const float WAIT_TIME = 0.4f;

Communication::Communication(IWorld * world, ActorPtr boss_, const Vector2 & position_, const Phase &phase_) :
	Actor(world, "Communication", Vector3::Zero, BoundingSphere()),
	timer(0.0f),
	textWaitTimer(0.0f),
	textNum(-1),
	isTextDraw(false),
	phase(phase_),
	initPosition(position_),
	textPosition(10, 2)
{
	texts.push_back("����̃~�b�V�����́A�o���A�Ɏ��ꂽ�G�󒆐�͂̌��j���B");
	texts.push_back("�܂��͋@�̂̑��c�Ɋ���Ă��炤�B��J���ėp�ӂ����񂾁A��؂Ɉ����B");
	texts.push_back("�����L�[�������͂v�`�r�c�L�[�ŁA���͂��������Ɍ������ċ@�񂪓����B");
	texts.push_back("�r�g�h�e�s�L�[�ō����ړ����ł���B�}�ڋ߁A���E�ɗ��p����B");
	texts.push_back("�r�o�`�b�d�L�[�Ńz�[�~���O�~�T�C�����łĂ�B�U���𓖂ĂÂ炢���^�̓G�@�͂���ŗ��Ƃ��B");
	texts.push_back("����ł͍��Ɉڂ�B");
	texts.push_back("�܂��͐�̗͂��ׂɕ�����ł���A�o���A�̔������u�̔j�󂾁B��q�̐퓬�@�ɒ��ӂ𕥂��B");
	texts.push_back("�������B���̒��q���B");
	texts.push_back("���̂܂ܐ�͂ɍU�����s���B��ʏ㕔�̃Q�[�W�͐�͂̑ϋv�l���B");
	texts.push_back("�E�E�E�����Ԃ�ƍd����͂��ȁB���`�������Ȃ��B");
	texts.push_back("���������F�R�̃X�p�C����̏�񂪓������B��͉����̃R���e�i��_���B");
	texts.push_back("��͉����̃R���e�i�͉Ζ�ɂƂ��Ďg���Ă���悤���B�U�������Đ�͂Ƀ_���[�W��^����B");
	texts.push_back("��o�����B���̂܂܍U���𑱍s�B��͂�@�����Ƃ��B");

	texts.push_back("���I���B�悭������B");
	texts.push_back("�ʐM���r�₦���E�E�E�I�I�I�@��������I�@��������I�I�E�E�E");
}

void Communication::OnMessage(EventMessage event, void *)
{

}

void Communication::OnUpdate(float deltaTime)
{
	if (phase != Phase::DEAD && world->GetPlayer() == nullptr)
	{
		phase = Phase::DEAD;
		timer = 0.0f;
		textWaitTimer = 0.0f;
	}

	switch (phase)
	{
	case Phase::START:StartPhase(deltaTime);
		break;
	case Phase::TUTORIAL:TutorialPhase(deltaTime);
		break;
	case Phase::BARRIER:BarrierPhase(deltaTime);
		break;
	case Phase::CONTAINER:ContainerPhase(deltaTime);
		break;
	case Phase::SHIP:ShipPhase(deltaTime);
		break;
	case Phase::DEAD:DeadPhase(deltaTime);
		break;
	case Phase::CLEAR:ClearPhase(deltaTime);
		break;
	default:
		break;
	}
}

void Communication::OnDraw() const
{
	GSrect rect(0.0f, 0.0f, 800.0f, 36.0f);
	GSvector2 scale(1.0f, 0.8f);
	GScolor color(1.0f,1.0f,1.0f,0.6f);
	gsDrawSprite2D(TEXTURE_ID::BLACK_BAR_TEX, &initPosition.ToGSvector2(), &rect, NULL, &color, &scale, 0);

	if (isTextDraw)
	{
		Vector2 pos = initPosition + textPosition;
		gsTextPos(pos.x, pos.y);
		gsDrawText("");	//����gsTextPos�ɑΉ����Ă��Ȃ����߁@���������Ŗ�����蕶���̈ʒu��ς���
		gsTextDraw(GS_FONT_NORMAL, 26, "���C���I", texts.at(textNum).c_str());
	}
}

void Communication::StartPhase(float deltaTime)
{
	isTextDraw = false;
	timer += deltaTime;
	if (timer > 1.0f)
	{
		timer = 0.0f;
		phase = Phase::TUTORIAL;
	}
}

void Communication::TutorialPhase(float deltaTime)
{
	//�e�L�X�g�i�s
	timer += deltaTime;
	
	//�ŏ���������
	if (textNum == -1)
		timer += deltaTime * 3.0f;
	if (timer < 6.0f) return;

	if (textWaitTimer <= 0.0f)
	{
		isTextDraw = false;
		gsPlaySE(SOUND_ID::RECEPTION_SE);
	}
	textWaitTimer += deltaTime;
	if (textWaitTimer > WAIT_TIME)
	{
		isTextDraw = true;
		timer = 0.0f;
		textWaitTimer = 0.0f;
		textNum++;

		//�Ō�܂ŗ�����i�K�ύX
		if (textNum >= 6)
		{
			phase = Phase::BARRIER;
			world->SendMessageW(EventMessage::BarrierPhase);
		}
	}
}

void Communication::BarrierPhase(float deltaTime)
{
	//�o���A�������u���S�ł����玟�֐i�ށB
	if (world->FindActor("BarrierGenerator") == nullptr)
	{
		if (textWaitTimer <= 0.0f)
		{
			isTextDraw = false;
			gsPlaySE(SOUND_ID::RECEPTION_SE);
		}
		textWaitTimer += deltaTime;
		if (textWaitTimer > WAIT_TIME)
		{
			isTextDraw = true;
			textWaitTimer = 0.0f;
			textNum++;
			phase = Phase::CONTAINER;
		}
	}
}

void Communication::ContainerPhase(float deltaTime)
{	
	//�R���e�i��j�󂵂��玟�֐i�ށB
	if (world->FindActor("AirShipContainer") == nullptr)
	{
		isTextDraw = false;
		timer = 0.0f;
		textWaitTimer = 0.0f;
		phase = Phase::SHIP;
	}

	//�Ō�܂Ői��ł���Ȃ�i�s���Ȃ�
	if (textNum >= 11) return;

	//�e�L�X�g�i�s
	//���������������
	if (textNum == 8)
		timer += deltaTime / 4;
	else
		timer += deltaTime;

	if (timer < 6.0f) return;

	if (textWaitTimer <= 0.0f)
	{
		isTextDraw = false;
		gsPlaySE(SOUND_ID::RECEPTION_SE);
	}
	textWaitTimer += deltaTime;
	if (textWaitTimer > WAIT_TIME)
	{
		isTextDraw = true;
		timer = 0.0f;
		textWaitTimer = 0.0f;
		textNum++;

		//�����܂Ői�񂾂�R���e�i�ɃJ�[�\����\������
		if (textNum >= 10)
		{
			world->SendMessageW(EventMessage::ContainerPhase);
		}
	}
}

void Communication::ShipPhase(float deltaTime)
{
	if (textNum == 12) return;

	if (textWaitTimer <= 0.0f)
	{
		isTextDraw = false;
		gsPlaySE(SOUND_ID::RECEPTION_SE);
	}
	textWaitTimer += deltaTime;
	if (textWaitTimer > WAIT_TIME)
	{
		isTextDraw = true;
		textWaitTimer = 0.0f;
		textNum = 12;
	}
}

void Communication::DeadPhase(float deltaTime)
{
	if (textNum == 14) return;

	timer += deltaTime;
	if (timer < 3.0f) return;
	if (textWaitTimer <= 0.0f)
	{
		isTextDraw = false;
		gsPlaySE(SOUND_ID::RECEPTION_SE);
	}
	textWaitTimer += deltaTime;
	if (textWaitTimer > WAIT_TIME)
	{
		isTextDraw = true;
		textWaitTimer = 0.0f;
		textNum = 14;
	}
}

void Communication::ClearPhase(float deltaTime)
{
	if (textNum == 13) return;

	timer += deltaTime;
	if (timer < 3.0f) return;
	if (textWaitTimer <= 0.0f)
	{
		isTextDraw = false;
		gsPlaySE(SOUND_ID::RECEPTION_SE);
	}
	textWaitTimer += deltaTime;
	if (textWaitTimer > WAIT_TIME)
	{
		isTextDraw = true;
		textWaitTimer = 0.0f;
		textNum = 13;
	}
}
