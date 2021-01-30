#pragma once
enum JumpMode
{
	UP,
	FALL
};

enum Direction
{
	TOP,
	RIGHT,
	BOTTOM,
	LEFT
};

enum MapObjectType
{
	NONE,
	// 梯子
	UPPERMOST,
	LADDER,
	LOWERMOST,
	ROCK,
	TOP_ROCK,
	//スロープ
	RIGHT_SLOPE,
	RIGHT_SLOPE_UP,
	// 草A
	GRASS_A
};

enum class RadderMode
{
	NONE,
	GRABBED,
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