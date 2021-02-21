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
	// �����Ȃ�
	NONE,
	// ���R����
	NATURAL_FALL,
	// �W�����v��̗���
	JUMP_FALL,
	// ���V
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
	// ��q
	UPPERMOST,
	LADDER,
	LOWERMOST,
	ROCK,
	TOP_ROCK,
	//�X���[�v
	RIGHT_SLOPE,
	RIGHT_SLOPE_UP,
	// �R�C��
	COIN,
	// ��
	KEY,
	// �W�����v��
	AIR_BROW_UP,
	// ������
	MOVE_FLOOR_A,
	// �_���[�W��
	DAMAGE_FLOOR_A,
	// �G�̃W�����v��
	ENEMY_WAIT_A,
	// �����I�u�W�F�N�g
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

enum class CharaActionState // TODO:��Ԉُ킪����ΕʂŊǗ�����H
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
	// ���[�v�ˌ�
	WARP,
	// �ʏ�ˌ�
	ATTACK_1,
	// �m�b�N�o�b�N+���G�t���̎ˌ�
	ATTACK_2,
	// �񒚌��e�̎ˌ�
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

// �X�v���C�g�摜�̏c�ԂɑΉ�
enum class PlayerAnimeType
{
	NONE,
	STAND,
	RUN,
	DASH,
	JUMP,
	CROUCH,
	GARD, // �g��Ȃ�
	ON_DAMAGE,
	DOWN, // �X�v���C�g���鏇�Ԃ��t
	SHOOT_ATTACK_1,
	SINGLE_BULLET,
	SHOOT_ATTACK_2,
	SHOOT_ATTACK_3,
	SHOOT_ATTACK_4

};

enum class EnemyAnimeType
{
	NONE, // NONE�͎g��Ȃ�
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
/// �_���[�W���󂯂��ۂ̋������Ǘ�����Enum�N���X
/// </summary>
enum class ArmorClass
{
	// ��ɔ�_�����[�V�����ɓ���
	NORMAL,
	// �U�����ɔ�_�����[�V�����ɓ���Ȃ�
	SUPER,
	// ��_�����[�V�����ɓ���Ȃ�
	HYPER
};

enum class EffectType
{
	NONE,
	STAR_BURST_1,
	STAR_TRAILS_1
};

