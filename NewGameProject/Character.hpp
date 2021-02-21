#pragma once
#include "Property.hpp"
#include "EnumManager.hpp"
#include "Bullet.hpp"

class Character
{
public:
	/** 画像 */
	Texture allImage;
	/* 当たり判定 */
	RectF hitBox;
	/* 当たり判定(1フレーム前) */
	RectF beforeHitBox;
	/* 着地点 */
	double ground;
	/* 横移動量 */
	double delta;
	/* 総横移動量 */
	double deltaAmt;
	/* 動く床に乗っているときの加算横移動量 */
	double deltaAmtOnMovingFloor;
	/* 1フレーム毎の経過時間(秒) */
	double deltaTime;
	/* ジャンプ量 */
	double jumpHeight;
	/* ジャンプ時の重力 */
	Vec2 gravity;
	/* 生命力 */
	int hp;
	/* 受けたダメージ */
	int damaged;
	/* 存在フラグ */
	bool isExists;
	/* 右向きフラグ */
	bool rightwardFlag;
	/** 操作受け付けフラグ */
	bool isActive;
	/** 無敵フラグ */
	bool isInvisible;
	/** 攻撃1存在フラグ */
	bool isAttack1;
	/** 汎用フラグ */
	bool flag;
	/** 右側にヒットしたか */
	bool isRightHit;
	/** 攻撃を受けたか */
	bool isOnDamage;
	/* ジャンプ落下フラグ */
	bool jumpFallFlag;
	/* 落下モード */
	CharaFallMode charaFallMode;
	/* ジャンプモード */
	JumpMode jumpMode;
	/* ダッシュ後フラグ */
	bool afterDashFlag;
	/* どの方向の壁に触れたか */
	MapTipTouching wallTipTouching;
	/* どの方向のオブジェクトに触れたか */
	MapTipTouching objectTipTouching;
	/* 触れたチップの種類 */
	MapType touchedMapType;
	/* 触れたチップのID */
	long touchedObjectId;
	bool topWallFlag;
	bool topWallFlag2;
	/* 一時的に壁判定処理を無視 */
	bool ignoreWall;
	/* キャラの種類 */
	CharaType charaType;
	/* 踏んでいる床の種類 */
	OnFloorType onFloorType;
	/* 位置 */
	Vec2 pos;
	/* 補正前の位置 */
	Vec2 beforePos;
	/* 配置座標 */
	Vec2 originPos;
	/* 動作状態 */
	CharaActionState actionState;
	/* 攻撃状態 */
	CharaAttackState attackState;
	/* アーマークラス */
	ArmorClass armorClass;
	/* 汎用ストップウォッチ */
	Stopwatch sw;
	/* クールタイム用のストップウォッチ */
	Stopwatch waitSw;
	/* 攻撃用ストップウォッチ1 */
	Stopwatch attackSw1;
	/* 汎用タイムカウント */
	double time;
	/* 画像番号 */
	int imageNumber;
	/* フォント */
	Font font;
	/** スプライト画像のメタデータマップ */
	std::unordered_map<int, SpriteImageMetaData> spriteImageMetaDataMap;
public:
	Character();
	virtual void Init(Font font);
	virtual void Action(Array<Bullet>& bullets);
	virtual void OnDamage(int damage, bool rightHit);
	virtual void KnockBack();
	virtual bool IsInvisible();
	virtual void MoveX(double moveAmt);
	virtual void MoveY(double moveAmt);
	bool IsMovingRightInFrame(Vec2 playerPos);
	bool IsFixLeftInFrame(Vec2 playerPos);
};