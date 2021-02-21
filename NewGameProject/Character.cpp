#include "Character.hpp"

Character::Character() :
	damaged(0),
	deltaTime(0.0),
	delta(0.0),
	time(0.0),
	deltaAmtOnMovingFloor(0.0),
	onFloorType(OnFloorType::NORMAL),
	actionState(CharaActionState::WAIT),
	attackState(CharaAttackState::NONE),
	armorClass(ArmorClass::NORMAL),
	touchedMapType(MapType::NORMAL),
	isExists(true),
	rightwardFlag(true),
	isAttack1(false),
	isActive(true),
	isOnDamage(false),
	flag(false),
	ignoreWall(false),
	imageNumber(0)
{
	this->ground = (PLAYER_STAND_POS.y);
}

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

