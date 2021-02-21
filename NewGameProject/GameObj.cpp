# include"GameObj.hpp"

GameObj::GameObj(MapCreator& mapCreator, std::unordered_map<int, SpriteImageMetaData> spriteImageMetaDataMap) :
	mapCreator(mapCreator)
{
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
	warpBullet.bulletName = BulletName::WARP;
	warpBullet.direction = player.rightwardFlag ? Direction::RIGHT : Direction::LEFT;
	warpBullet.image = warpBulletImage(188, 64, 16, 16);
	warpBullet.velocity = WIRE_BULLET_VELOCITY;
	warpBullet.range = WIRE_BULLET_RANGE;
	warpBullet.damage = 1;
	for (int i : step(3)) {
		Bullet attack1Bullet;
		attack1Bullet.owner = U"player";
		attack1Bullet.bulletName = BulletName::ATTACK_1;
		attack1Bullet.direction = player.rightwardFlag ? Direction::RIGHT : Direction::LEFT;
		attack1Bullet.image = player.allImage(327, 623, 6, 3).scaled(3.0);
		attack1Bullet.velocity = ATTACK1_BULLET_VELOCITY;
		attack1Bullet.range = ATTACK1_BULLET_RANGE;
		attack1Bullet.damage = 1;
		bullets << attack1Bullet;
	}
	SpriteImageMetaData icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::SHOOT_ATTACK_3]);
	TextureRegion bulletImage = SpriteUtil::ExtractionImage(player.allImage, icData, player.attackNumbers[3]);
	for (int i : step(2)) {
		Bullet attack3Bullet;
		attack3Bullet.owner = U"player";
		attack3Bullet.bulletName = BulletName::ATTACK_3;
		attack3Bullet.direction = player.rightwardFlag ? Direction::RIGHT : Direction::LEFT;
		attack3Bullet.velocity = ATTACK1_BULLET_VELOCITY;
		attack3Bullet.range = ATTACK1_BULLET_RANGE;
		attack3Bullet.damage = 2;
		attack3Bullet.image = bulletImage.scaled(0.7);
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
			int charaType = static_cast<int>(enemy.charaType);
			font(Format(enemy.name, U"_type: ", charaType)).draw(displayPos.movedBy(-100, 90));
		}
		if (enemy.name == U"skull") {
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
			String actionType = U"";
			if (enemy.actionState == CharaActionState::WAIT) {
				actionType = U"WAIT";
			}
			else if (enemy.actionState == CharaActionState::ATTACK) {
				actionType = U"ATTACK";
			}
			else if (enemy.actionState == CharaActionState::CHASE) {
				actionType = U"CHASE";
			}
			else if (enemy.actionState == CharaActionState::DOWN) {
				actionType = U"DOWN";
			}
			else if (enemy.actionState == CharaActionState::MOVE) {
				actionType = U"MOVE";
			}
			else if (enemy.actionState == CharaActionState::ON_DAMAGE) {
				actionType = U"ON_DAMAGE";
			}
			else if (enemy.actionState == CharaActionState::ON_DAMAGE_INVISIBLE) {
				actionType = U"ON_DAMAGE_INVISIBLE";
			}
			String attackState = U"";
			if (enemy.attackState == CharaAttackState::CHASE_ATTACK_A) {
				attackState = U"CHASE_ATTACK_A";
			}
			else if (enemy.attackState == CharaAttackState::NONE) {
				attackState = U"NONE";
			}
			else if (enemy.attackState == CharaAttackState::ATTACK_A) {
				actionType = U"ATTACK_A";
			}
			else if (enemy.attackState == CharaAttackState::ATTACK_B) {
				actionType = U"ATTACK_B";
			}
			font(Format(enemy.name, U"_ActionType: ", actionType)).draw(displayPos.movedBy(-100, 30));
			font(Format(enemy.name, U"_AnimeType: ", animeType)).draw(displayPos.movedBy(-100, 50));
			font(Format(enemy.name, U"_AttackState: ", attackState)).draw(displayPos.movedBy(-100, 10));
			font(Format(enemy.name, U"_IsExists: ", enemy.isExists)).draw(displayPos.movedBy(-100, 70));
			if (!enemy.isExists) {
				int a = 0;
			}
		}
	}
}

void GameObj::Init(Player &player)
{
	this->player = player;
	for (Bullet &bullet : bullets) {
		if (bullet.owner == U"player" && !bullet.isExists) {
			bullet.pos = bullet.startPos = player.pos; // 値が変わるか？
			bullet.direction = player.rightwardFlag ? Direction::RIGHT : Direction::LEFT;
		}
	}
	player.Init(font);
	Enemy::InitEnemies(enemies, player.pos, player.hitBox, font);
	this->font = font;
	if (player.crouchFlag) {
		player.UpdateDetection(0, -PLAYER_FIXED_CROUCH_H, PLAYER_DETEC_W, PLAYER_CROUCH_DETEC_H);
	}
	// 鍵の出現判定
	bool isExists = false;
	if (mapCreator.getAllCoin) {
		for (Enemy enemy : enemies) {
			if (enemy.isExists) {
				isExists = true;
			}
		}
		if (!isExists) {
			mapCreator.keyAppearance = true;
		}
	}
}

void GameObj::CreateEnemies()
{
	const XMLReader xml(MAP_XML_PATH);
	_ASSERT_EXPR(xml, L"Failed to load myGameTestMap.xml");
	Array<Enemy> enemies;
	Texture eye(U"image/enemy/eye.png");
	Texture hamburg(U"image/enemy/hamburg.png");
	Texture gob(U"image/enemy/gob.png");
	Texture skull(U"image/enemy/skull.png");
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
			enemy.allImage = SelectEnemyImage(enemy, w, h, eye, hamburg, gob, skull);
			enemy.pos = enemy.originPos = Vec2(x, y - 16);
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
					else if (elem4.attribute(U"name").value() == U"scoutingRange") {
						enemy.scoutingRange = Parse<int>(elem4.attribute(U"value").value());
					}
					else if (elem4.attribute(U"name").value() == U"closeScoutingRange") {
						enemy.closeScoutingRange = Parse<int>(elem4.attribute(U"value").value());
					}
					else if (elem4.attribute(U"name").value() == U"velocity") {
						enemy.velocity = Parse<double>(elem4.attribute(U"value").value());
					}
					else if (elem4.attribute(U"name").value() == U"chaseVelocity") {
						enemy.chaseVelocity = Parse<double>(elem4.attribute(U"value").value());
					}
					else if (elem4.attribute(U"name").value() == U"randomJumpChance") {
						double randomJumpChance = Parse<double>(elem4.attribute(U"value").value());
						// 設定値は整数を想定(10 / 100 = 0.1 = 10%)
						enemy.randomJumpChance = randomJumpChance / 100;
					}
					else if (elem4.attribute(U"name").value() == U"animeType") {
						animeType = Parse<int>(elem4.attribute(U"value").value());
						enemy.animeType = static_cast<EnemyAnimeType>(animeType);
					}
					else if (elem4.attribute(U"name").value() == U"armorClass") {
						String armorClass = elem4.attribute(U"value").value();
						enemy.armorClass = ConvertArmorClassNameToEnum(armorClass);
					}
					else if (elem4.attribute(U"name").value() == U"actionState") {
						int actionState = Parse<int>(elem4.attribute(U"value").value());
						enemy.actionState = static_cast<CharaActionState>(actionState);
					}
					else if (elem4.attribute(U"name").value() == U"afterOnDamage") {
						int afterOnDamage = Parse<int>(elem4.attribute(U"value").value());
						enemy.afterOnDamage = static_cast<AfterOnDamage>(afterOnDamage);
					}
					else if (elem4.attribute(U"name").value() == U"attackType") {
						String attackType = elem4.attribute(U"value").value();
						transform(attackType.begin(), attackType.end(), attackType.begin(), ::toupper);
						if (attackType == U"NONE") {
							enemy.attackType = EnemyAttackType::NONE;
						}
						else if (attackType == U"LONG_RANGE") {
							enemy.attackType = EnemyAttackType::LONG_RANGE;
						}
						else if (attackType == U"CLOSE_RANGE") {
							enemy.attackType = EnemyAttackType::CLOSE_RANGE;
						}
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

ArmorClass GameObj::ConvertArmorClassNameToEnum(String armorClass)
{
	if (U"SUPER" == armorClass) {
		return ArmorClass::SUPER;
	} else if (U"HYPER" == armorClass) {
		return ArmorClass::HYPER;
	}
	return ArmorClass::NORMAL;
};

Texture GameObj::SelectEnemyImage(Enemy &enemy, double w, double h, Texture eye, Texture hamburg, Texture gob, Texture skull)
{
	_ASSERT_EXPR(!eye.isEmpty() && !hamburg.isEmpty() && !gob.isEmpty() && !skull.isEmpty(), L"SelectEnemyImage::Texture is Empty.");
	EnemyType enemyType = static_cast<EnemyType>(enemy.type);
	switch (enemyType) {
	case EnemyType::EYE:
		return eye;
	case EnemyType::HAMBURG:
		return hamburg;
	case EnemyType::GOB:
		return gob;
	case EnemyType::SKULL:
		return skull;
	}
}

void GameObj::BulletAction(Player& _player, GameObj &gameObj, TimeManager& timeMngr)
{
	//TODO: 一応プレイヤー用なのでメソッド名を変えるとかしたい
	BulletManager::ControlWarpBullet(gameObj.bullets, _player, mapCreator.mapTips);
	BulletManager::ControlBullet(gameObj.bullets, _player, mapCreator.mapTips, timeMngr);
	BulletManager::BulletHit(_player, gameObj.enemies, gameObj.bullets, mapCreator.mapTips, gameObj.font, timeMngr);
}
