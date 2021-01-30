#pragma once
#include "GameObj.hpp"
#include "EnemyAnimeManager.hpp"
#include "Player.hpp"

class EnemyManager {
public:
	void Action(GameObj &objManager, Player& player);
	void Draw(EnemyAnimeManager &eaManager, GameObj& gameObj, Player player);
	void CollideToPlayer(Player &player, Enemy &enemy);
	bool IsHitRight(double hittingX, double hitX);
};