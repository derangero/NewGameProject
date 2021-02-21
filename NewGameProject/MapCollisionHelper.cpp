#include "MapCollisionHelper.hpp"

MapCollisionHelper::MapCollisionHelper(MapCreator& mapCreator)
    : mapCreator(mapCreator)
{}

void MapCollisionHelper::CheckCollision(Player &player, MapScreenHelper &screenHelper)
{
    if (player.waitFlag) { // 壁のすり抜け処理用
        return;
    }
    InitBeforeCheck(player);
    CheckSide(player, screenHelper);
    CheckHead(player, screenHelper);
    CheckFoot(player, screenHelper);
}

void MapCollisionHelper::CheckCollision(Enemy &enemy, MapScreenHelper &screenHelper)
{
    InitBeforeCheck(enemy);
    CheckSide(enemy, screenHelper);
    CheckFoot(enemy, screenHelper);
}

void MapCollisionHelper::CheckBlockCollision(Player& player, MapScreenHelper& screenHelper)
{
    CheckBlockCollisionSide(player, screenHelper);
    CheckBlockCollisionBottom(player, screenHelper);
}

void MapCollisionHelper::CheckBlockCollisionSide(Player &player, MapScreenHelper& screenHelper)
{
    for (ObjectTip& objectTip : mapCreator.objectTips) {
        if (MapType::MOVABLE_OBJ_A != objectTip.mapType) {
            continue;
        }
        for (MapTip& mapTip : mapCreator.mapTips) {
            if (mapTip.collision.intersects(objectTip.collision)) {
                double mapTipLeftX = mapTip.collision.left().begin.x;
                double objectRightX = objectTip.collision.right().begin.x;
                if (mapTipLeftX <= objectRightX) {
                    if (player.objectTipTouching == MapTipTouching::RIGHT) {
                        objectTip.MoveX(4.0);
                    }
                    if (player.objectTipTouching == MapTipTouching::LEFT) {
                        objectTip.MoveX(-4.0);
                    }
                    objectTip.movedDistance.x = 0.0;
                    objectTip.tipMovingBy = TipMovingBy::NONE;
                    break;
                }
            }
        }
        for (ObjectTip& other : mapCreator.objectTips) {
            // プレイヤーが触れていないオブジェクトも動いてしまうので
            if (other.collision == objectTip.collision
                    || player.touchedObjectId != objectTip.id) {
                continue;
            }
            if (other.collision.intersects(objectTip.collision)) {
                double otherLeftX = other.collision.left().begin.x;
                double objectRightX = objectTip.collision.right().begin.x;
                if (otherLeftX <= objectRightX) {
                    if (player.objectTipTouching == MapTipTouching::RIGHT) {
                        objectTip.MoveX(4.0);
                    }
                    if (player.objectTipTouching == MapTipTouching::LEFT) {
                        objectTip.MoveX(-4.0);
                    }
                    objectTip.movedDistance.x = 0.0;
                    objectTip.tipMovingBy = TipMovingBy::NONE;
                    break;
                }
            }
        }
    }
}

void MapCollisionHelper::InitBeforeCheck(Character& chara)
{
    if (CharaFallMode::BROW_UP_A != chara.charaFallMode) {
        chara.charaFallMode = CharaFallMode::NATURAL_FALL;
    }
    chara.wallTipTouching = MapTipTouching::NONE;
    chara.objectTipTouching = MapTipTouching::NONE;
    chara.touchedObjectId = -1;
    chara.topWallFlag = false;
    chara.ignoreWall = false;
}

/// <summary>
/// キャラ両端の当たり判定を行います。
/// ※落下時は一時的に地面にめり込む形になるのでフラグが立ちます
/// </summary>
/// <param name="mapTips">マップチップのリスト</param>
/// <param name="player">プレイヤー</param>
/// <param name="screenHelper">スクリーンヘルパー</param>
void MapCollisionHelper::CheckSide(Player &player, MapScreenHelper &screenHelper)
{
    Array<MapTip>& mapTips = mapCreator.mapTips;
    Vec2 screenOriginPos(MapScreenHelper::ChangeWorldToScreenPos(player.pos));
    CheckSide(player, screenHelper, screenOriginPos);
    if (player.wallTipTouching != MapTipTouching::NONE) {
        if (BulletMode::WARP == player.bulletMode) {
            player.ReplacePos(player.beforePos);
        }
        else if (!player.ignoreWall) {
            player.ReplaceX(player.beforePos.x);
        }
        player.dashFlag = false;
    }
    bool grabbed = false;
    for (ObjectTip& objectTip : mapCreator.objectTips) {
        RectF collision(objectTip.collision.movedBy(-screenOriginPos));
        if (player.hitBox.intersects(collision)) {
            DecideWallTouched(player, collision, objectTip);
            // 鍵をとったらクリア
            if (MapType::KEY == objectTip.mapType && objectTip.isExists) {
                if (CharaType::PLAYER == player.charaType) {
                    dynamic_cast<Player&>(player).gameFinished = true;
                }
                break;
            }
            // コインは消える
            if (CharaType::PLAYER == player.charaType) {
                if (dynamic_cast<Player&>(player).GetCoin(objectTip)) {
                    continue;
                }
            }
            // 注意:プレイヤーの左側ヒットボックスに触れた場合
            if (IsTouchedLeft(player, collision)) {
                player.objectTipTouching = MapTipTouching::RIGHT;
                if (CharaType::PLAYER == player.charaType) {
                    ActionObjectTip(player, grabbed, objectTip);
                    if (MapType::MOVE_FLOOR_A == objectTip.mapType) {
                        double deltaXAmt = mapCreator.GetObjectMoveXAmt(objectTip);
                        player.MoveX(deltaXAmt);
                    }
                    if (MapType::MOVABLE_OBJ_A == objectTip.mapType) {
                        // TODO: keyWに注意（あとでボタンの配置換えをするから）
                        // 移動中は操作を受け付けない
                        if (objectTip.tipMovingBy == TipMovingBy::NONE && objectTip.falling == false) {
                            objectTip.tipMovingBy = TipMovingBy::RIGHT;
                            player.touchedObjectId = objectTip.id;
                        }
                        player.MoveX((player.delta));
                    }
                }
                break;
            }
            if (IsTouchedRight(player, collision)) {
                player.objectTipTouching = MapTipTouching::LEFT;
                if (CharaType::PLAYER == player.charaType) {
                    ActionObjectTip(player, grabbed, objectTip);
                    if (MapType::MOVE_FLOOR_A == objectTip.mapType) {
                        double deltaXAmt = mapCreator.GetObjectMoveXAmt(objectTip);
                        player.MoveX(deltaXAmt);
                    }
                    if (MapType::MOVABLE_OBJ_A == objectTip.mapType) {
                        // TODO: keyWに注意（あとでボタンの配置換えをするから）
                        //objectTip.MoveX(!KeyW.pressed() ? player.delta : player.delta * 2);
                        // 移動中は操作を受け付けない
                        if (objectTip.tipMovingBy == TipMovingBy::NONE && objectTip.falling == false) {
                            objectTip.tipMovingBy = TipMovingBy::LEFT;
                            player.touchedObjectId = objectTip.id;
                        }
                        player.MoveX(-(player.delta));
                    }
                }
                break;
            }
        }
        objectTip.touched = false;
    }
    for (ObjectTip& objectTip : mapCreator.objectTips) {
        if (objectTip.tipMovingBy == TipMovingBy::NONE) {
            continue;
        }
        if (objectTip.movedDistance.x < 32.0) {
            if (objectTip.tipMovingBy == TipMovingBy::RIGHT) {
                objectTip.MoveX(-4.0);
            } else if (objectTip.tipMovingBy == TipMovingBy::LEFT) {
                objectTip.MoveX(4.0);
            }
            objectTip.movedDistance.x += 4.0;
        }
        else if (objectTip.movedDistance.x >= 32.0) {
            // 1マス分進んだらリセット
            objectTip.movedDistance.x = 0.0;
            objectTip.tipMovingBy = TipMovingBy::NONE;
        }
    }
}

void MapCollisionHelper::CheckBlockCollisionBottom(Player& player, MapScreenHelper& screenHelper)
{
    for (ObjectTip& objectTip : mapCreator.objectTips) {
        if (MapType::MOVABLE_OBJ_A != objectTip.mapType) {
            continue;
        }
        objectTip.falling = true;
        objectTip.MoveY(OBJ_VELOCITY);
        for (MapTip& mapTip : mapCreator.mapTips) {
            if (mapTip.collision.intersects(objectTip.collision)) {
                auto mapTop = mapTip.collision.top();
                auto objectBottom = objectTip.collision.bottom();
                if (mapTop.begin.y <= objectBottom.begin.y) {
                    objectTip.falling = false;
                    objectTip.MoveY(-(objectBottom.begin.y - mapTop.begin.y + 1.0));
                }
            }
        }
        for (ObjectTip& other: mapCreator.objectTips) {
            if (other.collision == objectTip.collision) {
                continue;
            }
            if (other.collision.intersects(objectTip.collision)) {
                auto otherTop = other.collision.top();
                auto objectBottom = objectTip.collision.bottom();
                if (otherTop.begin.y <= objectBottom.begin.y) {
                    objectTip.falling = false;
                    objectTip.MoveY(-(objectBottom.begin.y - otherTop.begin.y + 1.0));
                }
            }
        }
    }
}

void MapCollisionHelper::CheckSide(Enemy& enemy, MapScreenHelper& screenHelper)
{
    // 敵キャラの動いた距離 と プレイヤーのスクリーンを動かした距離を考慮
    Vec2 screenOriginPos = MapScreenHelper::GetEnemyScreenOriginPos(enemy.pos, enemy.originPos, enemy.playerPos);
    CheckSide(enemy, screenHelper, screenOriginPos);
    if (enemy.wallTipTouching != MapTipTouching::NONE) {
        enemy.ReplaceX(enemy.beforePos.x);
    }
}

void MapCollisionHelper::CheckSide(Character& chara, MapScreenHelper& screenHelper, Vec2 screenOriginPos)
{
    MapTip touchedMapTip;
    bool touchedNormalTip = false;
    chara.ignoreWall = false;
    for (MapTip& mapTip : mapCreator.mapTips) {
        RectF collision(mapTip.collision.movedBy(-screenOriginPos));
        if (chara.hitBox.intersects(collision)) {
            if (DecideWallTouched(chara, collision, mapTip)) {
                touchedNormalTip = true;
                break;
            }
            mapTip.touched = false;
        }
    }
}

bool MapCollisionHelper::DecideWallTouched(Character &chara, RectF collision, MapTip &mapTip)
{
    if (!mapTip.blockBehave) {
        return false;
    }
    if (IsTouchedLeft(chara, collision)) {
        chara.wallTipTouching = MapTipTouching::LEFT;
        mapTip.touched = true;
        return true;
    }
    if (IsTouchedRight(chara, collision)) {
        chara.wallTipTouching = MapTipTouching::RIGHT;
        mapTip.touched = true;
        return true;
    }
}

void MapCollisionHelper::ActionObjectTip(Player &player, bool grabbed, ObjectTip &objectTip)
{
    // 梯子
    CheckSideRadderAction(player, objectTip, grabbed);
    if (RadderMode::FIRST_TOUCH == player.radderMode) {
        player.radderMode = RadderMode::GRABBING;
        player.ground = player.pos.y;
        player.time = 0.0;
        player.shortJumpIndex = 0;
        player.jumpFlameCount = 0;
        player.jumpMode = JumpMode::UP;
        player.jumpFlag = false;
        player.jumpFallFlag = false;
        player.shortJumpYList.clear();
    } else if (MapType::MOVE_FLOOR_A == objectTip.mapType) {
        player.ReplaceX(player.beforePos.x);
        MoveOnMovingFloor(player, objectTip);
        player.dashFlag = false;
    }
}

void MapCollisionHelper::MoveOnMovingFloor(Character& chara, ObjectTip objectTip) {
    if (CharaType::NORMAL_ENEMY == chara.charaType) {
        Enemy& enemy = dynamic_cast<Enemy&>(chara);
        enemy.MoveX(objectTip.direction == Direction::RIGHT
            ? objectTip.deltaAmt
            : objectTip.direction == Direction::LEFT
            ? -(objectTip.deltaAmt)
            : 0.0);
        enemy.MoveY(objectTip.direction == Direction::UP
            ? -objectTip.deltaAmt
            : objectTip.direction == Direction::DOWN
            ? objectTip.deltaAmt
            : 0.0);
        enemy.UpdateHitBox();
    }
    if (CharaType::PLAYER == chara.charaType) {
        Player& player = dynamic_cast<Player&>(chara);
        player.MoveX(objectTip.direction == Direction::RIGHT
            ? objectTip.deltaAmt
            : objectTip.direction == Direction::LEFT
            ? -(objectTip.deltaAmt)
            : 0.0);
        player.MoveY(objectTip.direction == Direction::UP
            ? -objectTip.deltaAmt
            : objectTip.direction == Direction::DOWN
            ? objectTip.deltaAmt
            : 0.0);
    }
}

void MapCollisionHelper::CheckSideRadderAction(Player &player, ObjectTip objectTip, bool &grabbed)
{
    // 梯子モードではない + 梯子の頂上？
    if (RadderMode::GRABBING != player.radderMode
            && objectTip.mapType == MapType::TOP_ROCK) {
        player.ReplaceX(player.beforePos.x);
    }
    // 梯子の範囲でスペースをプレス
    else if (RadderMode::NONE == player.radderMode
            && objectTip.mapType == MapType::LADDER
            && KeySpace.down()) {
        // 見栄えのため位置補正
        player.ReplaceX(objectTip.mapGrid.x - 16);
        // 梯子モードにつなげる
        player.radderMode = RadderMode::FIRST_TOUCH;
    }
}

void MapCollisionHelper::CheckHead(Player& player, MapScreenHelper& screenHelper)
{
    Vec2 screenOriginPosition(MapScreenHelper::ChangeWorldToScreenPos(player.pos));
    for (MapTip &mapTip : mapCreator.mapTips) {
        RectF collision(mapTip.collision.movedBy(-screenOriginPosition));
        if (player.hitBox.intersects(collision)) {
            if (!mapTip.blockBehave) {
                continue;
            }
            if (IsTouchedHead(player, collision)) {
                player.topWallFlag = true;
                mapTip.touched = true;
                break;
            }
        }
        mapTip.touched = false;
    }
    for (ObjectTip& objectTip : mapCreator.objectTips) {
        RectF collision(objectTip.collision.movedBy(-screenOriginPosition));
        if (player.hitBox.intersects(collision)) {
            if (!objectTip.blockBehave) {
                continue;
            }
             if (IsTouchedHead(player, collision)) {
                player.topWallFlag = true;
                objectTip.touched = true;
                break;
            }
        }
        objectTip.touched = false;
    }

    if (player.topWallFlag) {
        player.topWallFlag2 = true;
        player.ReplaceY(player.beforePos.y);
    }
}

bool MapCollisionHelper::DecideFootBlock(Character &chara, RectF collision)
{
    Vec2 topBlock = collision.top().end;
    Vec2 foot = chara.hitBox.bottom().end;
    if (IsSunk(foot, topBlock)) { // 地面にめり込んでいるなら
        if (CharaType::PLAYER == chara.charaType) {
            Player& player = dynamic_cast<Player&>(chara);
            player.ReplaceY(chara.pos.y - (foot.y - topBlock.y));
            player.afterDashFlag = false;
        }
        else {
            Enemy& enemy = dynamic_cast<Enemy&>(chara);
            enemy.ReplaceY(chara.pos.y - (foot.y - topBlock.y));
            enemy.jumpMode = JumpMode::NONE;
            enemy.UpdateHitBox();
        }
        chara.gravity = Vec2::Zero();
        chara.ground = chara.pos.y;
        chara.jumpFallFlag = false;
        chara.charaFallMode = CharaFallMode::NONE;
        chara.wallTipTouching = MapTipTouching::BOTTOM;
        return true;
    }
    return false;
}

void MapCollisionHelper::ActionJumpPad(Character &chara, RectF collision) {
    // TODO:chara.wallTipTouching == MapTipTouching::BOTTOM(注意)
    if (CharaType::PLAYER != chara.charaType
        || chara.wallTipTouching == MapTipTouching::BOTTOM) {
        return;
    }
    chara.ground = chara.pos.y;
    if (IsSunk(chara.hitBox.bottom().end, collision.top().end)) {
        if (CharaFallMode::BROW_UP_A != chara.charaFallMode) {
            Player& player = dynamic_cast<Player&>(chara);
            player.ReplaceY(player.ground);
            player.time = 0.0;
            player.shortJumpIndex = 0;
            player.jumpFlameCount = 0;
            player.jumpMode = JumpMode::UP;
            player.jumpFallFlag = false;
            player.shortJumpYList.clear();
            player.charaFallMode = CharaFallMode::BROW_UP_A;
            player.jumpFlag = true;
        }
    }
}

void MapCollisionHelper::CheckFoot(Character& chara, MapScreenHelper& screenHelper)
{
    if (CharaFallMode::BROW_UP_A != chara.charaFallMode) {
        chara.charaFallMode = CharaFallMode::NATURAL_FALL;
    }
    Vec2 screenOriginPos;
    if (CharaType::PLAYER == chara.charaType) {
        screenOriginPos = MapScreenHelper::ChangeWorldToScreenPos(chara.pos);
    }
    else {
        Enemy& enemy = dynamic_cast<Enemy&>(chara);
        screenOriginPos = MapScreenHelper::GetEnemyScreenOriginPos(chara.pos,
                chara.originPos, enemy.playerPos);
    }
    for (MapTip &mapTip : mapCreator.mapTips) {
        RectF collision(mapTip.collision.movedBy(-screenOriginPos));
        if (chara.hitBox.intersects(collision.movedBy(0, -0.1))) { // (-0.1 ... -7)
            if (!mapTip.blockBehave) {
                continue;
            }
            if (DecideFootBlock(chara, collision)) {
                mapTip.touched = true;
                break;
            }
        }
    }
    for (ObjectTip &objectTip : mapCreator.objectTips) {
        RectF collision(objectTip.collision.movedBy(-screenOriginPos));
        if (chara.hitBox.intersects(collision.movedBy(0, -0.1))) { // (-0.1 ... -7)
            if (CharaType::PLAYER == chara.charaType) {
                if (dynamic_cast<Player&>(chara).topWallFlag2
                        && MapType::MOVE_FLOOR_A == objectTip.mapType) {
                    continue;
                }
            }
            bool sunk = objectTip.blockBehave
                    ? DecideFootBlock(chara, collision)
                    : false;
            if (MapType::AIR_BROW_UP == objectTip.mapType) {
                ActionJumpPad(chara, collision);
                continue;
            }
            if (MapType::MOVE_FLOOR_A == objectTip.mapType) {
                MoveOnMovingFloor(chara, objectTip);
                break;
            }
            if (CharaType::PLAYER == chara.charaType) {
                Player& player = dynamic_cast<Player&>(chara);
                if (MapType::DAMAGE_FLOOR_A == objectTip.mapType) {
                    player.OnDamage(objectTip.damage, player.rightwardFlag);
                    break;
                }
                if ((MapType::LOWERMOST == objectTip.mapType
                        && chara.hitBox.top().begin.y > collision.top().begin.y)) {
                    player.radderMode = RadderMode::NONE;
                    break;
                }
            }
            if (CharaType::NORMAL_ENEMY == chara.charaType) {
                if (MapType::ENEMY_WAIT_A == objectTip.mapType) {
                    Enemy& enemy = dynamic_cast<Enemy&>(chara);
                    if (CharaActionState::MOVE == enemy.actionState && RandomBool(0.01)) {
                        enemy.actionState = CharaActionState::WAIT;
                    } else if (CharaActionState::WAIT == enemy.actionState && RandomBool(0.01)) {
                        enemy.actionState = CharaActionState::MOVE;
                    }
                }
            }
        }
    }
}

bool MapCollisionHelper::IsTouchedLeft(Character chara, RectF map)
{
    Vec2 foot = chara.hitBox.bottom().end;
    Vec2 left = chara.hitBox.left().end;
    Vec2 right = chara.hitBox.right().end;

    Vec2 beforeFoot = chara.beforeHitBox.bottom().end;
    Vec2 beforeLeft = chara.beforeHitBox.left().end;
    Vec2 beforeRight = chara.beforeHitBox.right().end;
    // 壁
    Vec2 topBlock = map.top().end;
    Vec2 rightBlock = map.right().end;
    Vec2 leftBlock = map.left().end;
    Vec2 bottomBlock = map.bottom().end;

    //bool fallChara = chara.beforeHitBox.bottom().end.y < topBlock.y
    //    && chara.beforeHitBox.bottom().end.y < bottomBlock.y;
    bool touchLeft = topBlock.y < chara.beforeHitBox.bottom().end.y
            && left.x <= rightBlock.x
            && right.x > rightBlock.x;
    if (chara.charaType == CharaType::PLAYER) {
        chara.font(U"touchRigh：", touchLeft).draw(Scene::Center());
    }
    return touchLeft;
    //return foot.y > topBlock.y + 0.1
    //    && left.x <= rightBlock.x
    //    && right.x > rightBlock.x;
}

bool MapCollisionHelper::IsTouchedRight(Character chara, RectF map)
{
    Vec2 foot = chara.hitBox.bottom().end;
    Vec2 left = chara.hitBox.left().end;
    Vec2 right = chara.hitBox.right().end;

    Vec2 topBlock = map.top().end;
    Vec2 rightBlock = map.right().end;
    Vec2 leftBlock = map.left().end;
    bool touchRight = topBlock.y < chara.beforeHitBox.bottom().end.y
            && left.x <= leftBlock.x
            && right.x > leftBlock.x;
    if (chara.charaType == CharaType::PLAYER) {
        //chara.font(U"touchRigh：", touchRight).draw(Scene::Center());
    }
    return touchRight;
    //return foot.y > topBlock.y + 0.1
    //    && left.x <= leftBlock.x
    //    && right.x > leftBlock.x;
}

bool MapCollisionHelper::IsTouchedHead(Player player, RectF map)
{
    Vec2 head = player.hitBox.top().end;
    Vec2 foot = player.hitBox.bottom().end;
    Vec2 bottomBlock = map.bottom().end;
    Vec2 rightBlock = map.right().end;
    Vec2 leftBlock = map.left().end;
    return head.y < bottomBlock.y + 0.1 && foot.y > bottomBlock.y && leftBlock.x < rightBlock.x;
}

bool MapCollisionHelper::IsSunk(Vec2 foot, Vec2 topBlock)
{
    // 地面にめり込んでいるなら
    return foot.y >= topBlock.y - 0.1;
}