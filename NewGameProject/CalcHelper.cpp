#include "CalcHelper.hpp"

double CalcHelper::CalcGravity(double time)
{
	return (0.5 * 0.3 * time * time);
}

double CalcHelper::CalcJumpY(Player player, TimeManager timeManager)
{
	double time = player.time;
	double gra = CalcGravity(time);
	return player.groundY - (1.0 - pow(1.0 - sin(90_deg * time - gra), JUMP_DESTORTION)) * PLAYER_JUMP_HEIGHT;
}

double CalcHelper::CalcJumpY(Player player, TimeManager timeManager, double &newTime)
{
	double gra = CalcGravity(player.time);
	return (player.groundY - (1.0 - pow(1.0 - sin(90_deg * newTime - gra), JUMP_DESTORTION)) * (player.groundY - player.pos.y));
}
