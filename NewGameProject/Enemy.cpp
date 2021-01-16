#include "Enemy.hpp"
#include "EnemyAnimeManager.hpp"

Enemy::Enemy() :
	imagePos(Vec2(0, 0)),
	imageNumber(0),
	moveAmt(0.0),
	velocity(1.0),
	scoutingMagnification(0.0),
	animeType(EnemyAnimeType::WAIT),
	beforeAnimeType(EnemyAnimeType::WAIT)
{}

void Enemy::Init(Font font)
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
		UpdateHitBox(enemy, playerPos);
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
	scoutingRange.draw(ColorF(0.7, 0.2, 0.5, 0.5));
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
	if (CharaAttackState::NONE != attackState || CharaActionState::DOWN == actionState || EnemyAnimeType::ON_DAMAGE == animeType || CharaActionState::WAIT == actionState ) {
		return;
	}
	TernIfNeeded();
	MoveAction();
}

void Enemy::Attack(Array<Bullet>& bullets)
{
	if (HasDetectedPlayer()) {
		attackState = CharaAttackState::ATTACK_A;
		animeType = EnemyAnimeType::ATTACK1;
	}
	if (attackState == CharaAttackState::ATTACK_A) {
		for (Bullet &bullet : bullets) {
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
		if (!attackSw1.isRunning()) { // start
			attackSw1.restart();
			imageNumber = 0;
		} else if (attackSw1.sF() > 3.0) { //end
			attackState = CharaAttackState::NONE;
			animeType = beforeAnimeType;
			imageNumber = 0;
			attackSw1.pause();
			for (Bullet& bullet : bullets) {
				bullet.pos = Vec2::Zero();
				bullet.imageNumber = 0;
				bullet.isExists = false;
			}

		}
	}
}

bool Enemy::HasDetectedPlayer()
{
	return scoutingRange.intersects(playerHitBox);
}

void Enemy::TernIfNeeded() {
	if (deltaAmt > moveAmt) {
		rightwardFlag = !rightwardFlag;
		deltaAmt = 0.0;
	}
}

void Enemy::MoveAction() {
	MoveX(rightwardFlag ? delta : -delta);
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
	UpdateHitBox(isExists, actionState, hitBox, scoutingRange,
		spriteImageMetaDataMap, pos, playerPos, animeType, imageNumber, scoutingMagnification,
		rightwardFlag, name);
}

void Enemy::UpdateHitBox(Enemy& enemy, Vec2 playerPos) {
	UpdateHitBox(enemy.isExists, enemy.actionState, enemy.hitBox, enemy.scoutingRange,
		enemy.spriteImageMetaDataMap, enemy.pos, enemy.playerPos, enemy.animeType, enemy.imageNumber, enemy.scoutingMagnification,
		enemy.rightwardFlag, enemy.name);
}

void Enemy::UpdateHitBox(bool _isExists, CharaActionState _actionState, RectF &_hitBox, RectF &_scoutingRange,
	std::unordered_map<int, SpriteImageMetaData> _spriteImageMetaDataMap, Vec2 _pos, Vec2 _playerPos, EnemyAnimeType _animeType,
	int _imageNumber, int _scoutingMagnification, bool _rightwardFlag, String _name) {
	if (!_isExists || CharaActionState::DOWN == _actionState) {
		_hitBox.pos = Vec2::Zero();
		_scoutingRange = RectF();
		return;
	}
	Vec2 screenOriginPosition2(MapScreenHelper::ChangeWorldToScreenPos(_pos));
	Vec2 enemyPos = MapScreenHelper::FixPositionFromPlayerPos(_playerPos, _pos.movedBy(0, -screenOriginPosition2.y));
	if (!_spriteImageMetaDataMap.contains(static_cast<int>(_animeType)))
	{
		throw Error(U"エラー:Enemy.cpp UpdateHitBox priteImageMetaDataMap");
	}
	SpriteImageMetaData metaData = _spriteImageMetaDataMap[static_cast<int>(_animeType)];
	Size size = Size::Zero();
	if (metaData.sizes.size() <= _imageNumber)
	{
		_imageNumber = 0;
		size = metaData.sizes[_imageNumber];
		//throw Error(U"エラー:Enemy.cpp UpdateHitBox サイズの動的配列を超えるimageNumberが検出されました");
	}
	else {
		size = metaData.sizes[_imageNumber];
	}
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
	double w = _scoutingMagnification;
	double h = size.y;
	if (_rightwardFlag) {
		// TODO: 微妙に右にずれるのはなぜ？
		_scoutingRange = RectF(Vec2(enemyPos.x + (size.x / 2), fixedY).movedBy(0, 0), w, h);
	}
	else {
		_scoutingRange = RectF(Vec2(fixedX, fixedY).movedBy(-w, 0), w, h);
	}
}