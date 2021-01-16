# pragma once
# include "Player.hpp"
# include "Enemy.hpp"

class TimeManager;
class BulletManager {
public:
	BulletManager(Bullet bullet);
	static void ActionWarpBullet(Array<Bullet> &bullets, Player& player, Array<MapTip>& mapTips);
	static void ActionBullet_1(Array<Bullet> &bullets, Player& player, Array<MapTip>& mapTips, TimeManager& timeMngr);
	static void BulletHit(Player& player, Array<Enemy> &enemies, Array<Bullet> &bullets, Array<MapTip>& mapTips, Font font, TimeManager& timeMngr);
	static void LerpForBulletEndPos(Bullet& bullet, Player& player);
	static bool IsDistination(Bullet bullet, Player player);
	static void ClearBullet(Bullet & bullet);
	static void ClearBullet(Bullet & bullet, TimeManager& timeMngr);
	static bool IsCollisionDetected(Bullet & bullet, Player& player, Array<MapTip> mapTips);
	static bool IsOutRange(Bullet bullet);
	static bool IsHitRight(double hittingX, double hitX);
};