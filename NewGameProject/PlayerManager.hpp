#pragma once
# include <Siv3D.hpp>
# include "Player.hpp"
# include "TimeManager.hpp"
# include "CalcHelper.hpp"
# include "EnumManager.hpp"
# include "MapScreenHelper.hpp"
# include "BulletManager.hpp"

/// <summary>
/// プレイヤーのアクションクラスです
/// </summary>
class PlayerManager
{
public:
    PlayerManager();
    void Init(Player& player);
	void Action(Player &player, TimeManager &timeManager, Array<MapTip>& mapTips);
    void Walk(Player &player, TimeManager &timeManager);
    void Jump1(Player &player, TimeManager &timeManager);
    void Jump2(Player &player, TimeManager &timeManager, Array<MapTip>& mapTips);
    void Crouch1(Player& player, TimeManager& timeManager);
    void Dash1(Player &player, TimeManager &timeManager);
    void Dash2(Player &player, TimeManager &timeManager);
    void Fall(Player& player, TimeManager& timeManager);
    void Landing(Player& player, TimeManager &timeManager);
    void ShootBullet(Player& player, TimeManager& timeManager);
    void ForcedFall(Player& player, TimeManager& timeManager);
    void JumpMaxHeight(Player& player, TimeManager& timeManager);
    void JumpShortHeight(Player& player, TimeManager& timeManager);
    void ShootAttackBallet1(Player& player, TimeManager& timeManager);
    void ShootAttackBallet2(Player& player, TimeManager& timeManager);
    void ShootAttackBallet3(Player& player, TimeManager& timeManager);
    void ShootWarpBallet(Player& player, TimeManager& timeManager);
    bool CanWalk(Player player);
    bool CanJump(Player player);
    bool CanDash(Player player);
    bool CanCrouch(Player player);
    bool CanShootBulletAttack1(Player& player, TimeManager& timeManager);
    bool CanShootBulletAttack2(Player& player, TimeManager& timeManager);
    bool CanShootBulletAttack3(Player& player, TimeManager& timeManager);
    bool CanShootWarpBullet(Player& player, TimeManager& timeManager);
    bool IsFalling(Player player);
    bool notDashCrouch(Player player);
    void RightwardDash(Player& player, TimeManager& timeManager);
    void LeftwardDash(Player& player, TimeManager& timeManager);
    void ClearDash(Player& player, TimeManager& timeManager);
    void FixedDash(Player& player, TimeManager& timeManager, bool rightwardFlag);
};