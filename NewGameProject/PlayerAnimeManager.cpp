#include "PlayerAnimeManager.hpp"

PlayerAnimeManager::PlayerAnimeManager() : standNumber(0), jumpNumber(0), runNumber(0),
    crouchNumber(0) {
}

void PlayerAnimeManager::Draw(Player& player, TimeManager& _timeManager, Effect &effect)
{
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
    if (RadderMode::GRABBED != player.radderMode) {
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
    DrawPlayerImage(player, playerImage, Vec2(0, 0), Vec2(0, 0));
    ChangeOnDamageSprite(player, icData, timeManager);
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
    DrawPlayerAfterImage(player, playerImage, timeManager, effect);
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
    if (DrawFallAnime(player) || !player.walkFlag || player.jumpFlag || player.crouchFlag || BulletMode::NONE != player.bulletMode || RadderMode::GRABBED == player.radderMode) {
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
            || player.radderMode == RadderMode::GRABBED
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
    DrawPlayerImage(player, playerImage, IMAGE_CROUCH_POS, IMAGE_CROUCH_POS);
    player.UpdateDetection(0, PLAYER_FIXED_CROUCH_H, PLAYER_DETEC_W, PLAYER_CROUCH_DETEC_H);
    ChangeCrouchSprite(player, icData, timeManager);
}

void PlayerAnimeManager::BulletMotion(Player& player, TimeManager& timeManager)
{
    BulletWarp(player, timeManager); // 攻撃１とワープのモーションは共用
    BulletAttack2(player, timeManager);
    BulletAttack3(player, timeManager);
}

void PlayerAnimeManager::BulletWarp(Player& player, TimeManager& timeManager)
{
    if ((BulletMode::ATTACK_1 != player.bulletMode &&
        BulletMode::WARP != player.bulletMode) || player.dashFlag) {
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
    //TextureRegion playerImage = player.image(0.0 + 
    //    (player.attack1Number * fixed.x) + (player.attack1Number * BULLET_ATTACK2_SPRITE_SIZE.x),
    //    fixed.y + BULLET_ATTACK2_SPRITE_Y, BULLET_ATTACK2_SPRITE_SIZE.movedBy(Vec2(0, 0)));
    DrawPlayerImage(player, playerImage, fixed, -fixed);
    AnimationBean ani(icData.maxImageNumber, icData.interval, timeManager.attack2SpriteSw);
    ChangeAttack1Sprite(player, ani);
}

void PlayerAnimeManager::BulletAttack3(Player& player, TimeManager& timeManager)
{
    if (BulletMode::ATTACK_3 != player.bulletMode || player.dashFlag) {
        return;
    }

    Vec2 fixed = BULLET_ATTACK3_FIX_SPRITE_VEC2S[player.attack1Number];
    SpriteImageMetaData icData(player.spriteImageMetaDataMap[(int)PlayerAnimeType::SHOOT_ATTACK_3]);
    TextureRegion playerImage = SpriteUtil::ExtractionImage(player.allImage, icData, player.attackNumbers[3]);
    AnimationBean ani(icData.maxImageNumber, icData.interval, timeManager.attack3SpriteSw);
    //TextureRegion playerImage = player.image(0.0 + 
    //    (player.attack1Number * fixed.x) + (player.attack1Number * BULLET_ATTACK3_SPRITE_SIZE.x),
    //    fixed.y + BULLET_ATTACK3_SPRITE_Y, BULLET_ATTACK3_SPRITE_SIZE.movedBy(Vec2(0, 0)));
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
    Vec2 mapPlayerPos = GetMapPlayerPos(player);
    ColorF color = GetPlayerColor(player);
    player.rightwardFlag
        ? playerImage.draw(mapPlayerPos.movedBy(rightFixed), color)
        : playerImage.mirrored().draw(mapPlayerPos.movedBy(leftFixed), color);
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
