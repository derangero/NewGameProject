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
    Stopwatch bulletAttack1Motioning;
    Stopwatch bulletAttack1Cool;
    Stopwatch bulletAttack2Motioning;
    Stopwatch bulletAttack2Cool;
    Stopwatch bulletAttack3Motioning;
    Stopwatch bulletAttack3Cool;
    Stopwatch bulletAttack3SpriteSw;
    Stopwatch bulletAttack4Wait;
    Stopwatch bulletAttack4Cool;
    Stopwatch dashWaitSw;
    Stopwatch afterImageInterval;
    Stopwatch playerOnDamageSpriteSw;
    Stopwatch playerDownSpriteSw;
	TimeManager();
    void Control(Player& player);
    void Update();
    void ManageCoolTime(Player& player);
    void UpdateByBulletWarpCool(Player& player);
    void UpdateByAttack1Cool(Player& player);
    void UpdateByAttack2Cool(Player& player);
    void UpdateByAttack3Cool(Player& player);
    static bool IsOverWaitTime(TimeManager& timeManager, double time);
    void IncrementNumberByRepeat(int& number, const int max, const double interval, Stopwatch& sw);
};