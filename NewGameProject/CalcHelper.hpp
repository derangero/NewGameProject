#pragma once
# include <Siv3D.hpp>
# include "TimeManager.hpp"
# include "Player.hpp"

static class CalcHelper
{
public:
	// 落下時の重量を計算します。
	static double CalcGravity(double time);
	// ジャンプ時のY軸を計算します。
	static double CalcJumpY(Player player, TimeManager timeManager);
	static double CalcJumpY(Player player, TimeManager timeManager, double& newTime);
	static double CalcJumpOnTrampoline(Player player, TimeManager timeManager);
};