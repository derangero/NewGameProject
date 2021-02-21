#include "ObjectCollisionHelper.hpp"

ObjectCollisionHelper::ObjectCollisionHelper()
{
}

void ObjectCollisionHelper::PlayerCheckWallInit(Player& player)
{
    //player.isSlope = false;
    player.touchedLeftObjects.clear();
    player.touchedRightObjects.clear();
}

void ObjectCollisionHelper::Check(MapCreator& mapCreator, Player& player, MapScreenHelper& screenHelper, TimeManager &tManager)
{
    player.objectTipTouching = MapTipTouching::NONE;
    //if (RadderMode::GRABBED == player.radderMode) {
    //    if (KeyW.pressed()) {
    //        player.MoveY(-player.delta / 2);
    //    }
    //    else if (KeyS.pressed()) {
    //        player.MoveY(player.delta / 2);
    //    }
    //    else if (KeySpace.pressed()) {
    //        player.radderMode = RadderMode::RELEASE;
    //        player.waitFlag = false;
    //    }
    //    player.ground = player.pos.y;
    //}
    //else if (RadderMode::NONE == player.radderMode) {
    //    player.waitFlag = false;
    //}
    CheckSide(mapCreator.objectTips, player, screenHelper, tManager);
    if (!player.waitFlag || RadderMode::GRABBING != player.radderMode) {
        CheckHead(mapCreator.objectTips, player, screenHelper);
    }

    CheckFoot(mapCreator.objectTips, player, screenHelper);
    PlayerCheckWallInit(player);
}

void ObjectCollisionHelper::CheckSide(Array<ObjectTip>& objectTips, Player& player, MapScreenHelper& screenHelper, TimeManager& tManager)
{
    //bool grabbed = true;
    //ObjectTip touchedObjectTip;
    //Vec2 screenOriginPosition(screenHelper.MoveMapObject(player.pos, objectTips));
    //for (ObjectTip &objectTip : objectTips) {
    //    RectF collision(objectTip.collision.movedBy(-screenOriginPosition));
    //    if (player.hitBox.intersects(collision)) {
    //        touchedObjectTip = objectTip;
    //        if (MapType::KEY == objectTip.mapType && objectTip.isExists) {
    //            grabbed = false;
    //            player.gameFinished = true;
    //            break;
    //        }
    //        if (player.GetCoin(objectTip)) {
    //            grabbed = false;
    //            continue;
    //        };
    //        if (IsTouchedByPlayerLeft(player, collision)) {
    //            CheckSideAction(player, objectTip);
    //            player.objectTipTouching = MapTipTouching::LEFT;
    //            break;
    //        }
    //        if (IsTouchedByPlayerRight(player, collision)) {
    //            CheckSideAction(player, objectTip);
    //            player.objectTipTouching = MapTipTouching::RIGHT;
    //            break;
    //        }
    //    }
    //    player.objectTipTouching = MapTipTouching::NONE;
    //}
    //if (player.objectTipTouching != MapTipTouching::NONE) {
    //    if (grabbed && KeyEnter.pressed()) {
    //        player.radderMode = RadderMode::GRABBED;
    //        player.waitFlag = true;
    //        player.ground = player.pos.y;
    //        player.time = 0.0;
    //        player.shortJumpIndex = 0;
    //        player.jumpFlameCount = 0;
    //        player.jumpMode = JumpMode::UP;
    //        player.jumpFlag = false;
    //        player.jumpFallFlag = false;
    //        player.shortJumpYList.clear();
    //    }
    //    else if (MapType::MOVE_FLOOR_A == touchedObjectTip.mapType) {
    //        player.ReplaceX(player.beforePos.x);
    //        MovePlayerOnMovingFloor(player, touchedObjectTip);
    //        player.dashFlag = false;
    //    }
    //}
}

void ObjectCollisionHelper::CheckSideAction(Player &player, ObjectTip objectTip)
{
    if (objectTip.mapType == MapType::TOP_ROCK
            && RadderMode::GRABBING != player.radderMode) {
        player.ReplaceX(player.beforePos.x);
    }
    else if (KeyEnter.pressed()) {
        player.ReplaceX(objectTip.mapGrid.x - 16);
    }
}

void ObjectCollisionHelper::CheckFoot(Array<ObjectTip>& mapTips, Player& player, MapScreenHelper& screenHelper)
{
    Vec2 screenOriginPosition(screenHelper.MoveMapObject(player.pos, mapTips));
    ObjectTip touchedObjectTip;
    for (ObjectTip &mapTip : mapTips) {
        RectF collision(mapTip.collision.movedBy(-screenOriginPosition));
        if (!player.hitBox.intersects(collision.movedBy(0, -0.1))) {// (-0.1 ... -7)
            continue;
        }
        touchedObjectTip = mapTip;
        Vec2 foot = player.hitBox.bottom().end;
        Vec2 topBlock = collision.top().end;
        bool sunk = IsSunk(foot, topBlock);
        if (MapType::AIR_BROW_UP == mapTip.mapType) {
            player.ground = player.pos.y;
            if (sunk) { // 地面にめり込んでいるなら
                if (CharaFallMode::BROW_UP_A != player.charaFallMode) {
                    player.ReplaceY(player.ground);
                    player.time = 0.0;
                    player.shortJumpIndex = 0;
                    player.jumpFlameCount = 0;
                    player.jumpMode = JumpMode::UP;
                    player.jumpFallFlag = false;
                    player.shortJumpYList.clear();
                    player.charaFallMode = CharaFallMode::BROW_UP_A;
                    player.jumpFlag = true;
                    break; // ２つ以上のブロックをまたいだ場合を考慮
                }
            }
        }
        if (sunk &&
            (MapType::MOVE_FLOOR_A == mapTip.mapType
                || MapType::DAMAGE_FLOOR_A == mapTip.mapType
                || MapType::ENEMY_WAIT_A == mapTip.mapType)) {
            // 基本的な床として機能
            player.ReplaceY(player.pos.y - (foot.y - topBlock.y));
            player.ground = player.pos.y;
            player.charaFallMode = CharaFallMode::NONE;
            player.jumpFallFlag = false;
            player.afterDashFlag = false;
            // 床の特性ごとに処理
            if (MapType::MOVE_FLOOR_A == mapTip.mapType) {
                MovePlayerOnMovingFloor(player, touchedObjectTip);
            }
            if (MapType::DAMAGE_FLOOR_A == mapTip.mapType) {
                player.OnDamage(mapTip.damage, player.rightwardFlag);
            }
            break;
        }
        if ((mapTip.mapType == MapType::LOWERMOST
            && player.hitBox.top().begin.y > collision.top().begin.y)) {
            player.radderMode = RadderMode::NONE;
            break;
        }
        if (RadderMode::GRABBING == player.radderMode) {
            break;
        }
        if (mapTip.mapType != MapType::TOP_ROCK || RadderMode::RELEASE == player.radderMode) {
            continue;
        }
        if (mapTip.mapType == MapType::TOP_ROCK && KeyS.pressed() && KeyEnter.pressed()) {
            break;
        }
        if (sunk && MapType::AIR_BROW_UP != mapTip.mapType) { // 地面にめり込んでいるなら
            player.ReplaceY(player.pos.y - (foot.y - topBlock.y));
            player.ground = player.pos.y;
            player.charaFallMode = CharaFallMode::NONE;
            player.jumpFallFlag = false;
            player.afterDashFlag = false;
            player.isSlope = false;
            player.isSlopeUp = false;
            break; // ２つ以上のブロックをまたいだ場合を考慮
        }
        if (RadderMode::NONE == player.radderMode) {
            player.radderMode = RadderMode::RELEASE;
        }
    }
}

void ObjectCollisionHelper::MovePlayerOnMovingFloor(Player &player, ObjectTip touchedObjectTip) {
    player.MoveX(touchedObjectTip.direction == Direction::RIGHT
        ? touchedObjectTip.deltaAmt
        : touchedObjectTip.direction == Direction::LEFT
        ? -(touchedObjectTip.deltaAmt)
        : 0.0);
    player.MoveY(touchedObjectTip.direction == Direction::UP
        ? -touchedObjectTip.deltaAmt
        : touchedObjectTip.direction == Direction::DOWN
        ? touchedObjectTip.deltaAmt
        : 0.0);
}

void ObjectCollisionHelper::CheckHead(Array<ObjectTip>& objectTips, Player& player, MapScreenHelper& screenHelper)
{
    bool touched = false;
    Vec2 screenOriginPosition(MapScreenHelper::ChangeWorldToScreenPos(player.pos));
    for (ObjectTip& objectTip : objectTips) {
        if (MapType::MOVE_FLOOR_A != objectTip.mapType) {
            continue;
        }
        RectF collision(objectTip.collision.movedBy(-screenOriginPosition));
        if (player.hitBox.intersects(collision)) {
            if (IsTouchedHeadWall(player, collision)) {
                player.topWallFlag = true;
                touched = true;
            }
        }
    }
    if (touched && player.topWallFlag) {
        player.topWallFlag2 = true;
        player.ReplaceY(player.beforePos.y);
    }
}

bool ObjectCollisionHelper::IsSunk(Vec2 foot, Vec2 topBlock)
{
    // 地面にめり込んでいるなら
    return foot.y >= topBlock.y - 0.1;
}

bool ObjectCollisionHelper::IsTouchedHeadWall(Player player, RectF collision)
{
    Vec2 head = player.hitBox.top().end;
    Vec2 foot = player.hitBox.bottom().end;
    Vec2 bottomBlock = collision.bottom().end;
    Vec2 rightBlock = collision.right().end;
    Vec2 leftBlock = collision.left().end;
    return head.y <= bottomBlock.y + 0.1 && foot.y >= bottomBlock.y && leftBlock.x <= rightBlock.x;
}

bool ObjectCollisionHelper::IsTouchedByPlayerLeft(Player player, RectF map)
{
    // プレイヤー
    Vec2 foot = player.hitBox.bottom().end;
    Vec2 left = player.hitBox.left().end;
    Vec2 right = player.hitBox.right().end;
    // 壁
    Vec2 topBlock = map.top().end;
    Vec2 rightBlock = map.right().end;
    Vec2 leftBlock = map.left().end;
    return foot.y > topBlock.y + 0.1 && left.x <= rightBlock.x && right.x > leftBlock.x;
}

bool ObjectCollisionHelper::IsTouchedByPlayerRight(Player player, RectF map)
{
    Vec2 foot = player.hitBox.bottom().end;
    Vec2 left = player.hitBox.left().end;
    Vec2 right = player.hitBox.right().end;

    Vec2 topBlock = map.top().end;
    Vec2 rightBlock = map.right().end;
    Vec2 leftBlock = map.left().end;
    return foot.y > topBlock.y + 0.1 && left.x <= leftBlock.x && right.x > rightBlock.x;
}

bool ObjectCollisionHelper::CheckRightDownSlope(Player& player, ObjectTip mapTip, Vec2 screenOriginPosition)
{
    Quad quadDetection(mapTip.quadDetection);
    quadDetection = quadDetection.movedBy(-screenOriginPosition);
    Triangle triDetection(quadDetection.p0.asPoint(), quadDetection.p1.asPoint(), quadDetection.p2.asPoint());
    bool detected = player.hitBox.movedBy(0, player.rightwardFlag ? 16 : 0).intersects(triDetection);
    Vec2 mapPos = Vec2(
        mapTip.mapGrid.x - screenOriginPosition.x,
        mapTip.mapGrid.y - screenOriginPosition.y);
    if (detected) {
        player.isSlope = true;
        Line left = player.hitBox.left();
        Vec2 begin(left.end.asPoint().movedBy(0, 0));
        Vec2 end(left.begin.asPoint().movedBy(0, player.rightwardFlag ? 16 : 0));
        auto detected = triDetection.intersectsAt(Line(begin, end));
        if (!detected.has_value()) {
            return false;
        }

        double upY = 0.0;
        if (player.walkFlag || player.jumpFallFlag) {
            if (detected.value().size() == 1) { // 辺１つ
                upY += detected.value()[0].y - player.hitBox.h;
                player.MoveY(player.rightwardFlag ? (upY - player.pos.y) : -(player.pos.y - upY));
            }
            else {
                if (player.rightwardFlag) {
                    upY += detected.value()[0].y;
                    player.ReplaceY(upY - player.hitBox.h);
                }
                else {
                    upY += detected.value()[1].y - detected.value()[0].y; //底辺 - 辺
                    player.ReplaceY(player.pos.y + (player.rightwardFlag ? upY : -upY));

                }
            }
            player.beforePos.y = player.pos.y;
        }
        //ActionByRightDownSlope(player);
        InitActionBySlope(player);
        return true;
    }
    return false;
}

void ObjectCollisionHelper::ActionByRightDownSlope(Player& player)
{
    if (player.walkFlag) {
        player.ReplaceY(player.pos.y + (player.rightwardFlag ? player.delta / 2 : -player.delta / 2));
        player.beforePos.y = player.pos.y;
    }
    InitActionBySlope(player);
}

void ObjectCollisionHelper::InitActionBySlope(Player& player)
{
    player.ground = player.pos.y;
    player.charaFallMode = CharaFallMode::NATURAL_FALL;
    player.jumpFallFlag = false;
    player.afterDashFlag = false;
    player.isSlope = true;
    player.isSlopeUp = !player.rightwardFlag;
}
