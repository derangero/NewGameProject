#include "TimeManager.hpp"

TimeManager::TimeManager() : time(0.0), dashTime(0.0), afterImageInterval(true)
{
}

void TimeManager::Control(Player& player)
{
    Update();
    UpdateWhenOverTime(player);
}

void TimeManager::Update()
{
    if (bulletAttack1Cool.isRunning() && bulletAttack1Cool.sF() > 0.3) {
        bulletAttack1Cool.reset();
    }
}

void TimeManager::UpdateWhenOverTime(Player& player)
{
    if (player.waitFlag) {
        return;
    }
    UpdateByAttack1Wait(player);
    UpdateByAttack2Wait(player);
    UpdateByAttack3Wait(player);
    UpdateByBulletWarpWait(player);
}

void TimeManager::UpdateByAttack1Wait(Player& player) {
    if (bulletAttack1Wait.sF() > ATTACK1_SPRITE_WAIT) {
        player.attack1Number = 0;
        bulletAttack1Wait.reset();
    }
}

void TimeManager::UpdateByAttack2Wait(Player& player) {
    if (bulletAttack2Wait.sF() > ATTACK2_SPRITE_WAIT) {
        player.attack1Number = 0;
        bulletAttack2Wait.reset();
    }
}

void TimeManager::UpdateByAttack3Wait(Player& player) {
    if (bulletAttack3Wait.sF() > ATTACK3_SPRITE_WAIT) {
        player.attackNumbers[3] = 0;
        bulletAttack3Wait.reset();
    }
}

void TimeManager::UpdateByBulletWarpWait(Player& player) {
    if (bulletWarpWait.isRunning()
            && bulletWarpWait.sF() > BULLET_WARP_SPRITE_WAIT) {
        player.attack1Number = 0;
        bulletWarpWait.reset();
    }
}

bool TimeManager::IsOverWaitTime(TimeManager& timeManager, double time)
{
    if (timeManager.dashWaitSw.isRunning() && timeManager.dashWaitSw.sF() >= time) {
        timeManager.dashWaitSw.reset();
        return true;
    }
    return false;
}