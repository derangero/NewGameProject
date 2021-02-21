#include "EnemyManager.hpp"

void EnemyManager::Action(GameObj& gameObj, Player &player)
{
    for (Enemy& enemy : gameObj.enemies) {
        enemy.EnemyAction(gameObj.bullets, gameObj.font);
        CollideToPlayer(player, enemy);
    }
}

// EnemyAnimeManager &eaManager 参照をとると、enemiesが値渡しになる？
void EnemyManager::Draw(EnemyAnimeManager &enemyAnimeManager, GameObj& gameObj, Player player)
{
    enemyAnimeManager.Draw(gameObj.enemies, player, gameObj.smallFont);
}

void EnemyManager::CollideToPlayer(Player &player, Enemy &enemy)
{
    if (enemy.hitBox.intersects(player.hitBox)) {
        bool isRightHit = IsHitRight(enemy.hitBox.x, player.hitBox.center().x);
        player.OnDamage(ENEMY_HITBOX_DAMAGE, isRightHit);
    }
}

bool EnemyManager::IsHitRight(double hittingX, double hitX)
{
    return hittingX > hitX; // hittingXは当たり屋のほう、hitXは当てられたほう
}
