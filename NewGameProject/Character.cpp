#include "Character.hpp"

Character::Character() :
	groundY(PLAYER_STAND_POS.y),
	deltaTime(0.0),
	delta(0.0),
	time(0.0),
	actionState(CharaActionState::WAIT),
	attackState(CharaAttackState::NONE),
	isExists(true),
	rightwardFlag(true),
	isAttack1(false),
	isActive(true),
	flag(false),
	imageNumber(0)
{}

void Character::Init(Font font)
{
}

void Character::Action(Array<Bullet>& bullets)
{
}

void Character::OnDamage(int damage, bool isRightHit)
{
}

void Character::KnockBack()
{
}

bool Character::IsInvisible()
{
	return isInvisible;
}

void Character::MoveX(double moveAmt)
{
}

void Character::MoveY(double moveAmt)
{
}

bool Character::IsMovingRightInFrame(Vec2 playerPos)
{
	// �E����)�J�����̉���Ƀv���C���[�����邩�H
	// ��)�v���C���[�̊�ʒu��480�A481�Ɉړ������ꍇ
	// ��)�E�̍Œ[��1200�Ȃ�A�v���C���[�̈ʒu��880�𒴂�����J�����͎~�܂�
	return PLAYER_STAND_POS.x < playerPos.x && playerPos.x < PLAYER_RIGHT_END_POS.x;
}

bool Character::IsFixLeftInFrame(Vec2 playerPos)
{
	// �E����)�J�����̉���Ƀv���C���[�����邩�H
	// ��)�v���C���[�̊�ʒu��480�A481�Ɉړ������ꍇ
	// ��)�E�̍Œ[��1200�Ȃ�A�v���C���[�̈ʒu��880�𒴂�����J�����͎~�܂�
	return PLAYER_STAND_POS.x >= playerPos.x;
}