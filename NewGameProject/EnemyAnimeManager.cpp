#include "EnemyAnimeManager.hpp"

EnemyAnimeManager::EnemyAnimeManager()
{
}

void EnemyAnimeManager::Draw(Array<Enemy> &enemies, Player player, Font font)
{
    for (Enemy &enemy : enemies) {
        if (!enemy.isExists) {
            continue;
        }
        SpriteImageMetaData imageMetaData(enemy.spriteImageMetaDataMap[static_cast<int>(enemy.animeType)]);
        AnimationBean aniBean = AnimationBean::InitAnimationBean(enemy, imageMetaData);
        Vec2 screenOriginPosition2(MapScreenHelper::ChangeWorldToScreenPos(enemy.pos));
        Vec2 enemyPos = MapScreenHelper::FixPositionFromPlayerPos(player.pos, enemy.pos.movedBy(0, -screenOriginPosition2.y));
        if (imageMetaData.vecs.size() <= enemy.imageNumber)
        {
            throw Error(U"エラー:SpriteUtil.cpp ExtractionImage vecs");
        }
        if (imageMetaData.sizes.size() <= enemy.imageNumber)
        {
            throw Error(U"エラー:SpriteUtil.cpp ExtractionImage sizes");
        }
        SpriteUtil::ExtractionImage(enemy.allImage, imageMetaData, enemy.imageNumber)
            .mirrored(!enemy.rightwardFlag)
            .drawAt(enemyPos, ColorF(1.0, 1.0, 1.0, GetFlashPeriodic(enemy)));
        font(enemy.hp).draw(enemyPos.movedBy(0, -20));
        
        enemy.imageNumber = Animate(aniBean, enemy.sw);
        if (enemy.imageNumber == 4) {
            int a = 0;
        }
    }
}

double EnemyAnimeManager::GetFlashPeriodic(Enemy enemy) {
    return enemy.actionState == CharaActionState::ON_DAMAGE || enemy.actionState == CharaActionState::DOWN
        ? Periodic::Square0_1(0.1s)
        : 1.0;
}
int EnemyAnimeManager::Animate(AnimationBean &aniBean, Stopwatch &_sw)
{
    int &imageNumber = aniBean.imageNumber;
    _sw.start();
    if (_sw.sF() >= aniBean.interval) {
        imageNumber += 1;
        _sw.reset();
        if (imageNumber > aniBean.maxImageNumber) {
            if (aniBean.endMode == AnimationEndMode::REPEAT) {
                imageNumber = 0;
            }
            else if (aniBean.endMode == AnimationEndMode::STOP) {
                imageNumber = aniBean.maxImageNumber;
            }
        }
    }
    return imageNumber;
}