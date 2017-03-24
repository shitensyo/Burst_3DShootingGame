#include "Effect.h"

#pragma comment( lib, "cg.lib" )
#pragma comment( lib, "cgGL.lib" )

// �R���X�g���N�^
Effect::Effect(const char* fileName) :
	mContext(0),
	mEffect(0),
	mTechnique(0),
	mPass(0) {
	// �R���e�L�X�g���쐬
	mContext = cgCreateContext();
	// �R���e�L�X�g���n�������f�k�ɐݒ�
	cgGLRegisterStates(mContext);
	// �G�t�F�N�g��ǂݍ���
	mEffect = cgCreateEffectFromFile(mContext, fileName, NULL);
	if (mEffect == 0) {
		// �G���[���b�Z�[�W���o�͂���
		const char *listing = cgGetLastListing(mContext);
		if (listing != 0) {
			///�u�b�{�{�̃A�E�g�v�b�g�E�B���h�E�ɃG���[���b�Z�[�W���o��
			//OutputDebugString(listing);
		}
	}
}

// �f�X�g���N�^
Effect::~Effect() {
	// �G�t�F�N�g���폜
	if (cgIsEffect(mEffect) == CG_TRUE) {
		cgDestroyEffect(mEffect);
	}
	// �R���e�e�L�X�g���폜
	if (mContext != 0) {
		cgDestroyContext(mContext);
	}
}

// �e�N�j�b�N��ݒ�
void Effect::setTechnique(const char* techniqueName) {
	// �e�N�j�b�N���擾����
	mTechnique = cgGetNamedTechnique(mEffect, techniqueName);
}

// ���݂̃p�X���J�n����
void Effect::begin() {
	// ���݂̃e�N�j�b�N���ݒ肳��Ă��邩�H
	if (cgIsTechnique(mTechnique) == CG_FALSE) {
		// �p�X�𖳌��ɂ���
		mPass = 0;
		return;
	}
	// �ŏ��̃p�X���擾����
	mPass = cgGetFirstPass(mTechnique);
	if (cgIsPass(mPass) == CG_TRUE) {
		// �ŏ��̃p�X��ݒ肷��
		cgSetPassState(mPass);
	}
}

// �p�X���w�肷��
void Effect::pass(int passNo) {
	// �ŏ��̃p�X���擾����
	mPass = cgGetFirstPass(mTechnique);
	// �w��̃p�X������
	for (int n = 0; n < passNo; n++) {
		mPass = cgGetNextPass(mPass);
	}
	// �p�X���L���ł���ΐݒ肷��
	if (cgIsPass(mPass) == CG_TRUE) {
		cgSetPassState(mPass);
	}
}

// ���݂̃e�N�j�b�N�̃p�X�����擾
int Effect::getNumPass() {
	// ���݂̃e�N�j�b�N���ݒ肳��Ă��邩�H
	if (cgIsTechnique(mTechnique) == CG_FALSE) {
		// �p�X�͑��݂��Ȃ�
		return 0;
	}
	// �p�X�̑������`�F�b�N����
	int numPass = 0;
	for (CGpass pass = cgGetFirstPass(mTechnique);
		cgIsPass(pass) == CG_TRUE;
		pass = cgGetNextPass(pass)) {
		numPass++;
	}
	return numPass;
}

// ���݂̃p�X���I������
void Effect::end() {
	// ���݂̃p�X�����Z�b�g����
	if (cgIsPass(mPass) == CG_TRUE) {
		cgResetPassState(mPass);
	}
	// �p�X�𖳌��ɂ���
	mPass = 0;
}

// float�̃p�����[�^��ݒ�
void Effect::setParameter(const char* paramName, float v) {
	// ���O����p�����[�^���擾
	CGparameter param = cgGetNamedEffectParameter(mEffect, paramName);
	if (cgIsParameter(param) == CG_TRUE) {
		// float�̃p�����[�^��ݒ�
		cgSetParameter1fv(param, &v);
	}
}

// Vector2�̃p�����[�^��ݒ�
void Effect::setParameter(const char* paramName, const GSvector2& v2) {
	CGparameter param = cgGetNamedEffectParameter(mEffect, paramName);
	if (cgIsParameter(param) == CG_TRUE) {
		cgSetParameter2fv(param, (const float*)&v2);
	}
}

// Vector3�̃p�����[�^��ݒ�
void Effect::setParameter(const char* paramName, const GSvector3& v3) {
	CGparameter param = cgGetNamedEffectParameter(mEffect, paramName);
	if (cgIsParameter(param) == CG_TRUE) {
		cgSetParameter3fv(param, (const float*)&v3);
	}
}

// Color4�̃p�����[�^��ݒ�
void Effect::setParameter(const char* paramName, const GScolor4& c4) {
	CGparameter param = cgGetNamedEffectParameter(mEffect, paramName);
	if (cgIsParameter(param) == CG_TRUE) {
		cgSetParameter4fv(param, (const float*)&c4);
	}
}

// Matrix4�̃p�����[�^��ݒ�
void Effect::setParameter(const char* paramName, const GSmatrix4& m4) {
	CGparameter param = cgGetNamedEffectParameter(mEffect, paramName);
	if (cgIsParameter(param) == CG_TRUE) {
		cgSetMatrixParameterfr(param, (const float*)&m4);
	}
}

// �e�N�X�`���̃p�����[�^��ݒ�
void Effect::setTexture(const char* textureName, GLuint texture) {
	CGparameter param = cgGetNamedEffectParameter(mEffect, textureName);
	if (cgIsParameter(param) == CG_TRUE) {
		cgGLSetupSampler(param, texture);
	}
}

