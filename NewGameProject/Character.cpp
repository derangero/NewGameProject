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
