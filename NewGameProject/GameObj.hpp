#pragma once
# include "Player.hpp"
# include "Enemy.hpp"
# include "BulletManager.hpp"
# include "MapCreator.hpp"
# include "Bullet.hpp"
# include "BulletData.hpp"
# include "SpriteImageMetaData.hpp"

class GameObj {
public:
	Player player;
	Texture warpBulletImage;
	Texture bulletImage;
	Array<Enemy> enemies;
	Array<Bullet> bullets;
	Array<MapTip> mapTips;
	Font font;
	Font smallFont;
	GameObj();
	void DisplayAnimeTypeForDebug(Vec2 displayPos);
	void Init(Player& player);
	void CreateEnemies();
	void SelectEnemyImage(Enemy& enemy, double w, double h, Texture eye, Texture hamburg);
	void BulletAction(Player& _player, GameObj& gameObj, TimeManager& timeMngr);
};