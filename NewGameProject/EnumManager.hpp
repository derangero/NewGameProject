#pragma once

enum class TipMovingBy
{
	NONE,
	RIGHT,
	LEFT
};
enum class JumpMode
{
	NONE,
	UP,
	FALL
};

enum class CharaFallMode
{
	// 落下なし
	NONE,
	// 自由落下
	NATURAL_FALL,
	// ジャンプ後の落下
	JUMP_FALL,
	// 浮遊
	BROW_UP_A
};

enum class MapTipTouching
{
	NONE,
	TOP,
	RIGHT,
	BOTTOM,
	LEFT
};

enum class CharaType
{
	PLAYER,
	NORMAL_ENEMY,
	BOSS_ENEMY
};

enum class Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum class MapType
{
	NORMAL,
	// 梯子
	UPPERMOST,
	LADDER,
	LOWERMOST,
	ROCK,
	TOP_ROCK,
	//スロープ
	RIGHT_SLOPE,
	RIGHT_SLOPE_UP,
	// コイン
	COIN,
	// 鍵
	KEY,
	// ジャンプ台
	AIR_BROW_UP,
	// 動く床
	MOVE_FLOOR_A,
	// ダメージ床
	DAMAGE_FLOOR_A,
	// 敵のジャンプ床
	ENEMY_WAIT_A,
	// 動くオブジェクト
	MOVABLE_OBJ_A
};

enum class RadderMode
{
	NONE,
	FIRST_TOUCH,
	GRABBING,
	RELEASE
};

enum class EnemyType
{
	NONE,
	EYE,
	HAMBURG,
	GOB,
	SKULL
};

enum class CharaActionState // TODO:状態異常があれば別で管理する？
{
	WAIT,
	MOVE,
	ATTACK,
	ON_DAMAGE,
	ON_DAMAGE_INVISIBLE,
	DOWN,
	CHASE
};

enum class CharaAttackState
{
	NONE,
	ATTACK_A,
	ATTACK_B,
	ATTACK_C,
	ATTACK_D,
	CHASE_ATTACK_A
};

enum class HitBoxDetection
{
	NONE,
	TOP_BEGIN,
	BOTTOM_BEGIN,
	BOTTOM_END
};

enum class AnimationEndMode
{
	STOP,
	REPEAT,
	VANISH
};

enum class BulletMode
{
	NONE,
	// ワープ射撃
	WARP,
	// 通常射撃
	ATTACK_1,
	// ノックバック+無敵付きの射撃
	ATTACK_2,
	// 二丁拳銃の射撃
	ATTACK_3
};

enum class BulletName
{
	NONE,
	WARP,
	ATTACK_1,
	ATTACK_2,
	ATTACK_3
};

enum class OnFloorType
{
	NORMAL,
	MOVING
};

// スプライト画像の縦番に対応
enum class PlayerAnimeType
{
	NONE,
	STAND,
	RUN,
	DASH,
	JUMP,
	CROUCH,
	GARD, // 使わない
	ON_DAMAGE,
	DOWN, // スプライトする順番が逆
	SHOOT_ATTACK_1,
	SINGLE_BULLET,
	SHOOT_ATTACK_2,
	SHOOT_ATTACK_3,
	SHOOT_ATTACK_4

};

enum class EnemyAnimeType
{
	NONE, // NONEは使わない
	WAIT,
	WALK,
	ON_DAMAGE,
	DOWN,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	ATTACK4,
	GURD
};

enum class AfterOnDamage
{
	NON,
	WAIT,
	MOVE,
	RUN_OUT
};

enum class EnemyAttackType
{
	NONE,
	LONG_RANGE,
	CLOSE_RANGE
};

/// <summary>
/// ダメージを受けた際の挙動を管理するEnumクラス
/// </summary>
enum class ArmorClass
{
	// 常に被ダメモーションに入る
	NORMAL,
	// 攻撃中に被ダメモーションに入らない
	SUPER,
	// 被ダメモーションに入らない
	HYPER
};

enum class EffectType
{
	NONE,
	STAR_BURST_1,
	STAR_TRAILS_1
};

