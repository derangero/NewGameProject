#include "PlayerManager.hpp"

PlayerManager::PlayerManager()
{
}

void PlayerManager::Action(Player &player, TimeManager &timeManager, Array<MapTip>& mapTips)
{
    player.font(U"AttackNumber:", player.attack1Number).draw(280, 10);
    if (player.waitFlag || !player.isExists) {
        return;
    }
    Init(player);
    player.KnockBack();
    Walk(player, timeManager);
    Jump1(player, timeManager);
    Jump2(player, timeManager, mapTips);
    if (player.isActive) {
        Dash1(player, timeManager);
        Dash2(player, timeManager);
        Crouch1(player, timeManager);
        ShootBullet(player, timeManager);
    }
    Fall(player, timeManager);
}

void PlayerManager::Init(Player &player)
{
    player.walkFlag = false;
    player.beforePos = Vec2(player.pos.x, player.pos.y);
}

void PlayerManager::Walk(Player& player, TimeManager& timeManager)
{
    if (!CanWalk(player)) {
        return;
    }
    player.walkFlag = KeyA.pressed() || KeyD.pressed();
    // ジャンプ中の横移動時、ダッシュボタンを押した場合加速
    double delta = player.jumpFlag && KeyW.pressed() ? player.delta * DASH_ACCELERATION : player.delta;
    // TODO:同時押しで移動しない処理はスロープでバグるのでいったん一方通行で
    if (KeyA.pressed()) {
        player.MoveX(-delta);
        player.rightwardFlag = false;
    } else if (KeyD.pressed()) {
        player.MoveX(delta);
        player.rightwardFlag = true;
    }
}

void PlayerManager::Jump1(Player& player, TimeManager& timeManager) {
    if (!CanJump(player)) {
        return;
    }
    ForcedFall(player, timeManager);
    if (KeySpace.pressed() && player.isActive) {
        player.jumpFlag = true;
    }
    else if (player.jumpFlag && player.shortJumpYList.isEmpty()) { // ボタンを離した時, ジャンプ距離を計算
        if (player.jumpFlameCount <= FLAME_BY_FALING) {
            player.pos.y = CalcHelper::CalcJumpY(player, timeManager);
            double newTime = 0;
            for (int i = 0; i < FLAME_BY_JUMP; i++) {
                player.shortJumpYList.push_back(CalcHelper::CalcJumpY(player, timeManager, newTime)); // 参照型にするように（注意）
                newTime += JUMP_BASE_TAME;
            }
        }
    }
}

void PlayerManager::Jump2(Player& player, TimeManager& timeManager, Array<MapTip>& mapTips) {
    if (!player.jumpFlag) {
        return;
    }
    if (player.shortJumpYList.isEmpty()) {
        JumpMaxHeight(player, timeManager);
    }
    else {
        JumpShortHeight(player, timeManager);
    }
    player.jumpFlameCount++; // ジャンプ中はインクリメント
    if (player.jumpFlameCount >= FALL_FLAME_COUNT) {
        player.jumpFallFlag = true;
    }
    player.time += JUMP_BASE_TAME;
    Landing(player, timeManager);
}

void PlayerManager::Crouch1(Player& player, TimeManager& timeManager)
{
    if (!CanCrouch(player))
    {
        return;
    }
    player.crouchFlag = KeyC.pressed();
}

bool OverDashWait(TimeManager timeManager, double waitTime) {
    return timeManager.dashWaitSw.isRunning() && timeManager.dashWaitSw.sF() >= waitTime;
}

void PlayerManager::Dash1(Player& player, TimeManager &timeManager)
{
    if (!CanDash(player)) {
        return;
    }
 
    if (TimeManager::IsOverWaitTime(timeManager, DASH_WAIT_TIME)) {
        return;
    }
    if (KeyW.down() && !timeManager.dashWaitSw.isRunning()) {
        player.dashFlag = true;
        timeManager.dashWaitSw.start();
        player.tempXBeforDash = player.pos.x;
    }
}

void PlayerManager::Dash2(Player& player, TimeManager& timeManager)
{
    if (!player.dashFlag) {
        timeManager.dashTime = 0.0;
        return;
    }

    RightwardDash(player, timeManager);
    LeftwardDash(player, timeManager);
}

/// <summary>
/// 着地した時の処理です
/// </summary>
/// <param name="player"></param>
/// <param name="timeManager"></param>
void PlayerManager::Landing(Player &player, TimeManager &timeManager) {
    if (player.jumpMode == JumpMode::FALL && !player.naturalFallFlag) {
        player.ReplaceY(player.groundY);
        player.time = 0.0;
        player.shortJumpIndex = 0;
        player.jumpFlameCount = 0;
        player.jumpMode = JumpMode::UP;
        player.jumpFlag = false;
        player.jumpFallFlag = false;
        player.shortJumpYList.clear();
    }
}

void PlayerManager::ShootBullet(Player& player, TimeManager& timeManager)
{
    // HACK:どこでオブジェクトが移動しているのか全く分からん
    ShootAttackBallet1(player, timeManager); // モーションの競合注意
    ShootAttackBallet2(player, timeManager); // E)無敵つきの射撃
    ShootAttackBallet3(player, timeManager); // R)二丁拳銃
    ShootWarpBallet(player, timeManager);
}

void PlayerManager::ShootAttackBallet1(Player& player, TimeManager& timeManager)
{
    if (CanShootBulletAttack1(player, timeManager) && KeyEnter.down()) {
        BalletActionStart(player, BulletMode::ATTACK_1, BulletName::ATTACK_1, timeManager.bulletAttack1Motioning);
        if (player.attack1Number == BULLET_WARP_MAX_SPRITE_NUMBER) {
            player.attack1Number = 2;
        }
    }
    if (BulletMode::ATTACK_1 == player.bulletMode) {
        player.bulletMode;
        if ((player.attack1Number > 0 && player.attack1Number == BULLET_WARP_MAX_SPRITE_NUMBER)
                || CharaActionState::ON_DAMAGE_INVISIBLE == player.actionState) {
            BalletActionEnd(player, timeManager.bulletAttack1Motioning, timeManager.bulletAttack1Cool);
        }
    }
}

void PlayerManager::ShootAttackBallet2(Player& player, TimeManager& timeManager)
{
    if (CanShootBulletAttack2(player, timeManager)) {
        if (KeyE.down()) {
            BalletActionStart(player, BulletMode::ATTACK_2, BulletName::ATTACK_1, timeManager.bulletAttack2Motioning);
            player.isInvisible = true;
        }
    }
    // 反動で後ろに進む感じ
    if (timeManager.bulletAttack2Motioning.isRunning() && player.isInvisible) {
        player.MoveX((player.rightwardFlag ? -player.delta : player.delta) / 5);
    }
    if (player.attack1Number > 0 && player.attack1Number >= BULLET_ATTACK2_MAX_SPRITE_NUMBER) {
        //TODO:保留
        //player.isAttack1 = false;
        BalletActionEnd(player, timeManager.bulletAttack2Motioning, timeManager.bulletAttack2Cool);
        player.isInvisible = false;
    }
}

void PlayerManager::ShootAttackBallet3(Player &player, TimeManager& timeManager)
{
    if (CanShootBulletAttack3(player, timeManager) && KeyR.down()) {
        BalletActionStart(player, BulletMode::ATTACK_3, BulletName::ATTACK_3, timeManager.bulletAttack3Motioning);
    }
    if ((player.attackNumbers[3] > 0 && player.attackNumbers[3] >= BULLET_ATTACK3_MAX_SPRITE_NUMBER)
        || CharaActionState::ON_DAMAGE_INVISIBLE == player.actionState) {
        BalletActionEnd(player, timeManager.bulletAttack3Motioning, timeManager.bulletAttack3Cool);
        player.attackNumbers[3] = 0;
    }
}

void PlayerManager::BalletActionStart(Player &player, BulletMode bulletMode, BulletName bulletName,
        Stopwatch &motioningSw)
{
    player.isShooted = true;
    player.bulletMode = bulletMode;
    player.bulletName = bulletName;
    motioningSw.restart();
}

void PlayerManager::BalletActionEnd(Player &player, Stopwatch &motioningSw, Stopwatch& coolSw)
{
    player.bulletMode = BulletMode::NONE;
    //TODO:悪影響がないか？
    //player.bulletName = bulletName::NONE;
    player.attack1Number = 0;
    motioningSw.reset();
    coolSw.restart();
}

void PlayerManager::ShootWarpBallet(Player& player, TimeManager& timeManager) {
    if (BulletMode::NONE != player.bulletMode
            && BulletMode::WARP != player.bulletMode) {
        return;
    }
    if (CanShootWarpBullet(player, timeManager) && KeyQ.down()) {
        player.bulletMode = BulletMode::WARP;
    }
    else if ((player.attack1Number > 0 && player.attack1Number == BULLET_WARP_MAX_SPRITE_NUMBER) || player.isAttack1) {
        player.bulletMode = BulletMode::NONE;
        player.isAttack1 = false;
        timeManager.bulletWarpWait.start();
    }
}
/// <summary>
/// ジャンプの最高点に到達する前に当たり判定があれば新たに座標管理します
/// また、プレイヤーがジャンプ時に被弾した時も同様です
/// </summary>
void PlayerManager::ForcedFall(Player& player, TimeManager& timeManager)
{
    if ((player.topWallFlag2 || !player.isActive) && player.shortJumpYList.isEmpty()) {
        double newTime = 0;
        for (int i = 0; i < FLAME_BY_JUMP; i++) {
            player.shortJumpYList.push_back(CalcHelper::CalcJumpY(player, timeManager, newTime)); // 参照型にするように（注意）
            newTime += 0.07;
        }
        player.topWallFlag2 = false;
    }
}

/// <summary>
/// 最高点までジャンプした時の落下処理です
/// </summary>
/// <param name="player"></param>
/// <param name="timeManager"></param>
void PlayerManager::JumpMaxHeight(Player& player, TimeManager& timeManager)
{
    //: player.pos.y = CalcHelper::CalcJumpY(player, timeManager);
    player.ReplaceY(JumpMode::FALL == player.jumpMode && player.jumpFallFlag
        ? player.pos.y + FALL_AMT
        : CalcHelper::CalcJumpY(player, timeManager));
    if (player.pos.y <= (player.groundY - PLAYER_JUMP_HEIGHT) + 1) {
        player.jumpMode = JumpMode::FALL;
    }
}

void PlayerManager::JumpShortHeight(Player& player, TimeManager& timeManager)
{
    if (player.shortJumpYList.size() < ABOUT_TOP_JUMP_Y_INDEX) { // 念のためガード
        return;
    }

    if (IsFalling(player)) {
        player.MoveY(FALL_AMT);
    }
    else { //ジャンプ中
        double y = player.pos.y;
        if (player.shortJumpYList.size() - 1 >= player.shortJumpIndex + ABOUT_TOP_JUMP_Y_INDEX) {
            y = player.shortJumpYList[player.shortJumpIndex + ABOUT_TOP_JUMP_Y_INDEX];
        }
        player.ReplaceY(y);
    }
    player.shortJumpIndex += 1;
    player.jumpMode = JumpMode::FALL;
}

bool PlayerManager::CanWalk(Player player)
{
    return !player.crouchFlag && !player.dashFlag &&  player.isActive;
}

bool PlayerManager::CanJump(Player player)
{
    return !player.dashFlag && !player.jumpFallFlag && !player.crouchFlag;
}

bool PlayerManager::CanDash(Player player)
{
    return !player.jumpFallFlag && !player.crouchFlag && !player.jumpFlag;
}

bool PlayerManager::CanCrouch(Player player)
{
    return !player.dashFlag && !player.jumpFlag && !player.jumpFallFlag && BulletMode::NONE == player.bulletMode;
}

bool PlayerManager::CanShootBulletAttack1(Player& player, TimeManager &timeManager) {
    return notDashCrouch(player)
        && player.bulletMode == BulletMode::NONE
        && !timeManager.bulletAttack1Motioning.isRunning()
        && !timeManager.bulletAttack1Cool.isRunning();
}

bool PlayerManager::CanShootBulletAttack2(Player& player, TimeManager &timeManager) {
    return notDashCrouch(player)
        && player.bulletMode == BulletMode::NONE
        && !timeManager.bulletAttack2Motioning.isRunning()
        && !timeManager.bulletAttack2Cool.isRunning();
}

bool PlayerManager::CanShootBulletAttack3(Player& player, TimeManager &timeManager) {
    return notDashCrouch(player)
        && player.bulletMode == BulletMode::NONE
        && !timeManager.bulletAttack3Motioning.isRunning()
        && !timeManager.bulletAttack3Cool.isRunning();
}

bool PlayerManager::CanShootWarpBullet(Player& player, TimeManager &timeManager) {
    return !player.dashFlag && !player.afterDashFlag && !player.isAttack1 && !timeManager.bulletWarpWait.isRunning();
}

bool PlayerManager::notDashCrouch(Player player) {
    return !player.dashFlag && !player.afterDashFlag && !player.crouchFlag;
}

bool PlayerManager::IsFalling(Player player)
{
    return JumpMode::FALL == player.jumpMode && player.jumpFallFlag;
}

void PlayerManager::RightwardDash(Player& player, TimeManager& timeManager)
{
    if (!player.rightwardFlag) {
        return;
    }
    if (!player.rightWallFlag && player.pos.x <= player.tempXBeforDash + DASH_DIST) {
        FixedDash(player, timeManager, player.rightwardFlag);
    }
    else {
        ClearDash(player, timeManager);
    }
}

void PlayerManager::LeftwardDash(Player& player, TimeManager& timeManager)
{
    if (player.rightwardFlag) {
        return;
    }
    if (!player.leftWallFlag && player.pos.x >= player.tempXBeforDash - DASH_DIST) {
        if (!player.jumpFlag) {
            player.ReplaceY(
                player.groundY - (1.0 - pow(1.0 - sin(DASH_PI * timeManager.dashTime), DASH_DISTORTION)) * DASH_HEIGHT);
        }
        player.MoveX(-(!player.jumpFlag ? player.delta * 2 : player.delta * 4));
        timeManager.dashTime += 0.1;
    }
    else {
        ClearDash(player, timeManager);
    }
}

void PlayerManager::ClearDash(Player& player, TimeManager& timeManager)
{
    player.tempXBeforDash = 0.0;
    player.dashFlag = false;
    player.ReplaceY(player.groundY);
    player.afterDashFlag = true;
    timeManager.dashTime = 0.0;
}

void PlayerManager::FixedDash(Player& player, TimeManager& timeManager, bool rightwardFlag)
{
    if (!player.jumpFlag) {
        player.ReplaceY(
            player.groundY - (1.0 - pow(1.0 - sin(DASH_PI * timeManager.dashTime), DASH_DISTORTION)) * DASH_HEIGHT);
    }
    int multiplicand = !player.jumpFlag ? 2 : 4;
    player.MoveX(rightwardFlag
        ? player.delta * multiplicand
        : -(player.delta * multiplicand));
    timeManager.dashTime += 0.1;
}

void PlayerManager::Fall(Player& player, TimeManager& timeManager)
{
    if (player.naturalFallFlag && !player.jumpFlag && !player.dashFlag) {

        if (!player.rightwardFlag && player.isSlope) {
            return;
        }
        player.MoveY(FALL_AMT);
        player.ReplaceY(player.pos.y);
        player.jumpFallFlag = player.afterDashFlag ? false : true;
    }
}