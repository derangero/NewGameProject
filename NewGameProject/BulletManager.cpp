#include "BulletManager.hpp"
# include "TimeManager.hpp"

BulletManager::BulletManager(Bullet bullet)
{
}

void BulletManager::ActionWarpBullet(Array<Bullet>& bullets, Player& player, Array<MapTip>& mapTips)
{
	for (Bullet& bullet : bullets) {
		if (bullet.name != BulletName::WARP) {
			continue;
		}
		// TODO:Debug
		player.font(U"playerWarpBulletX:", bullet.pos.x).draw(0, 150);
		player.font(U"playerWarpBulletY:", bullet.pos.y).draw(0, 170);
		player.font(U"isExists:", bullet.isExists).draw(0, 190);

		// TODO:当たり判定等の挙動が不審なので考えること
		if (IsCollisionDetected(bullet, player, mapTips)) {
			player.waitFlag = true; // 線形補間中は操作を受け付けない
			if (!bullet.bulletSw.isRunning()) {
				bullet.bulletSw.restart();
			}
			LerpForBulletEndPos(bullet, player);
		}
		else {
			if (BulletMode::WARP == player.bulletMode && !bullet.isExists) {
				bullet.isExists = true;
			}
			if (bullet.isExists) {
				bullet.Update(player.pos, player.detection);
				bullet.Draw(player.pos, player.detection);
				String bulletName = U"NONE";
				if (player.bulletMode == BulletMode::WARP) {
					bulletName = U"WARP";
				}
				else {
					bulletName = U"NONE";
				}
				player.font(U"playerBulletMode:", bulletName).draw(0, 290);
				if (IsOutRange(bullet)) {
					ClearBullet(bullet);
				}
			}
		}
	}
}

void BulletManager::ActionBullet_1(Array<Bullet>& bullets, Player& player, Array<MapTip>& mapTips, TimeManager& timeMngr)
{
	player.font(U"isShooted:", player.isShooted).draw(0, 210);
	// オブジェクトのライフサイクルを管理
	for (Bullet& bullet : bullets) {
		if (bullet.owner != U"player" || bullet.name != player.bulletName || !player.isShooted) {
			continue;
		}
		if (!bullet.isExists) {
			bullet.isExists = true;
			player.isShooted = false;
			break;
		}
	}
	// 本処理
	for (Bullet& bullet : bullets) {
		if (bullet.owner != U"player" || bullet.name != player.bulletName || !bullet.isExists) {
			continue;
		}
		if (IsCollisionDetected(bullet, player, mapTips)) {
			ClearBullet(bullet, timeMngr);
			bullet.isHit = false;
			return;
		}
		bullet.Update(player.pos, player.detection);
		bullet.Draw(player.pos, player.detection, bullet.name, player.allImage,
			player.spriteImageMetaDataMap, timeMngr);

		if (IsOutRange(bullet)) {
			ClearBullet(bullet, timeMngr);
		}
	}
}

void BulletManager::BulletHit(Player& player, Array<Enemy>& enemies, Array<Bullet>& bullets, Array<MapTip>& mapTips, Font font, TimeManager& timeMngr)
{
	for (Bullet& playerBullet : bullets) {
		if (playerBullet.owner != U"player") {
			continue;
		}
		for (Enemy& enemy : enemies) {
			if (enemy.hitBox.intersects(playerBullet.hitBox) && !enemy.isInvisible && playerBullet.isExists) {
				enemy.OnDamage(playerBullet.damage, false);
				font(playerBullet.damage).draw(enemy.playerPos.movedBy(0, -60));
				player.isAttack1 = true;
				playerBullet.isExists = false;
				timeMngr.bulletAttack1Cool.reset();
			}
			if (enemy.hitBox.intersects(player.detection)) {
				bool isRightHit = IsHitRight(enemy.hitBox.x, player.detection.center().x);
				player.OnDamage(ENEMY_HITBOX_DAMAGE, isRightHit);
			}
		}
	}
	for (Bullet& enemyBullet : bullets) {
		if (enemyBullet.owner == U"player") {
			continue;
		}
		if (enemyBullet.hitBox.intersects(player.detection)) {
			bool isRightHit = IsHitRight(enemyBullet.hitBox.center().x, player.detection.center().x);
			player.OnDamage(enemyBullet.damage, isRightHit);
		}
	}
}

bool BulletManager::IsOutRange(Bullet bullet) {
	return Direction::RIGHT == bullet.direction && bullet.pos.x >= bullet.startPos.x + bullet.range
		|| Direction::LEFT == bullet.direction && bullet.pos.x <= bullet.startPos.x - bullet.range;
}

/// <summary>
/// 当たり屋と当てられ屋の位置関係を判定します
/// </summary>
/// <param name="hittingX">当たり屋</param>
/// <param name="hitX">当てられ屋</param>
/// <returns>当たり屋が右側かどうか</returns>
bool BulletManager::IsHitRight(double hittingX, double hitX)
{
	return hittingX > hitX; // hittingXは当たり屋のほう、hitXは当てられたほう
}

void BulletManager::LerpForBulletEndPos(Bullet& bullet, Player& player) {
	double speedCollected = Direction::RIGHT == bullet.direction
			? ((bullet.endPos.x - bullet.startPos.x) / 50)
			: ((bullet.startPos.x - bullet.endPos.x) / 50);
	const double t = Min(bullet.bulletSw.sF() / speedCollected, 1.0);
	const double fixedX = Direction::RIGHT == bullet.direction ? player.pos.x - 10 : player.pos.x + 10;
	player.beforePos = Vec2(fixedX, player.pos.y);
	player.pos = player.pos.lerp(Vec2(bullet.endPos.x, bullet.endPos.y), EaseOutQuint(t));
	if (IsDistination(bullet, player) || t >= 0.3) { // 0.3は滞在時間をカットしたいので。イージングの種類で変わる。
  		player.pos = bullet.endPos;
		player.groundY = bullet.endPos.y;
		player.waitFlag = false;
		player.time = 0.0; // 落下後の初期化処理
		bullet.isHit = false;
		bullet.bulletSw.reset();
		bullet.endPos = Vec2(0, 0);
		ClearBullet(bullet);
	}
}

bool BulletManager::IsDistination(Bullet bullet, Player player) {
	return  Direction::RIGHT == bullet.direction
		? player.pos.x + 0.1 >= bullet.endPos.x
		: player.pos.x - 0.1 <= bullet.endPos.x;
}

void BulletManager::ClearBullet(Bullet &bullet) {
	bullet.isExists = false;
	bullet.ClearPos();
}

void BulletManager::ClearBullet(Bullet &bullet, TimeManager& timeMngr) {
	bullet.isExists = false;
	bullet.ClearPos();
	timeMngr.bulletAttack1Cool.reset();
	timeMngr.bulletAttack3SpriteSw.reset();
	bullet.InitImageNumbers();
}

bool BulletManager::IsCollisionDetected(Bullet& bullet, Player& player, Array<MapTip> mapTips) {
	if (!bullet.isExists) {
		return false;
	}
	if (bullet.isHit) {
		return true;
	}
	if (bullet.pos.isZero()) {
		return false;
	}
	Vec2 screenOriginPosition(MapScreenHelper::ChangeWorldToScreenPos(player.pos));
	for (auto i : step(mapTips.size())) {
		RectF map(mapTips[i].detection);
		map = map.movedBy(-screenOriginPosition);
		if (bullet.hitBox.intersects(map)) {
			bullet.endPos = Vec2(bullet.pos.x, bullet.pos.y);
			bullet.isHit = true;
			return true;
		}
	}
	return false;
}
