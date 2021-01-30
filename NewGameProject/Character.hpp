#pragma once
#include "Property.hpp"
#include "EnumManager.hpp"
#include "Bullet.hpp"

class Character
{
public:
	/** 画像 */
	Texture allImage;
	/* 着地点 */
	double groundY;
	/* 横移動量 */
	double delta;
	/* 総横移動量 */
	double deltaAmt;
	/* 1フレーム毎の経過時間(秒) */
	double deltaTime;
	/* 生命力 */
	int hp;
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
	/* 位置 */
	Vec2 pos;
	/* 補正前の位置 */
	Vec2 beforePos;
	/* 動作状態 */
	CharaActionState actionState;
	/* 攻撃状態 */
	CharaAttackState attackState;
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