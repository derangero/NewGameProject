#pragma once
# include "Player.hpp"
# include "MapScreenHelper.hpp"
# include "AnimationBean.hpp"

class EnemyAnimeManager {
public:
	Stopwatch sw;
	EnemyAnimeManager();
	void Draw(Array<Enemy> &enemies, Player player, Font font);
	double GetFlashPeriodic(Enemy enemy);
	static int Animate(AnimationBean &aniBean, Stopwatch& _sw);
};