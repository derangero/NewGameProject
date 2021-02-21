#include "BulletManager.hpp"
# include "TimeManager.hpp"

BulletManager::BulletManager(Bullet bullet)
{
}

void BulletManager::ControlWarpBullet(Array<Bullet>& bullets, Player& player, Array<MapTip>& mapTips)
{
	for (Bullet& bullet : bullets) {
		if (bullet.bulletName != BulletName::WARP) {
			continue;
		}
		// TODO:Debug
		player.font(U"playerWarpBulletX:", bullet.pos.x).draw(0, 150);
		player.font(U"playerWarpBulletY:", bullet.pos.y).draw(0, 170);
		player.font(U"isExists:", bullet.isExists).draw(0, 190);

		// TODO:�����蔻�蓙�̋������s�R�Ȃ̂ōl���邱��
		if (IsCollisionDetected(bullet, player, mapTips)) {
			player.waitFlag = true; // ���`��Ԓ��͑�����󂯕t���Ȃ�
			if (!bullet.bulletSw.isRunning()) {
				bullet.bulletSw.restart();
			}
			LerpForBulletEndPos(bullet, player);
			bullet.hitBox = RectF();
		}
		else {
			if (BulletMode::WARP == player.bulletMode && !bullet.isExists) {
				bullet.isExists = true;
			}
			if (bullet.isExists) {
				bullet.Update(player.pos, player.hitBox);
				bullet.Draw(player.pos, player.hitBox);
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

void BulletManager::ControlBullet(Array<Bullet>& bullets, Player& player, Array<MapTip>& mapTips, TimeManager& timeMngr)
{
	// �I�u�W�F�N�g�̃��C�t�T�C�N�����Ǘ�
	for (Bullet& bullet : bullets) {
		// Enemy�̃o���b�g������̂�
		if (bullet.owner != U"player") {
			continue;
		}
		// �o���b�g���K�v�ȏꍇ�A���݃t���O��True�ɂ���GET
		if (!bullet.isExists) {
			if (player.isShooted && player.bulletName == bullet.bulletName) {
				bullet.isExists = true;
				player.isShooted = false;
				break;
			} else {
				ClearBullet(bullet, player, timeMngr);
			}
		}
	}
	// �{����
	for (Bullet& bullet : bullets) {
		if (bullet.owner != U"player" || bullet.bulletName == BulletName::WARP) {
			continue;
		}
		if (bullet.isExists) {
			if (IsCollisionDetected(bullet, player, mapTips) || IsOutOfFrame(bullet, player)) {
				ClearBullet(bullet, player, timeMngr);
				bullet.isHit = false;
				return;
			}
			bullet.Update(player.pos, player.hitBox);
			bullet.Draw(player.pos, player.hitBox, bullet.bulletName, player.allImage,
				player.spriteImageMetaDataMap, timeMngr);

			if (IsOutRange(bullet)) {
				// TODO:��U�ۗ�
				//ClearBullet(bullet, timeMngr);
			}
		}
	}
}

bool BulletManager::IsOutOfFrame(Bullet &bullet, Player &player)
{
	if (Direction::RIGHT == bullet.direction) {
		if (player.IsMovingRightInFrame(player.pos)) { // �J�������ړ����Ă��邩�ǂ���
			// �J�������ړ����Ă�����A�ړ�����g�[�̈ʒu�ɉ�����
			return bullet.pos.x > (Scene::Size().x + (player.pos.x - PLAYER_STAND_POS.x));
		}
		else if (PLAYER_STAND_POS.x >= player.pos.x) {
			return bullet.pos.x > Scene::Size().x;
		}
		else if (PLAYER_RIGHT_END_POS.x <= player.pos.x) {
			return bullet.pos.x > 1200; // TODO:�ۗ�
		}
	}
	else if (Direction::LEFT == bullet.direction) {
		if (player.IsMovingRightInFrame(player.pos)) {
			return bullet.pos.x < (player.pos.x - PLAYER_STAND_POS.x);
		}
		else if (PLAYER_STAND_POS.x >= player.pos.x) { // ���[�A�J�����Œ�
			return bullet.pos.x < 0.0;
		}
		else if (player.pos.x >= PLAYER_RIGHT_END_POS.x) { // �E�[�A�J�����Œ�
			return bullet.pos.x < (800 - (player.pos.x - PLAYER_RIGHT_END_POS.x));
		}
	}
	return false;
}

void BulletManager::BulletHit(Player& player, Array<Enemy>& enemies, Array<Bullet>& bullets, Array<MapTip>& mapTips, Font font, TimeManager& timeMngr)
{
	for (Bullet& playerBullet : bullets) {
		if (playerBullet.owner != U"player") {
			continue;
		}
		#ifdef _DEBUG
		if (playerBullet.isExists) {
			playerBullet.hitBox.draw(ColorF(1.0, 1.0, 1.0, 0.5));
		}
		#endif _DEBUG
		for (Enemy& enemy : enemies) {
			//TODO: !enemy.isInvisible ����ȏ������l���ł���
			if (enemy.hitBox.intersects(playerBullet.hitBox) && playerBullet.isExists) {
				enemy.OnDamage(playerBullet.damage, false);
				player.isAttack1 = true;
				playerBullet.isExists = false;
			}
		}
	}
	for (Bullet& enemyBullet : bullets) {
		if (enemyBullet.owner == U"player") {
			continue;
		}
		if (enemyBullet.hitBox.intersects(player.hitBox)) {
			bool isRightHit = IsHitRight(enemyBullet.hitBox.center().x, player.hitBox.center().x);
			player.OnDamage(enemyBullet.damage, isRightHit);
		}
	}
}

bool BulletManager::IsOutRange(Bullet bullet) {
	return Direction::RIGHT == bullet.direction && bullet.pos.x >= bullet.startPos.x + bullet.range
		|| Direction::LEFT == bullet.direction && bullet.pos.x <= bullet.startPos.x - bullet.range;
}

/// <summary>
/// �����艮�Ɠ��Ă�ꉮ�̈ʒu�֌W�𔻒肵�܂�
/// </summary>
/// <param name="hittingX">�����艮</param>
/// <param name="hitX">���Ă�ꉮ</param>
/// <returns>�����艮���E�����ǂ���</returns>
bool BulletManager::IsHitRight(double hittingX, double hitX)
{
	return hittingX > hitX; // hittingX�͓����艮�̂ق��AhitX�͓��Ă�ꂽ�ق�
}

void BulletManager::LerpForBulletEndPos(Bullet& bullet, Player& player) {
	double speedCollected = Direction::RIGHT == bullet.direction
			? ((bullet.endPos.x - bullet.startPos.x) / 50)
			: ((bullet.startPos.x - bullet.endPos.x) / 50);
	const double t = Min(bullet.bulletSw.sF() / speedCollected, 1.0);
	const double fixedX = Direction::RIGHT == bullet.direction ? player.pos.x - 10 : player.pos.x + 10;
	player.beforePos = Vec2(fixedX, player.pos.y);
	player.pos = player.pos.lerp(Vec2(bullet.endPos.x, bullet.endPos.y), EaseOutQuint(t));
	if (IsDistination(bullet, player) || t >= 0.3) { // 0.3�͑؍ݎ��Ԃ��J�b�g�������̂ŁB�C�[�W���O�̎�ނŕς��B
  		player.pos = bullet.endPos;
		player.ground = bullet.endPos.y;
		player.waitFlag = false;
		player.time = 0.0; // ������̏���������
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

void BulletManager::ClearBullet(Bullet &bullet, Player &player, TimeManager& timeMngr) {
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
	for (auto mapTip : mapTips) {
		RectF map(mapTip.collision);
		map = map.movedBy(-screenOriginPosition);
		if (bullet.hitBox.intersects(map)) {
			bullet.endPos = Vec2(bullet.pos.x, bullet.pos.y);
			bullet.isHit = true;
			return true;
		}
	}
	return false;
}
