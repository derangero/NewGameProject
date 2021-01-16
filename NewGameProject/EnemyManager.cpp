#include "EnemyManager.hpp"

void EnemyManager::Action(GameObj& gameObj)
{
    for (Enemy& enemy : gameObj.enemies) {
        enemy.EnemyAction(gameObj.bullets, gameObj.font);
    }
}

// EnemyAnimeManager &eaManager 参照をとると、enemiesが値渡しになる？
void EnemyManager::Draw(EnemyAnimeManager &eaManager, GameObj& gameObj, Player player)
{
    eaManager.Draw(gameObj.enemies, player, gameObj.smallFont);
}
