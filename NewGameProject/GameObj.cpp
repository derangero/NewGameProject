# include"GameObj.hpp"

GameObj::GameObj()
{
	mapTips = MapCreator::GetMapTips(Texture(U"map/base.png"));
	warpBulletImage = Texture(U"image/stg0729.png");
	bulletImage = Texture(U"image/stg0729.png");
	CreateEnemies();
	JSONReader json(U"ini/enemyBullet.json");
	std::unordered_map<EnemyType, BulletData> map;
	for (const auto j2 : json.arrayView()) {
		BulletData bulletData;
		bulletData.type = j2[U"type"].get<int>();
		bulletData.damage = j2[U"damage"].get<int>();
		bulletData.hitBox_w = j2[U"hitBox_w"].get<int>();
		bulletData.hitBox_h = j2[U"hitBox_h"].get<int>();
		bulletData.range = j2[U"range"].get<double>();
		bulletData.velocity = j2[U"velocity"].get<double>();
		bulletData.generationCount = j2[U"generationCount"].get<int>();
		EnemyType enemyType = static_cast<EnemyType>(bulletData.type);
		map[enemyType] = bulletData;

	}
	// エネミーの射撃オブジェクト準備
	for (Enemy& enemy : enemies) {
		EnemyType enemyType = static_cast<EnemyType>(enemy.type);
		BulletData bulletData(map[enemyType]);
		for (auto i : step(bulletData.generationCount)) {
			Bullet bullet;
			bullet.pos = Vec2::Zero();
			bullet.owner = enemy.name;
			bullet.velocity = bulletData.velocity;
			bullet.damage = bulletData.damage;
			bullet.range = bulletData.range;
			bullet.hitBox = RectF(bulletData.hitBox_w, bulletData.hitBox_h);
			bullet.spriteImage = enemy.allImage;
			bullets << bullet;
		}
	}
	// プレイヤーの射撃オブジェクト準備
	Bullet warpBullet;
	warpBullet.owner = U"player";
	warpBullet.name = BulletName::WARP;
	warpBullet.direction = player.rightwardFlag ? Direction::RIGHT : Direction::LEFT;
	warpBullet.image = warpBulletImage(188, 64, 16, 16);
	warpBullet.velocity = WIRE_BULLET_VELOCITY;
	warpBullet.range = WIRE_BULLET_RANGE;
	warpBullet.damage = 1;
	for (int i : step(3)) {
		Bullet attack1Bullet;
		attack1Bullet.owner = U"player";
		attack1Bullet.name = BulletName::ATTACK_1;
		attack1Bullet.direction = player.rightwardFlag ? Direction::RIGHT : Direction::LEFT;
		attack1Bullet.image = player.allImage(327, 623, 6, 3).scaled(3.0);
		attack1Bullet.velocity = ATTACK1_BULLET_VELOCITY;
		attack1Bullet.range = ATTACK1_BULLET_RANGE;
		attack1Bullet.damage = 1;
		bullets << attack1Bullet;
	}
	for (int i : step(3)) {
		Bullet attack3Bullet;
		attack3Bullet.owner = U"player";
		attack3Bullet.name = BulletName::ATTACK_3;
		attack3Bullet.direction = player.rightwardFlag ? Direction::RIGHT : Direction::LEFT;
		//attack3Bullet.image = player.image(327, 623, 6, 3).scaled(3.0);
		attack3Bullet.velocity = ATTACK1_BULLET_VELOCITY;
		attack3Bullet.range = ATTACK1_BULLET_RANGE;
		attack3Bullet.damage = 2;
		bullets << attack3Bullet;
	}

	bullets << warpBullet;
	this->font = Font(20);
	this->smallFont = Font(8);
}

void GameObj::DisplayAnimeTypeForDebug(Vec2 displayPos)
{
	for (Enemy enemy : enemies) {
		if (enemy.name == U"hamburg") {
			String animeType = U"";
			if (enemy.animeType == EnemyAnimeType::NONE) {
				animeType = U"NONE";
			}
			else if (enemy.animeType == EnemyAnimeType::WAIT) {
				animeType = U"WAIT";
			}
			else if (enemy.animeType == EnemyAnimeType::WALK) {
				animeType = U"WALK";
			}
			else if (enemy.animeType == EnemyAnimeType::ON_DAMAGE) {
				animeType = U"ON_DAMAGE";
			}
			else if (enemy.animeType == EnemyAnimeType::DOWN) {
				animeType = U"DOWN";
			}
			else if (enemy.animeType == EnemyAnimeType::ATTACK1) {
				animeType = U"ATTACK1";
			}
			else if (enemy.animeType == EnemyAnimeType::ATTACK2) {
				animeType = U"ATTACK2";
			}
			font(Format(U"AnimeType: ", animeType)).draw(displayPos);
		}
	}
}

void GameObj::Init(Player& player)
{
	this->player = player;
	for (Bullet &bullet : bullets) {
		if (bullet.owner == U"player" && !bullet.isExists) {
			bullet.pos = bullet.startPos = player.pos; // 値が変わるか？
			bullet.direction = player.rightwardFlag ? Direction::RIGHT : Direction::LEFT;
		}
	}
	player.Init(font);
	Enemy::InitEnemies(enemies, player.pos, player.detection, font);
	this->font = font;
}

void GameObj::CreateEnemies()
{
	const XMLReader xml(MAP_XML_PATH);
	if (!xml)
	{
		throw Error(U"Failed to load `myGameTestMap.xml`");
	}
	Array<Enemy> enemies;
	Texture eye(U"image/enemy/eye.png");
	Texture hamburg(U"image/enemy/hamburg.png");
	Texture gob(U"image/enemy/hamburg.png");
	for (auto elem = xml.firstChild(); elem; elem = elem.nextSibling())
	{
		// エネミーオブジェクトを利用する場合、ENEMIY_NAMESにプロパティ名を設定する
		if (elem.name() != U"objectgroup" || !ENEMY_NAMES.includes(elem.attribute(U"name").value())) {
			continue;
		}
		for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
		{
			double w = Parse<double>(elem2.attribute(U"width").value());
			double h = Parse<double>(elem2.attribute(U"height").value());
			double x = Parse<double>(elem2.attribute(U"x").value());
			double y = Parse<double>(elem2.attribute(U"y").value());
			String name = elem2.attribute(U"name").value();
			String type = elem2.attribute(U"type").value();
			Enemy enemy;
			enemy.name = name;
			enemy.type = Parse<int>(type);
			SelectEnemyImage(enemy, w, h, eye, hamburg);
			enemy.pos = Vec2(x, y - 16);
			String jsonURI = U"ini/";
			JSONReader imageJson(jsonURI.append(enemy.name).append(U".json"));
			enemy.spriteImageMetaDataMap = SpriteUtil::GetEnemySpriteImageMetaDataMap(imageJson);
			int animeType = 0;
			for (auto elem3 = elem2.firstChild(); elem3; elem3 = elem3.nextSibling())
			{
				for (auto elem4 = elem3.firstChild(); elem4; elem4 = elem4.nextSibling())
				{
					if (elem4.attribute(U"name").value() == U"rightward") {
						enemy.rightwardFlag = Parse<bool>(elem4.attribute(U"value").value());
					}
					else if (elem4.attribute(U"name").value() == U"hp") {
						enemy.hp = Parse<int>(elem4.attribute(U"value").value());
					}
					else if (elem4.attribute(U"name").value() == U"moveAmt") {
						enemy.moveAmt = Parse<double>(elem4.attribute(U"value").value());
					}
					else if (elem4.attribute(U"name").value() == U"scoutingRangeMagnification") {
						enemy.scoutingMagnification = Parse<double>(elem4.attribute(U"value").value());
					}
					else if (elem4.attribute(U"name").value() == U"velocity") {
						enemy.velocity = Parse<double>(elem4.attribute(U"value").value());
					}
					else if (elem4.attribute(U"name").value() == U"animeType") {
						animeType = Parse<int>(elem4.attribute(U"value").value());
						enemy.animeType = static_cast<EnemyAnimeType>(animeType);
					}
					else if (elem4.attribute(U"name").value() == U"actionState") {
						int actionState = Parse<int>(elem4.attribute(U"value").value());
						enemy.actionState = static_cast<CharaActionState>(actionState);
					}
					else if (elem4.attribute(U"name").value() == U"afterOnDamage") {
						int afterOnDamage = Parse<int>(elem4.attribute(U"value").value());
						enemy.afterOnDamage = static_cast<AfterOnDamage>(afterOnDamage);
					}
				}
			}
			SpriteImageMetaData metaData = enemy.spriteImageMetaDataMap[animeType];
			Size size = metaData.sizes[enemy.imageNumber];
			double fixedX = enemy.pos.x - (size.x / 2);
			double fixedY = enemy.pos.y - (size.y / 2);
			enemy.hitBox = RectF(Vec2(fixedX, fixedY), size.x - RESIZED_ENEMY_HITBOXES.x, size.y - RESIZED_ENEMY_HITBOXES.x);
			enemies.push_back(enemy);
		}
	}
	this->enemies = enemies;
};

void GameObj::SelectEnemyImage(Enemy &enemy, double w, double h, Texture eye, Texture hamburg)
{
	EnemyType enemyType = static_cast<EnemyType>(enemy.type);
	switch (enemyType) {
	case EnemyType::EYE:
		enemy.allImage = eye;
		//enemy.image = enemy.allImage(0 + 57, 61, Vec2(w, h));
		break;
	case EnemyType::HAMBURG:
		enemy.allImage = hamburg;
		//enemy.image = enemy.allImage(0 + 64, 67, Vec2(w, h));
		break;
	}
}

void GameObj::BulletAction(Player& _player, GameObj &gameObj, TimeManager& timeMngr)
{
	//TODO: 一応プレイヤー用なのでメソッド名を変えるとかしたい
	BulletManager::ActionWarpBullet(gameObj.bullets, _player, mapTips);
	BulletManager::ActionBullet_1(gameObj.bullets, _player, mapTips, timeMngr);
	BulletManager::BulletHit(_player, gameObj.enemies, gameObj.bullets, mapTips, gameObj.font, timeMngr);
}
