#pragma once

#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <gslib.h>

// �G�t�F�N�g�N���X
class Effect {
public:
	// �R���X�g���N�^
	Effect(const char* filename);
	// �f�X�g���N�^
	~Effect();
	// ���݂̃p�X���J�n����
	void begin();
	// �p�X���w�肷��
	void pass(int passNo);
	// ���݂̃p�X���I������
	void end();
	// ���݂̃e�N�j�b�N�̃p�X�����擾
	int getNumPass();
	// �e�N�j�b�N��ݒ�
	void setTechnique(const char* techniqueName);
	// float�̃p�����[�^��ݒ�
	void setParameter(const char* paramName, float v);
	// Vector2�̃p�����[�^��ݒ�
	void setParameter(const char* paramName, const GSvector2& v2);
	// Vector3�̃p�����[�^��ݒ�
	void setParameter(const char* paramName, const GSvector3& v3);
	// Color4�̃p�����[�^��ݒ�
	void setParameter(const char* paramName, const GScolor4& c4);
	// Matrix4�̃p�����[�^��ݒ�
	void setParameter(const char* paramName, const GSmatrix4& m4);
	// �e�N�X�`���̃p�����[�^��ݒ�
	void setTexture(const char* textureName, GLuint texture);
private:
	// �b�f�R���e�L�X�g
	CGcontext mContext;
	// �G�t�F�N�g
	CGeffect mEffect;
	// �e�N�j�b�N
	CGtechnique mTechnique;
	// �p�X
	CGpass mPass;
};
