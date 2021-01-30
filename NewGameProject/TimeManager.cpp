#include "TimeManager.hpp"

TimeManager::TimeManager() : time(0.0), dashTime(0.0), afterImageInterval(true)
{
}

void TimeManager::Control(Player& player)
{
    Update();
    ManageCoolTime(player);
}

void TimeManager::Update()
{
    if (bulletAttack1Cool.isRunning() && bulletAttack1Cool.sF() > 0.3) {
        bulletAttack1Cool.reset();
    }
}

void TimeManager::ManageCoolTime(Player& player)
{
    if (player.waitFlag) {
        return;
    }
    UpdateByAttack1Cool(player);
    UpdateByAttack2Cool(player);
    UpdateByAttack3Cool(player);
    UpdateByBulletWarpCool(player);
}

void TimeManager::UpdateByAttack1Cool(Player& player) {
    if (bulletAttack1Cool.sF() > ATTACK1_SPRITE_WAIT) {
        bulletAttack1Cool.reset();
    }
}

void TimeManager::UpdateByAttack2Cool(Player& player) {
    if (bulletAttack2Cool.sF() > ATTACK2_SPRITE_WAIT) {
        bulletAttack2Cool.reset();
    }
}

void TimeManager::UpdateByAttack3Cool(Player& player) {
    if (bulletAttack3Cool.sF() > ATTACK3_SPRITE_COOL) {
        bulletAttack3Cool.reset();
    }
}

void TimeManager::UpdateByBulletWarpCool(Player& player) {
    if (bulletWarpWait.isRunning()
            && bulletWarpWait.sF() > BULLET_WARP_SPRITE_WAIT) {
        //TODO:ˆá‚¤UŒ‚‚Å‚à’Ê‚é
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