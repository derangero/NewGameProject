#pragma once
# include <Siv3D.hpp>
# include "Player.hpp"

/// <summary>
/// éûä‘Çä«óùÇ∑ÇÈÉNÉâÉXÇ≈Ç∑
/// </summary>
class TimeManager {
public:
    double time;
    double dashTime;
    Stopwatch jumpSw;
    Stopwatch runSw;
    Stopwatch standSw;
    Stopwatch crouchSw;
    Stopwatch attack1SpriteSw;
    Stopwatch attack2SpriteSw;
    Stopwatch attack3SpriteSw;
    Stopwatch bulletWarpWait;
    Stopwatch bulletAttack1Wait;
    Stopwatch bulletAttack1Cool;
    Stopwatch bulletAttack2Wait;
    Stopwatch bulletAttack2Cool;
    Stopwatch bulletAttack3Wait;
    Stopwatch bulletAttack3Cool;
    Stopwatch bulletAttack3SpriteSw;
    Stopwatch bulletAttack4Wait;
    Stopwatch bulletAttack4Cool;
    Stopwatch dashWaitSw;
    Stopwatch afterImageInterval;
    Stopwatch playerOnDamageSpriteSw;
	TimeManager();
    void Control(Player& player);
    void Update();
    void UpdateWhenOverTime(Player& player);
    void UpdateByBulletWarpWait(Player& player);
    void UpdateByAttack1Wait(Player& player);
    void UpdateByAttack2Wait(Player& player);
    void UpdateByAttack3Wait(Player& player);
    static bool IsOverWaitTime(TimeManager& timeManager, double time);
};