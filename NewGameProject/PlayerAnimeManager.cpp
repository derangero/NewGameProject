#include "PlayerAnimeManager.hpp"

PlayerAnimeManager::PlayerAnimeManager() : standNumber(0), jumpNumber(0), runNumber(0),
    crouchNumber(0) {
}

void PlayerAnimeManager::Draw(Player& player, TimeManager& _timeManager, Effect &effect)
{
    if (!player.isExists) {
        Down(player, timeManager);
        return;
    }
    BulletMotion(player, timeManager);
    Jump(player, timeManager, effect);
    Dash(player, timeManager);
    Run(player, timeManager);
    Stand(player, timeManager);
    Crouch(player, timeManager);
    GrabLadder(player, timeManager);
    OnDamage(player, timeManager);
    player.flag = !player.flag; //点滅用
}

void PlayerAnimeManager::GrabLadder(Player &player, TimeManager &tManager)
{
    if (RadderMode::GRABBING != player.radderMode) {
        return;
    }
    TextureRegion playerImage = player.allImage(249, PLAYER_GRAB_LADDER_SPRITE_Y,
        PLAYER_GRAB_LADDER_SPRITE_SIZE);
    DrawPlayerImage(player, playerImage, Vec2(0, 0), Vec2(0, 0));
}

void PlayerAnimeManager::OnDamage(Player& player, TimeManager& tManager)
{
    if (player.actionState != CharaActionState::ON_DAMAGE_INVISIBLE) {
        return;
    }
    SpriteImageMetaData icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::ON_DAMAGE]);
    TextureRegion playerImage = SpriteUtil::ExtractionImage(player.allImage, icData, player.imageNumber);
    DrawPlayerInvisibleImage(player, playerImage, Vec2(0, 0), Vec2(0, 0));
    ChangeOnDamageSprite(player, icData, timeManager);
}

void PlayerAnimeManager::Down(Player& player, TimeManager& tManager)
{
    if (player.actionState != CharaActionState::DOWN) {
        return;
    }
    SpriteImageMetaData& icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::DOWN]);
    TextureRegion playerImage = SpriteUtil::ExtractionImage(player.allImage, icData, player.imageNumber);
    _ASSERT_EXPR(PLAYER_DOWN_SPRITE_FIX_VEC2_ARRAY.size() > player.imageNumber, L"PlayerAnimeManager::Down, OutOfRange FIX_VEC2_ARRAY");
    Vec2 fixPos = PLAYER_DOWN_SPRITE_FIX_VEC2_ARRAY[player.imageNumber];
    DrawPlayerImage(player, playerImage, fixPos, fixPos);
    ChangeDownSprite(player, icData, timeManager);
}

void PlayerAnimeManager::Jump(Player& player, TimeManager &timeManager, Effect &effect)
{
    if (!player.jumpFlag || BulletMode::NONE != player.bulletMode) {
        effect.clear();
        return;
    }
    //TextureRegion playerImage = player.image(0.0 + (jumpNumber * PLAYER_JUMP_SPRITE_SIZE.x), PLAYER_JUMP_SPRITE_Y,
    //    PLAYER_JUMP_SPRITE_SIZE);
    SpriteImageMetaData icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::JUMP]);
    TextureRegion playerImage = SpriteUtil::ExtractionImage(player.allImage, icData, jumpNumber);
    //DrawPlayerAfterImage(player, playerImage, timeManager, effect);
    DrawPlayerImage(player, playerImage, IMAGE_JUMP_LEFT_POS, IMAGE_JUMP_RIGHT_POS);
    ChangeJumpSprite(player, icData, timeManager);
}

void PlayerAnimeManager::Dash(Player& player, TimeManager& timeManager)
{
    if (!player.dashFlag) {
        return;
    }

    SpriteImageMetaData icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::DASH]);
    TextureRegion playerImage = SpriteUtil::ExtractionImage(player.allImage, icData, SPRITE_DASH_NUMBER);
    //TextureRegion playerImage = player.image(PLAYER_DASH_SPRITE_POS, PLAYER_DASH_SPRITE_SIZE);
    DrawPlayerImage(player, playerImage, Vec2(0, 0), Vec2(0, 0));
}

void PlayerAnimeManager::Run(Player& player, TimeManager& timeManager)
{
    if (DrawFallAnime(player) || !player.walkFlag || player.jumpFlag || player.crouchFlag || BulletMode::NONE != player.bulletMode || RadderMode::GRABBING == player.radderMode) {
        return;
    }

    SpriteImageMetaData icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::RUN]);
    TextureRegion playerImage = SpriteUtil::ExtractionImage(player.allImage, icData, runNumber);
    //TextureRegion playerImage = player.image(0.0 + (runNumber * PLAYER_RUN_SPRITE_SIZE.x), PLAYER_RUN_SPRITE_Y, PLAYER_RUN_SPRITE_SIZE);
    DrawPlayerImage(player, playerImage, IMAGE_WALK_POS, IMAGE_WALK_POS);
    ChangeRunSprite(player, icData, timeManager);
}

void PlayerAnimeManager::Stand(Player& player, TimeManager& timeManager)
{
    if (DrawFallAnime(player) || player.walkFlag || player.jumpFlag
            || player.dashFlag || player.crouchFlag || BulletMode::NONE != player.bulletMode
            || player.radderMode == RadderMode::GRABBING
            || player.actionState != CharaActionState::WAIT) {
        return;
    }
    SpriteImageMetaData icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::STAND]);
    TextureRegion playerImage = SpriteUtil::ExtractionImage(player.allImage, icData, standNumber);
    DrawPlayerStandImage(player, playerImage);
    ChangeStandSprite(player, icData, timeManager);
}

void PlayerAnimeManager::Crouch(Player& player, TimeManager& timeManager)
{
    if (!player.crouchFlag) {
        crouchNumber = 0;
        return;
    }
    SpriteImageMetaData icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::CROUCH]);
    TextureRegion playerImage = SpriteUtil::ExtractionImage(player.allImage, icData, crouchNumber);
    Vec2 fixPos = PLAYER_CROUCH_SPRITE_FIX_VEC2_ARRAY[crouchNumber];
    DrawPlayerImage(player, playerImage, fixPos, fixPos);
    ChangeCrouchSprite(player, icData, timeManager);
}

void PlayerAnimeManager::BulletMotion(Player& player, TimeManager& timeManager)
{
    BulletAttack1(player, timeManager); // 攻撃１とワープのモーションは共用
    BulletAttack2(player, timeManager);
    BulletAttack3(player, timeManager);
}

void PlayerAnimeManager::BulletAttack1(Player& player, TimeManager& timeManager)
{
    if ((BulletMode::ATTACK_1 != player.bulletMode && BulletMode::WARP != player.bulletMode)
            || player.dashFlag) {
        return;
    }
    SpriteImageMetaData icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::SHOOT_ATTACK_1]);
    TextureRegion playerImage = SpriteUtil::ExtractionImage(player.allImage, icData, player.attack1Number);
    DrawPlayerImage(player, playerImage, Vec2(0,0), Vec2(0, 0));
    // TODO:↓Beanクラスを使う必要もないかな？
    AnimationBean ani(icData.maxImageNumber, icData.interval, timeManager.attack1SpriteSw);
    ChangeAttack1Sprite(player, ani);
}

void PlayerAnimeManager::BulletAttack2(Player& player, TimeManager& timeManager)
{
    if (BulletMode::ATTACK_2 != player.bulletMode || player.dashFlag) {
        return;
    }
    SpriteImageMetaData icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::SHOOT_ATTACK_2]);
    TextureRegion playerImage = SpriteUtil::ExtractionImage(player.allImage, icData, player.attack1Number);
    Vec2 fixed = BULLET_ATTACK2_FIX_SPRITE_VEC2S[player.attack1Number];
    DrawPlayerImage(player, playerImage, fixed, -fixed);
    AnimationBean ani(icData.maxImageNumber, icData.interval, timeManager.attack2SpriteSw);
    ChangeAttack1Sprite(player, ani);
}
// TODO: BulletAnimeManager
void PlayerAnimeManager::BulletAttack3(Player& player, TimeManager& timeManager)
{
    if (BulletMode::ATTACK_3 != player.bulletMode || player.dashFlag) {
        return;
    }
    Vec2 fixed = BULLET_ATTACK3_FIX_SPRITE_VEC2S[player.attack1Number];
    SpriteImageMetaData icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::SHOOT_ATTACK_3]);
    TextureRegion playerImage = SpriteUtil::ExtractionImage(player.allImage, icData, player.attackNumbers[3]);
    AnimationBean ani(icData.maxImageNumber, icData.interval, timeManager.attack3SpriteSw);
    DrawPlayerImage(player, playerImage, fixed, -fixed);
    ChangeAttackNSprite(player, ani, 3);
}

/// <summary>
/// 落下モーションを描画します
/// </summary>
/// <param name="player">プレイヤークラス</param>
/// <returns>落下モードかどうか</returns>
bool PlayerAnimeManager::DrawFallAnime(Player& player)
{
    if (player.jumpFallFlag && !player.jumpFlag && !player.dashFlag && BulletMode::NONE == player.bulletMode) {
        SpriteImageMetaData icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::JUMP]);
        TextureRegion playerImage = SpriteUtil::ExtractionImage(player.allImage, icData, FALL_ANIME_NUMBER);
        //TextureRegion playerImage = player.image(0.0 + (FALL_ANIME_NUMBER * PLAYER_JUMP_SPRITE_SIZE.x),
        //    PLAYER_JUMP_SPRITE_Y, PLAYER_JUMP_SPRITE_SIZE);
        DrawPlayerImage(player, playerImage, Vec2(0, 0), Vec2(0, 0));
        return true;
    }
    return false;
}

void PlayerAnimeManager::ChangeJumpSprite(Player player, SpriteImageMetaData icData, TimeManager& timeManager)
{
    timeManager.jumpSw.start();
    if (timeManager.jumpSw.sF() >= icData.interval) {
        jumpNumber++;
        if (JumpMode::UP == player.jumpMode) {
            if (jumpNumber > PLAYER_JUMP_UP_MAX_IMAGE_NUMBER) {
                jumpNumber = PLAYER_JUMP_UP_MAX_IMAGE_NUMBER;
            }
        }
        else {
            if (jumpNumber > icData.maxImageNumber) {
                jumpNumber = icData.maxImageNumber;
            }
        }
        timeManager.jumpSw.reset();
    }
}

void PlayerAnimeManager::ChangeRunSprite(Player player, SpriteImageMetaData icData, TimeManager& timeManager)
{
    timeManager.runSw.start();
    if (timeManager.runSw.sF() >= icData.interval) {
        runNumber++;
        if (runNumber > icData.maxImageNumber) {
            runNumber = 0;
        }
        timeManager.runSw.reset();
    }
}

void PlayerAnimeManager::ChangeStandSprite(Player player, SpriteImageMetaData icData, TimeManager& timeManager)
{
    timeManager.standSw.start();
    if (timeManager.standSw.sF() >= icData.interval) {
        standNumber++;
        timeManager.standSw.reset();
        if (standNumber > icData.maxImageNumber) {
            standNumber = 0;
        }
    }
}

void PlayerAnimeManager::ChangeCrouchSprite(Player player, SpriteImageMetaData icData, TimeManager& timeManager)
{
    timeManager.crouchSw.start();
    if (timeManager.crouchSw.sF() >= icData.interval) {
        if (crouchNumber < icData.maxImageNumber) {
            crouchNumber++;
        }
        timeManager.crouchSw.reset();
    }
}

void PlayerAnimeManager::ChangeAttack1Sprite(Player& player, AnimationBean& aniBean)
{
    aniBean.sw.start();
    if (aniBean.sw.sF() >= aniBean.interval) {
        player.attack1Number += 1;
        if (player.attack1Number > aniBean.maxImageNumber) {
            player.attack1Number = aniBean.maxImageNumber;
        }
        aniBean.sw.reset();
    }
}

void PlayerAnimeManager::ChangeAttackNSprite(Player& player, AnimationBean& aniBean, int n)
{
    aniBean.sw.start();
    if (aniBean.sw.sF() >= aniBean.interval) {
        player.attackNumbers[n] += 1;
        if (player.attackNumbers[n] > aniBean.maxImageNumber) {
            player.attackNumbers[n] = aniBean.maxImageNumber;
        }
        aniBean.sw.reset();
    }
}


void PlayerAnimeManager::ChangeOnDamageSprite(Player& player, SpriteImageMetaData icData, TimeManager& timeManager)
{
    timeManager.playerOnDamageSpriteSw.start();
    if (timeManager.playerOnDamageSpriteSw.sF() >= icData.interval) {
        player.imageNumber++;
        if (player.imageNumber > PLAYER_ONDAMEGE_MAX_SPRITE_NUMBER) {
            player.imageNumber = PLAYER_ONDAMEGE_MAX_SPRITE_NUMBER;
        }
        timeManager.playerOnDamageSpriteSw.reset();
    }
}

void PlayerAnimeManager::ChangeDownSprite(Player& player, SpriteImageMetaData& icData, TimeManager& timeManager)
{
    timeManager.playerDownSpriteSw.start();
    if (timeManager.playerDownSpriteSw.sF() >= icData.interval * PLAYER_DOWN_SLOW_FOLD) {
        player.imageNumber--;
        if (player.imageNumber < 0) {
            player.imageNumber = 0;
        }
        timeManager.playerDownSpriteSw.reset();
    }
}

void PlayerAnimeManager::DrawPlayerStandImage(Player player, TextureRegion playerImage)
{
    Vec2 mapPlayerPos = GetMapPlayerPos(player);
    ColorF color = GetPlayerColor(player);
    player.rightwardFlag
        ? playerImage.draw(mapPlayerPos.movedBy(FIXED_STAND_RIGHT_X, 0), color)
        : playerImage.mirrored().draw(mapPlayerPos.movedBy(FIXED_STAND_LEFT_X, 0), color);
}

ColorF PlayerAnimeManager::GetPlayerColor(Player player)
{
    ColorF color = ColorF(1.0);
    if (player.waitFlag) {
        color = ColorF(1.0, 0.5);
    }
    if (player.IsInvisible()) {
        if (CharaActionState::ON_DAMAGE_INVISIBLE  == player.actionState) {
            color = ColorF(1.0, player.flag ? 0.0 : 1.0, player.flag ? 0.0 : 1.0, Periodic::Square0_1(0.1s));
        }
        else {
            color = ColorF(1.0, 1.0, 1.0, Periodic::Square0_1(0.1s));
        }
    }

    return color;
}

void PlayerAnimeManager::DrawPlayerImage(Player player, TextureRegion playerImage, Vec2 leftFixed, Vec2 rightFixed)
{
    DrawPlayerImageAction(player, playerImage, leftFixed, rightFixed, false);
}

void PlayerAnimeManager::DrawPlayerInvisibleImage(Player player, TextureRegion playerImage, Vec2 leftFixed, Vec2 rightFixed)
{
    DrawPlayerImageAction(player, playerImage, leftFixed, rightFixed, true);
}

void PlayerAnimeManager::DrawPlayerImageAction(Player player, TextureRegion playerImage, Vec2 leftFixed, Vec2 rightFixed, bool isInvisible)
{
    if (CharaActionState::ON_DAMAGE_INVISIBLE != player.actionState || isInvisible) {
        Vec2 mapPlayerPos = GetMapPlayerPos(player);
        ColorF color = GetPlayerColor(player);
        player.rightwardFlag
            ? playerImage.draw(mapPlayerPos.movedBy(rightFixed), color)
            : playerImage.mirrored().draw(mapPlayerPos.movedBy(leftFixed), color);
    }
}

Vec2 PlayerAnimeManager::GetMapPlayerPos(Player player) {
    double x = MapScreenHelper::IsMoveCameraX(player.pos.x)
        ? PLAYER_STAND_POS.x
        : player.pos.x - (PLAYER_STAND_POS.x - PLAYER_STAND_POS.x);
    double y = MapScreenHelper::IsMoveCameraY(player.pos.y)
        ? PLAYER_STAND_POS.y
        : player.pos.y - (PLAYER_STAND_POS.y - PLAYER_STAND_POS.y);
    return Vec2(x, y);
}
/// <summary>
/// プレイヤーキャラの画像に残像表現を行います。
/// </summary>
/// <param name="player">プレイヤーオブジェクト</param>
/// <param name="playerImage">プレイヤー画像</param>
/// <param name="fixedPos">表示位置</param>
void PlayerAnimeManager::DrawPlayerAfterImage(Player player, TextureRegion playerImage, TimeManager& timeManager, Effect &effect) {
    Vec2 mapPlayerPos = GetMapPlayerPos(player);
    if (timeManager.afterImageInterval.elapsed() >= 0.05s)
    {
        effect.add<Afterimage>(player.rightwardFlag ? playerImage : playerImage.mirrored(), mapPlayerPos, 0.5);  //0.7秒かけて消える
        timeManager.afterImageInterval.restart();
    }
    //HACK:重い？
    effect.update();
}
