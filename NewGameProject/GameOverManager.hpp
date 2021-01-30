#pragma once
#include "Siv3D.hpp"
#include "Player.hpp"
#include "PlayerAnimeManager.hpp"
class GameOverManager
{
public:
    double bGroundChangeTime;
    double gameOverTime;
    Font gameOverTitleFont;
    Font gameOverMiddleFont;
    String gameOverStr;
    String continueStr;
    String titleStr;
public:
    GameOverManager();
    void DrawScene(Player &player, PlayerAnimeManager& playerAnimeManager, TimeManager& timeManager,
        Effect& effect);
};