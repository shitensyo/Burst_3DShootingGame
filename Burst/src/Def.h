#pragma once

//ウィンドウの幅
static const float WINDOW_WIDTH = 800;

//ウィンドウの高さ
static const float WINDOW_HEIGHT = 600;

//ブルームのきめ細かさ（幅）、数値が大きいほど細かくなる
static const int BLOOM_WIDTH = 400;
//ブルームのきめ細かさ（高さ）、数値が大きいほど細かくなる
static const int BLOOM_HEIGHT = 300;


//視野角
static const float FOV = 60.0f;
//アスペクト比
static const float ASPECT = WINDOW_WIDTH / WINDOW_HEIGHT;
//ニア
static const float PERSPECTIVE_NEAR = 0.3f;
//ファー
static const float PERSPECTIVE_FAR = 20000.0f;