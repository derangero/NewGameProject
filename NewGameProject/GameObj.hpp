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
	Font font;
	Font smallFont;
	MapCreator &mapCreator;
	GameObj(MapCreator &mapCreator, std::unordered_map<int, SpriteImageMetaData> spriteImageMetaDataMap);
	void DisplayAnimeTypeForDebug(Vec2 displayPos);
	void Init(Player& player);
	void CreateEnemies();
	Texture SelectEnemyImage(Enemy& enemy, double w, double h, Texture eye, Texture hamburg, Texture gob, Texture skull);
	void BulletAction(Player& _player, GameObj& gameObj, TimeManager& timeMngr);
};