#pragma once
#include <Siv3D.hpp>

// マップチップの画像が横に展開されている数
constexpr auto MAP_IMAGE_WIDTH_MAX = 16;
// マップチップの縦横サイズ
constexpr auto MAP_IMAGE_SQUARE_SIZE = 16;

// ジャンプ時
// スプライト画像のY座標指定(頂点)
constexpr auto PLAYER_JUMP_SPRITE_Y = 385;
// 画像サイズ
constexpr auto PLAYER_JUMP_SPRITE_SIZE = Vec2(46, 47);
// スプライト切り替え時間
constexpr auto PLAYER_JUMP_SPRITE_CHANGE = 0.1;
// 上昇時の最大画像番号
constexpr auto PLAYER_JUMP_UP_MAX_IMAGE_NUMBER = 2;

// ダッシュ時
constexpr auto SPRITE_DASH_NUMBER = 4;
// スプライト画像の座標指定
constexpr auto PLAYER_DASH_SPRITE_POS = Vec2(263, 318);
// 画像サイズ
constexpr auto PLAYER_DASH_SPRITE_SIZE = Vec2(52, 42);

// 歩き時
// スプライト画像のY座標指定(頂点)
constexpr auto PLAYER_RUN_SPRITE_Y = 265;
// 画像サイズ
constexpr auto PLAYER_RUN_SPRITE_SIZE = Vec2(63.75, 47);
// スプライト切り替え時間
constexpr auto PLAYER_RUN_SPRITE_CHANGE = 0.05;

// 直立時
// スプライト画像のY座標指定(頂点)
constexpr auto PLAYER_STAND_SPRITE_Y = 175;
// 画像サイズ
constexpr auto PLAYER_STAND_SPRITE_SIZE = Vec2(50, 55);
// スプライト切り替え時間
constexpr auto PLAYER_STAND_SPRITE_CHANGE = 0.4;

// しゃがみ時
constexpr auto CROUCH_MAX_IMAGE_NUMBER = 4;
// スプライト画像のY座標指定(頂点)
constexpr auto PLAYER_CROUCH_SPRITE_X = 88;
// スプライト画像のY座標指定(頂点)
constexpr auto PLAYER_CROUCH_SPRITE_Y = 456;
// 画像サイズ
constexpr auto PLAYER_CROUCH_SPRITE_SIZE = Vec2(44, 48);
// スプライト切り替え時間
constexpr auto PLAYER_CROUCH_SPRITE_CHANGE = 0.03;

// 梯子つかみ時
// スプライト画像のY座標指定(頂点)
constexpr auto PLAYER_GRAB_LADDER_SPRITE_Y = 1134;
// 画像サイズ
constexpr auto PLAYER_GRAB_LADDER_SPRITE_SIZE = Vec2(21, 48);

// ワープ射撃時
// スプライト画像のY座標指定(頂点)
constexpr auto BULLET_WARP_SPRITE_Y = 788;
// 画像サイズ
constexpr auto BULLET_WARP_SPRITE_SIZE = Vec2(56, 54);
// スプライト切り替え時間
constexpr auto BULLET_WARP_SPRITE_CHANGE = 0.03;
// ウェイトタイム
constexpr auto BULLET_WARP_SPRITE_WAIT = 1.0;
// 発射時のスプライト画像
constexpr auto BULLET_WARP_FLASH_SPRITE_NUMBER = 2;
// 最大スプライト画像
constexpr auto BULLET_WARP_MAX_SPRITE_NUMBER = 4;

// 攻撃１時
// スプライト画像のY座標指定(頂点)
constexpr auto ATTACK1_SPRITE_Y = 788;
// 画像サイズ
constexpr auto ATTACK1_SPRITE_SIZE = Vec2(56, 54);
// スプライト切り替え時間
constexpr auto ATTACK1_SPRITE_CHANGE = 0.03;
// ウェイトタイム
constexpr auto ATTACK1_SPRITE_WAIT = 1.0;
// 発射時のスプライト画像
constexpr auto ATTACK1_FLASH_SPRITE_NUMBER = 2;
// 最大スプライト画像
constexpr auto ATTACK1_MAX_SPRITE_NUMBER = 4;

// 攻撃２時
// スプライト画像のY座標指定(頂点)
constexpr auto BULLET_ATTACK2_SPRITE_Y = 877;
// 画像サイズ
constexpr auto BULLET_ATTACK2_SPRITE_SIZE = Vec2(49, 50);
// 修正用の画像座標
static Array<Vec2> BULLET_ATTACK2_FIX_SPRITE_VEC2S = {
	Vec2(0, 0), Vec2(0, 0), Vec2(8, 0), Vec2(8, 0), Vec2(8, 0), Vec2(8, 0), Vec2(0, 0)
};
// スプライト切り替え時間
constexpr auto ATTACK2_SPRITE_CHANGE = 0.1;
// ウェイトタイム
constexpr auto ATTACK2_SPRITE_WAIT = 4.0;
// 最大スプライト画像
constexpr auto BULLET_ATTACK2_MAX_SPRITE_NUMBER = 6;

// 攻撃3時
// スプライト画像のY座標指定(頂点)
constexpr auto BULLET_ATTACK3_SPRITE_Y = 963;
// 画像サイズ
constexpr auto BULLET_ATTACK3_SPRITE_SIZE = Vec2(48, 49);
// 最大スプライト画像
constexpr auto BULLET_ATTACK3_MAX_SPRITE_NUMBER = 11;
// 修正用の画像サイズ
static Array<Vec2> BULLET_ATTACK3_FIX_SPRITE_VEC2S = {
	Vec2(0, 0), Vec2(0, 0), Vec2(1, 0), Vec2(1, 0), Vec2(4, 0), Vec2(4, 0), Vec2(7, 0),
	Vec2(9, 0), Vec2(9, 0), Vec2(1, 0), Vec2(1, 0), Vec2(0, 0),
};
// クールタイム
constexpr auto ATTACK3_SPRITE_COOL = 3.0;

// 被ダメージ時
// スプライト画像のY座標指定(頂点)
constexpr auto PLAYER_ONDAMEGE_SPRITE_Y = 633;
// 画像サイズ
constexpr auto PLAYER_ONDAMEGE_SPRITE_SIZE = Vec2(40, 53);
// スプライト切り替え時間
constexpr auto PLAYER_ONDAMEGE_SPRITE_CHANGE = 0.02;
// 被ダメ時間
constexpr auto PLAYER_ONDAMEGE_SPRITE_WAIT = 1.5;
// 無敵時間
constexpr auto PLAYER_INVISIBLE_TIME = 4.0;
// ノックバック時、のけ反りスピードの倍率
constexpr auto PLAYER_SQUEEZE_A = 0.1;
// 最大スプライト画像
constexpr auto PLAYER_ONDAMEGE_MAX_SPRITE_NUMBER = 3;

// ダウン時
// 修正用の画像サイズ
static Array<Vec2> PLAYER_DOWN_SPRITE_FIX_VEC2_ARRAY = {
	Vec2(0, 15), Vec2(0, 7), Vec2(0, 7), Vec2(0, 7), Vec2(0, 0),
	Vec2(0, 0), Vec2(0, 0)
};
// スプライト切り替え速度を遅くする倍率
constexpr auto PLAYER_DOWN_SLOW_FOLD = 3.0;

// プレイヤーのHP
constexpr auto PLAYER_HP = 3;
// プレイヤーのひん死HP
constexpr auto PLAYER_DANGER_HP = 2;
// プレイヤーの位置(X)
constexpr auto PLAYER_STAND_POS_X = 400;
// プレイヤーの位置(Y)
constexpr auto PLAYER_STAND_POS_Y = 480;
// プレイヤーの中心となる座標
constexpr auto PLAYER_STAND_POS = Vec2(PLAYER_STAND_POS_X, PLAYER_STAND_POS_Y);
// カメラを動かさない基準(右側最大... 1200)
constexpr auto PLAYER_RIGHT_END_POS = Vec2(880, PLAYER_STAND_POS_Y);

// プレイヤーの当たり判定(高さ)
constexpr auto PLAYER_DETEC_H = 54.1;
// プレイヤーの当たり判定(幅)
constexpr auto PLAYER_DETEC_W = 25;
// STAND時の画像位置補正(X)
constexpr auto FIXED_STAND_RIGHT_X = -15;
constexpr auto FIXED_STAND_LEFT_X = -10;

// 画像表示の補正
// しゃがみ
static Array<Vec2> PLAYER_CROUCH_SPRITE_FIX_VEC2_ARRAY = {
	Vec2(0, 0), Vec2(0, -10), Vec2(0, -7), Vec2(0, -12), Vec2(0, -14)
};
// 歩き
constexpr auto IMAGE_WALK_POS = Vec2(-18, 8);
// ジャンプ
constexpr auto IMAGE_JUMP_LEFT_POS = Vec2(-20, 0);
constexpr auto IMAGE_JUMP_RIGHT_POS = Vec2(-3, 0);

// プレイヤーのしゃがみ時の当たり判定(高さ)
constexpr auto PLAYER_CROUCH_DETEC_H = 30.1;
// 当たり判定の補正　※画像よりも小さくして有利にする
constexpr auto PLAYER_FIXED_CROUCH_H = 24;

// プレイヤーのジャンプの高さ
constexpr int PLAYER_JUMP_HEIGHT = 110;
// ジャンプ時のゆがみ（サインカーブ）
constexpr double JUMP_DESTORTION = 1.5;
// ジャンプ時の総フレーム数
constexpr int FLAME_BY_JUMP = 40;
// ジャンプ時の落下開始時点のフレームカウント(大体)
constexpr int FLAME_BY_FALING = 16;
// ジャンプ座標リストの大体頂点あたりのインデックス
constexpr int ABOUT_TOP_JUMP_Y_INDEX = 11;
// Y軸移動時の固定値
constexpr int MOVE_STANDARD_X = 200;
// ダッシュの距離
constexpr int DASH_DIST = 100;
// ダッシュ時のゆがみ(cf.サインカーブ)
constexpr double DASH_DISTORTION = 0.5;
// ダッシュ時の縦浮遊
constexpr double DASH_HEIGHT = 20.0;
// ダッシュの計算のためのπ
constexpr double DASH_PI = 125_deg;
// ダッシュボタンを押したときの加速倍率
constexpr double DASH_ACCELERATION = 1.5;
// 降下時の画像番号(0から)
constexpr int FALL_ANIME_NUMBER = 6;
// マップの相対パス
constexpr auto MAP_XML_PATH = U"map/test4.tmx";
// スクリーンサイズ（マップの最大サイズ）
constexpr auto MAX_SCREEN_SIZE = Vec2(1920.0, 1280.0);
// カメラのポジション +16は左端の柵を見せないように
constexpr auto CAMERA_POS = Vec2(
	MAX_SCREEN_SIZE.x / 4.0 - 80 + 16, MAX_SCREEN_SIZE.y / 2.0 * 1.5 + 20);
// 落下量
constexpr auto FALL_AMT = 7;
// ジャンプ時の時間経過値
constexpr auto JUMP_BASE_TAME = 0.07;
// ジャンプ落下が始まるフレームカウント
constexpr auto FALL_FLAME_COUNT = 20;
// ダッシュの間隔時間
constexpr auto DASH_WAIT_TIME = 0.4;

// ワイヤーバレット
// 速度
constexpr auto WIRE_BULLET_VELOCITY = 400.0;
// 射程距離
constexpr auto WIRE_BULLET_RANGE = 300.0;
// 着弾時プレイヤーの移動速度
constexpr auto WIRE_BULLET_MOVE_SPEED = 10;

// 攻撃１バレット
// 速度
constexpr auto ATTACK1_BULLET_VELOCITY = 450.0;
// 射程距離
constexpr auto ATTACK1_BULLET_RANGE = 500.0;

// 攻撃3バレットの開始画像番号
constexpr auto SHOOT_ATTACK_3_START_IMAGE_NUMBET = 12;


// おまじない系(FIXED:原因をはっきりさせること)
// オブジェクトのY軸をマイナスする。（何故か16px下にずれている）
constexpr auto OBJECT_FIXED_Y = 16.0;

// 敵接触時のダメージ
constexpr auto ENEMY_HITBOX_DAMAGE = 1;

// 敵ヒットボックスのサイズ調整用
constexpr auto RESIZED_ENEMY_HITBOXES = Vec2(5, 5);

// 敵ダウン時のアニメーション持続時間
constexpr auto ENEMY_DOWN_REMAINNING_TIME = 1.0;

constexpr auto OBJ_VELOCITY = 5.0;