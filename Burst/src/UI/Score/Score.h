#pragma once

#include <gslib.h>
#include "../../Math/Vector2.h"

//�X�R�A�N���X
class Score {
public:
	//�R���X�g���N�^
	explicit Score(int score = 0);
	//�X�R�A�̉��Z
	void AddScore(int add);
	//�X�R�A�̕`��
	void Draw() const;
	//�X�R�A�̎擾
	int GetScore() const;
	//�K���v���[�g�̈ړ�
	void SetPlateBasePos(const Vector2& pos);
	//�K���v���[�g�̊�������W�擾
	GSvector2 GetInitPlateBasePos();

private:
	//�X�R�A
	int score;
	//�K���v���[�g�̊���W
	GSvector2 plateBasePos;
};