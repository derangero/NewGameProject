#include "GameEndManager.hpp"

GameEndManager::GameEndManager() :
    bGroundChangeTime(0.0),
    gameOverTime(0.0),
    gameOverTitleFont(Font(60, U"font/yurumoji.ttf")),
    gameOverMiddleFont(Font(40, U"font/yurumoji.ttf")),
    gameClearStr(U"GAME_CLEAR!"),
    gameOverStr(U"GAME_OVER..."),
    continueStr(U"CONTINUE"),
    titleStr(U"TITLE")
{}

void GameEndManager::DrawScene(Player & player, PlayerAnimeManager & playerAnimeManager, TimeManager & timeManager, Effect & effect,
    GameEffectManager &effectManager)
{
    DrawMissScene(player, playerAnimeManager, timeManager, effect);
    DrawFinishScene(player, playerAnimeManager, timeManager, effect, effectManager);
}

void GameEndManager::DrawMissScene(Player &player, PlayerAnimeManager &playerAnimeManager, TimeManager &timeManager,
    Effect &effect)
{
    if ((player.isExists && !player.IsFallOff()) || player.gameFinished) {
        return;
    }
    bGroundChangeTime += Scene::DeltaTime() * 0.5;
    Rect(0, 0, 800, 600).draw(ColorF(1.0, Min(bGroundChangeTime, 1.0))); // 0.1`1.0
    // “|‚ê‚½‚çƒLƒƒƒ‰‚ÌƒŒƒCƒ„[‚ð‘O–Ê‚É
    playerAnimeManager.Draw(player, timeManager, effect);
    if (bGroundChangeTime >= 0.5) {
        gameOverTime += Scene::DeltaTime() * 5.0;
        const size_t length = static_cast<size_t>(gameOverTime);
        Point pt = Scene::Center().movedBy(-150, -100);
        gameOverTitleFont(gameOverStr.substr(0, length)).draw(pt, Palette::Black);
        if (gameOverTime > gameOverStr.size()) {
            if (gameOverMiddleFont(continueStr).draw(pt.movedBy(30, 100), Palette::Black).mouseOver()) {
                Line(pt.movedBy(30, 140), pt.movedBy(225, 135)).draw(4, Palette::Black);
            }
            if (gameOverMiddleFont(titleStr).draw(pt.movedBy(30, 140), Palette::Black).mouseOver()) {
                Line(pt.movedBy(30, 180), pt.movedBy(145, 185)).draw(4, Palette::Black);
            }
        }
    }
}

void GameEndManager::DrawFinishScene(Player& player, PlayerAnimeManager& playerAnimeManager, TimeManager& timeManager, Effect& effect,
    GameEffectManager &effectManager)
{
    if (!player.gameFinished) {
        return;
    }
    Point pt = Scene::Center().movedBy(-150, -100);
    gameOverTitleFont(gameClearStr).draw(pt, Palette::Black);
    effectManager.DrawStart();
    player.Init(gameOverTitleFont);
    player.waitFlag = true;
}
