#include "Enemy.hpp"
#include "EnemyAnimeManager.hpp"

Enemy::Enemy() :
	imageNumber(0),
	moveAmt(0.0),
	velocity(1.0),
	scoutingRange(0),
	closeScoutingRange(0),
	animeType(EnemyAnimeType::WALK),
	beforeAnimeType(EnemyAnimeType::WALK)
{}

void Enemy::Init(Font font)
{
}

void Enemy::KnockBack()
{
}

void Enemy::InitEnemies(Array<Enemy>& _enemies, Vec2 playerPos, RectF playerHitBox, Font font)
{
	for (Enemy& enemy : _enemies) {
		if (!enemy.isExists) {
			enemy.pos = Vec2(0, 0);
			continue;
		}
		InitEnemy(enemy, playerPos, playerHitBox, font);
	}
}

void Enemy::InitEnemy(Enemy &enemy, Vec2 playerPos, RectF playerHitBox, Font font)
{
		enemy.deltaTime = Scene::DeltaTime();
		enemy.delta = MOVE_STANDARD_X * enemy.deltaTime * enemy.velocity;
		enemy.playerPos = playerPos;
		enemy.playerHitBox = playerHitBox;
		enemy.font = font;
		enemy.UpdateHitBox(enemy, playerPos);
}

void Enemy::State()
{
	if (CharaActionState::ON_DAMAGE == actionState && waitSw.sF() > 1.0) {
		switch (afterOnDamage) {
		case AfterOnDamage::WAIT:
			// TODO: 2種類のステータス管理は面倒なので治す
			actionState = CharaActionState::WAIT;
			animeType = EnemyAnimeType::WAIT;
			imageNumber = 0;
			break;
		case AfterOnDamage::MOVE:
			actionState = CharaActionState::MOVE;
			animeType = EnemyAnimeType::WALK;
			imageNumber = 0;
			break;
		default:
			break;
		}
		waitSw.reset();
	}
	else if (CharaActionState::DOWN == actionState && waitSw.sF() > 1.0) {
		actionState = CharaActionState::WAIT;
		animeType = EnemyAnimeType::WAIT;
		imageNumber = 0;
		waitSw.reset();
		isExists = false;
	}
}

void Enemy::EnemyAction(Array<Bullet>& bullets, Font font)
{
	#ifdef _DEBUG
	hitBox.draw(ColorF(0.5));
	scoutingRangeArea.draw(ColorF(0.7, 0.2, 0.5, 0.5));
	closeScoutingRangeArea.draw(ColorF(0.4, 0.3, 0.5, 1.0));
	#endif
	Init(font);
	State();
	Move();
	Attack(bullets);
}

void Enemy::OnDamage(int damage, bool isRightHit)
{
	hp -= damage;
	//TODO: SE鳴らす
	waitSw.start();
	if (hp <= 0) {
		actionState = CharaActionState::DOWN;
		animeType = EnemyAnimeType::DOWN;
		imageNumber = 0;
	}
	else {
		actionState = CharaActionState::ON_DAMAGE;
		animeType = EnemyAnimeType::ON_DAMAGE;
		imageNumber = 0;
	}
}

void Enemy::Move()
{
	if (CharaActionState::MOVE != actionState) {
		return;
	}
	TernIfNeeded();
	MoveAction();
}

CharaAttackState Enemy::SelectAttackState()
{
	switch (attackType)
	{
	case EnemyAttackType::CLOSE_RANGE:
		return CharaAttackState::CHASE_ATTACK_A;
	case EnemyAttackType::LONG_RANGE:
		return CharaAttackState::ATTACK_A;
	default:
		return CharaAttackState::NONE;
	}
}

void Enemy::CloseRangeAttack()
{
	// close attack enemy is chase type only at this point.
	if (attackType != EnemyAttackType::CLOSE_RANGE) {
		return;
	}
}

void Enemy::Attack(Array<Bullet>& bullets)
{
	if (U"gob" == name) {
		int a = 0;
	}
	SpriteImageMetaData simData = spriteImageMetaDataMap[static_cast<int>(animeType)];
	if (HasDetectedPlayer(scoutingRangeArea)) {
		if (attackType == EnemyAttackType::CLOSE_RANGE) {
			attackState = CharaAttackState::CHASE_ATTACK_A;
		}
		else if (attackType == EnemyAttackType::LONG_RANGE) {
			attackState = CharaAttackState::ATTACK_A;
			animeType = EnemyAnimeType::ATTACK1;
		}

		if (CharaAttackState::CHASE_ATTACK_A == attackState) {
			if (HasDetectedPlayer(closeScoutingRangeArea)) {
				attackState = CharaAttackState::ATTACK_A;
				animeType = EnemyAnimeType::ATTACK1;
			}
			else {
				// Can't stop doing after attack
				EndAttack1(simData, bullets);
			}
		}
	}
	else {
		if (attackState == CharaAttackState::CHASE_ATTACK_A) {
			attackState = CharaAttackState::NONE;
			actionState = CharaActionState::MOVE;
			animeType = beforeAnimeType;
			imageNumber = 0;
			attackSw1.reset();
		}
	}

	if (CharaAttackState::ATTACK_A == attackState) {
		actionState = CharaActionState::ATTACK;
		LongRangeAttack(bullets);
		CloseRangeAttack();
		BeginAttack1();
		EndAttack1(simData, bullets);
	}
}

void Enemy::BeginAttack1()
{
	if (!attackSw1.isRunning()) { // start
		attackSw1.restart();
		imageNumber = 0;
	}
}

void Enemy::EndAttack1(SpriteImageMetaData simData, Array<Bullet>& bullets)
{
	if (IsEndAttackMotion(simData)) { //end
		attackState = CharaAttackState::NONE;
		actionState = CharaActionState::MOVE;
		animeType = beforeAnimeType;
		imageNumber = 0;
		attackSw1.reset();
		for (Bullet& bullet : bullets) {
			bullet.pos = Vec2::Zero();
			bullet.imageNumber = 0;
			bullet.isExists = false;
		}
	}
}

bool Enemy::IsEndAttackMotion(SpriteImageMetaData simData) {
	return attackSw1.isRunning()
		&& imageNumber == simData.maxImageNumber
		&& attackSw1.sF() > simData.coolTime;
}
void Enemy::LongRangeAttack(Array<Bullet>& bullets)
{
	if (attackType != EnemyAttackType::LONG_RANGE) {
		return;
	}
	for (Bullet& bullet : bullets) {
		if (name != bullet.owner) {
			continue;
		}
		// Init
		if (bullet.pos.isZero()) {
			bullet.pos = Vec2(pos.x, pos.y);
			bullet.isExists = true;
		}
		// BulletMove
		double v = rightwardFlag ? bullet.velocity : -bullet.velocity;
		double moving = (Scene::DeltaTime() * v);
		if (bullet.isExists) {
			bullet.distance = Vec2(bullet.distance.x + moving, bullet.distance.y);
		}
		bullet.pos = Vec2(bullet.pos.x + moving, bullet.pos.y);
		// Draw
		AnimationBean aniBean = AnimationBean::InitAnimationBean(bullet);
		Vec2 bulletPos = MapScreenHelper::GetObjectPos(bullet.pos, playerPos);
		bullet.spriteImage(50 * bullet.imageNumber, 150 * aniBean.imageVirticalNumber, Vec2(50, 50))
			.drawAt(bulletPos);

		bullet.hitBox.pos = bullet.isExists ? bulletPos : Vec2();
		bullet.hitBox.draw(ColorF(0.3, 0.5, 0.6, 0.5));
		bullet.imageNumber = EnemyAnimeManager::Animate(aniBean, bullet.bulletSw);
		if ((rightwardFlag && bullet.distance.x > bullet.range)
			|| (!rightwardFlag && -(bullet.distance.x) > bullet.range)) {
			bullet.isExists = false;
			bullet.distance = Vec2::Zero();
		}
	}
}

bool Enemy::HasDetectedPlayer(RectF scouting)
{
	bool isScouting = scouting.intersects(playerHitBox);
	return isScouting;
}

//bool Enemy::HasDetectedPlayer()
//{
//	switch (attackType)
//	{
//	case EnemyAttackType::CLOSE_RANGE:
//		return closeScoutingRangeArea.intersects(playerHitBox);
//	case EnemyAttackType::LONG_RANGE:
//		return scoutingRangeArea.intersects(playerHitBox);
//	default:
//		return false;
//	}
//}

void Enemy::TernIfNeeded() {
	if (deltaAmt > moveAmt) {
		rightwardFlag = !rightwardFlag;
		deltaAmt = 0.0;
	}
}

void Enemy::MoveAction() {
	double _delta = attackState == CharaAttackState::CHASE_ATTACK_A
		? delta + delta * chaseVelocity
		: delta;
	MoveX(rightwardFlag ? _delta : -_delta);
	UpdateHitBox();
}

void Enemy::MoveX(double moveAmt)
{
	pos.x = pos.x + moveAmt;
	deltaAmt += delta;
}

void Enemy::MoveY(double moveAmt)
{
}

void Enemy::UpdateHitBox() {
	UpdateHitBox(isExists, actionState, hitBox, scoutingRangeArea, closeScoutingRangeArea,
		spriteImageMetaDataMap, pos, playerPos, animeType, imageNumber, scoutingRange,
		closeScoutingRange, rightwardFlag, name);
}

void Enemy::UpdateHitBox(Enemy& enemy, Vec2 playerPos) {
	UpdateHitBox(enemy.isExists, enemy.actionState, enemy.hitBox, enemy.scoutingRangeArea, enemy.closeScoutingRangeArea,
		enemy.spriteImageMetaDataMap, enemy.pos, enemy.playerPos, enemy.animeType, enemy.imageNumber, enemy.scoutingRange,
		enemy.closeScoutingRange, enemy.rightwardFlag, enemy.name);
}

void Enemy::UpdateHitBox(bool _isExists, CharaActionState _actionState, RectF &_hitBox, RectF &_scoutingRangeArea, RectF& _closeScoutingRangeArea,
	std::unordered_map<int, SpriteImageMetaData> _spriteImageMetaDataMap, Vec2 _pos, Vec2 _playerPos, EnemyAnimeType _animeType,
	int _imageNumber, int _scoutingRange, int _closeScoutingRange, bool _rightwardFlag, String _name)
{
	if (!_isExists || CharaActionState::DOWN == _actionState) {
		_hitBox.pos = Vec2::Zero();
		_scoutingRangeArea = RectF();
		_closeScoutingRangeArea = RectF();
		return;
	}
	Vec2 screenOriginPosition2(MapScreenHelper::ChangeWorldToScreenPos(_pos));
	Vec2 enemyPos = MapScreenHelper::FixPositionFromPlayerPos(_playerPos, _pos.movedBy(0, -screenOriginPosition2.y));
	if (!_spriteImageMetaDataMap.contains(static_cast<int>(_animeType)))
	{
		throw Error(U"エラー:Enemy.cpp UpdateHitBox priteImageMetaDataMap");
	}
	SpriteImageMetaData metaData = _spriteImageMetaDataMap[static_cast<int>(_animeType)];
	Size size = metaData.sizes[_imageNumber];
	double extendX = 0.0;
	if (_name == U"hamburg") {
		if (_animeType == EnemyAnimeType::ATTACK1 && (_imageNumber == 6 || _imageNumber == 7)) {
			extendX = 40.0;
		}
	}
	double sizeX = size.x + extendX;
	double fixedX = enemyPos.x - (sizeX / 2);
	double fixedY = enemyPos.y - (size.y / 2);
	_hitBox = RectF(Vec2(fixedX, fixedY),
		sizeX - RESIZED_ENEMY_HITBOXES.x,
		size.y - RESIZED_ENEMY_HITBOXES.y);
	int w = _scoutingRange;
	int closeW = _closeScoutingRange;
	int h = size.y;
	if (_rightwardFlag) {
		// TODO: 微妙に右にずれるのはなぜ？
		_scoutingRangeArea = RectF(Vec2(enemyPos.x + (size.x / 2), fixedY).movedBy(0, 0), w, h);
		_closeScoutingRangeArea = RectF(Vec2(enemyPos.x + (size.x / 2), fixedY).movedBy(0, 0), closeW, h);
	}
	else {
		_scoutingRangeArea = RectF(Vec2(fixedX, fixedY).movedBy(-w, 0), w, h);
		_closeScoutingRangeArea = RectF(Vec2(fixedX, fixedY).movedBy(-closeW, 0), closeW, h);
	}
	if (IsOutOfFrame(_hitBox, _playerPos, _pos)) {
		_hitBox.pos = Vec2::Zero();
	}
}

bool Enemy::IsOutOfFrame(RectF hitBox, Vec2 playerPos, Vec2 enemyPos)
{
	double leftX = hitBox.left().begin.x;
	double rightX = hitBox.right().begin.x;
	if (playerPos.x < enemyPos.x) {
		//　敵の位置がプレイヤーより右側
		if (IsMovingRightInFrame(playerPos)) {
			double movingRight = playerPos.x - PLAYER_STAND_POS.x;
			return leftX > Scene::Size().x + movingRight;
		}
		else if (PLAYER_STAND_POS.x >= playerPos.x) {
			return leftX > Scene::Size().x;
		}
	}
	else {
		//　敵の位置がプレイヤーより左側
		double leftFrame = playerPos.x - PLAYER_STAND_POS.x;
		return rightX < 0;
	}
}