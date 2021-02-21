#pragma once
# include <Siv3D.hpp>
# include "GameEffect.hpp"
class GameEffectManager
{
public:
	Texture firework_1;
	Texture deco_1;
	Array<GameEffect> gameEffects;
public:
	GameEffectManager();
	void DrawStart();
};