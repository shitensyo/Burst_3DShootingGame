#include "Effect.h"

#pragma comment( lib, "cg.lib" )
#pragma comment( lib, "cgGL.lib" )

// コンストラクタ
Effect::Effect(const char* fileName) :
	mContext(0),
	mEffect(0),
	mTechnique(0),
	mPass(0) {
	// コンテキストを作成
	mContext = cgCreateContext();
	// コンテキストをＯｐｅｎＧＬに設定
	cgGLRegisterStates(mContext);
	// エフェクトを読み込む
	mEffect = cgCreateEffectFromFile(mContext, fileName, NULL);
	if (mEffect == 0) {
		// エラーメッセージを出力する
		const char *listing = cgGetLastListing(mContext);
		if (listing != 0) {
			///ＶＣ＋＋のアウトプットウィンドウにエラーメッセージを出力
			//OutputDebugString(listing);
		}
	}
}

// デストラクタ
Effect::~Effect() {
	// エフェクトを削除
	if (cgIsEffect(mEffect) == CG_TRUE) {
		cgDestroyEffect(mEffect);
	}
	// コンテテキストを削除
	if (mContext != 0) {
		cgDestroyContext(mContext);
	}
}

// テクニックを設定
void Effect::setTechnique(const char* techniqueName) {
	// テクニックを取得する
	mTechnique = cgGetNamedTechnique(mEffect, techniqueName);
}

// 現在のパスを開始する
void Effect::begin() {
	// 現在のテクニックが設定されているか？
	if (cgIsTechnique(mTechnique) == CG_FALSE) {
		// パスを無効にする
		mPass = 0;
		return;
	}
	// 最初のパスを取得する
	mPass = cgGetFirstPass(mTechnique);
	if (cgIsPass(mPass) == CG_TRUE) {
		// 最初のパスを設定する
		cgSetPassState(mPass);
	}
}

// パスを指定する
void Effect::pass(int passNo) {
	// 最初のパスを取得する
	mPass = cgGetFirstPass(mTechnique);
	// 指定のパスを検索
	for (int n = 0; n < passNo; n++) {
		mPass = cgGetNextPass(mPass);
	}
	// パスが有効であれば設定する
	if (cgIsPass(mPass) == CG_TRUE) {
		cgSetPassState(mPass);
	}
}

// 現在のテクニックのパス数を取得
int Effect::getNumPass() {
	// 現在のテクニックが設定されているか？
	if (cgIsTechnique(mTechnique) == CG_FALSE) {
		// パスは存在しない
		return 0;
	}
	// パスの総数をチェックする
	int numPass = 0;
	for (CGpass pass = cgGetFirstPass(mTechnique);
		cgIsPass(pass) == CG_TRUE;
		pass = cgGetNextPass(pass)) {
		numPass++;
	}
	return numPass;
}

// 現在のパスを終了する
void Effect::end() {
	// 現在のパスをリセットする
	if (cgIsPass(mPass) == CG_TRUE) {
		cgResetPassState(mPass);
	}
	// パスを無効にする
	mPass = 0;
}

// floatのパラメータを設定
void Effect::setParameter(const char* paramName, float v) {
	// 名前からパラメータを取得
	CGparameter param = cgGetNamedEffectParameter(mEffect, paramName);
	if (cgIsParameter(param) == CG_TRUE) {
		// floatのパラメータを設定
		cgSetParameter1fv(param, &v);
	}
}

// Vector2のパラメータを設定
void Effect::setParameter(const char* paramName, const GSvector2& v2) {
	CGparameter param = cgGetNamedEffectParameter(mEffect, paramName);
	if (cgIsParameter(param) == CG_TRUE) {
		cgSetParameter2fv(param, (const float*)&v2);
	}
}

// Vector3のパラメータを設定
void Effect::setParameter(const char* paramName, const GSvector3& v3) {
	CGparameter param = cgGetNamedEffectParameter(mEffect, paramName);
	if (cgIsParameter(param) == CG_TRUE) {
		cgSetParameter3fv(param, (const float*)&v3);
	}
}

// Color4のパラメータを設定
void Effect::setParameter(const char* paramName, const GScolor4& c4) {
	CGparameter param = cgGetNamedEffectParameter(mEffect, paramName);
	if (cgIsParameter(param) == CG_TRUE) {
		cgSetParameter4fv(param, (const float*)&c4);
	}
}

// Matrix4のパラメータを設定
void Effect::setParameter(const char* paramName, const GSmatrix4& m4) {
	CGparameter param = cgGetNamedEffectParameter(mEffect, paramName);
	if (cgIsParameter(param) == CG_TRUE) {
		cgSetMatrixParameterfr(param, (const float*)&m4);
	}
}

// テクスチャのパラメータを設定
void Effect::setTexture(const char* textureName, GLuint texture) {
	CGparameter param = cgGetNamedEffectParameter(mEffect, textureName);
	if (cgIsParameter(param) == CG_TRUE) {
		cgGLSetupSampler(param, texture);
	}
}

