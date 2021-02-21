#pragma once
#include "Siv3D.hpp"
#include "Player.hpp"
#include "PlayerAnimeManager.hpp"
#include "GameEffectManager.hpp"
class GameEndManager
{
public:
    double bGroundChangeTime;
    double gameOverTime;
    Font gameOverTitleFont;
    Font gameOverMiddleFont;
    String gameClearStr;
    String gameOverStr;
    String continueStr;
    String titleStr;
public:
    GameEndManager();
    void DrawScene(Player& player, PlayerAnimeManager& playerAnimeManager, TimeManager& timeManager,
        Effect &effect, GameEffectManager &effectManager);
    void DrawMissScene(Player &player, PlayerAnimeManager& playerAnimeManager, TimeManager& timeManager,
        Effect &effect);
    void DrawFinishScene(Player &player, PlayerAnimeManager& playerAnimeManager, TimeManager& timeManager,
        Effect &effect, GameEffectManager &effectManager);
};