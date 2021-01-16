#include "EnemyManager.hpp"

void EnemyManager::Action(GameObj& gameObj)
{
    for (Enemy& enemy : gameObj.enemies) {
        enemy.EnemyAction(gameObj.bullets, gameObj.font);
    }
}

// EnemyAnimeManager &eaManager �Q�Ƃ��Ƃ�ƁAenemies���l�n���ɂȂ�H
void EnemyManager::Draw(EnemyAnimeManager &eaManager, GameObj& gameObj, Player player)
{
    eaManager.Draw(gameObj.enemies, player, gameObj.smallFont);
}
