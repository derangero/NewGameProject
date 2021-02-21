#pragma once
# include <Siv3D.hpp>
# include "TimeManager.hpp"
# include "Player.hpp"

static class CalcHelper
{
public:
	// �������̏d�ʂ��v�Z���܂��B
	static double CalcGravity(double time);
	// �W�����v����Y�����v�Z���܂��B
	static double CalcJumpY(Player player, TimeManager timeManager);
	static double CalcJumpY(Player player, TimeManager timeManager, double& newTime);
	static double CalcJumpOnTrampoline(Player player, TimeManager timeManager);
};