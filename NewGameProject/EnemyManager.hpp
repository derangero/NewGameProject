#pragma once
#include "GameObj.hpp"
#include "EnemyAnimeManager.hpp"
#include "Player.hpp"

class EnemyManager {
public:
	static void Action(GameObj &objManager);
	static void Draw(EnemyAnimeManager &eaManager, GameObj& gameObj, Player player);
};