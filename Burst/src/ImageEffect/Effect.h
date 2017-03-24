#pragma once

#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <gslib.h>

// エフェクトクラス
class Effect {
public:
	// コンストラクタ
	Effect(const char* filename);
	// デストラクタ
	~Effect();
	// 現在のパスを開始する
	void begin();
	// パスを指定する
	void pass(int passNo);
	// 現在のパスを終了する
	void end();
	// 現在のテクニックのパス数を取得
	int getNumPass();
	// テクニックを設定
	void setTechnique(const char* techniqueName);
	// floatのパラメータを設定
	void setParameter(const char* paramName, float v);
	// Vector2のパラメータを設定
	void setParameter(const char* paramName, const GSvector2& v2);
	// Vector3のパラメータを設定
	void setParameter(const char* paramName, const GSvector3& v3);
	// Color4のパラメータを設定
	void setParameter(const char* paramName, const GScolor4& c4);
	// Matrix4のパラメータを設定
	void setParameter(const char* paramName, const GSmatrix4& m4);
	// テクスチャのパラメータを設定
	void setTexture(const char* textureName, GLuint texture);
private:
	// ＣＧコンテキスト
	CGcontext mContext;
	// エフェクト
	CGeffect mEffect;
	// テクニック
	CGtechnique mTechnique;
	// パス
	CGpass mPass;
};
