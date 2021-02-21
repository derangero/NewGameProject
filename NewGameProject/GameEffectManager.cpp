#include "GameEffectManager.hpp"

GameEffectManager::GameEffectManager() :
	firework_1(Texture(U"image/effect/firework.png")),
	deco_1(Texture(U"image/effect/deco1.png"))
{
    EffectMetaData firework1MetaData(U"firework1", firework_1, PROP_STAR_BURST_1);
    EffectMetaData firework2MetaData(U"firework2", firework_1, PROP_STAR_BURST_2);
    EffectMetaData firework3MetaData(U"firework3", firework_1, PROP_STAR_BURST_3);
    gameEffects.push_back(GameEffect(firework1MetaData));
    gameEffects.push_back(GameEffect(firework2MetaData));
    gameEffects.push_back(GameEffect(firework3MetaData));
    EffectMetaData deco1MetaData(U"deco1", deco_1, PROP_DECO_1);
    EffectMetaData deco2MetaData(U"deco2", deco_1, PROP_DECO_2);
    gameEffects.push_back(GameEffect(deco1MetaData));
    gameEffects.push_back(GameEffect(deco2MetaData));
}

void GameEffectManager::DrawStart()
{
    for (GameEffect& gameEffect : gameEffects) {
        if (U"firework1" == gameEffect.name) {
            gameEffect.StartDraw(Scene::CenterF());
        }
        else if (U"firework2" == gameEffect.name) {
            gameEffect.StartDraw(Vec2(100, 100));
        }
        else if (U"firework3" == gameEffect.name) {
            gameEffect.StartDraw(Vec2(700, 200));
        }
        else if (U"deco1" == gameEffect.name) {
            gameEffect.StartDraw(Vec2(100, 500));
        }
        else if (U"deco2" == gameEffect.name) {
            gameEffect.StartDraw(Vec2(500, 400));
        }
    }
}
