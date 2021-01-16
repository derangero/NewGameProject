#include "ObjectCollisionDetection.hpp"

ObjectCollisionDetection::ObjectCollisionDetection()
{
}

void ObjectCollisionDetection::PlayerCheckWallInit(Player& player)
{
    //player.isSlope = false;
    player.touchedLeftObjects.clear();
    player.touchedRightObjects.clear();
}

void ObjectCollisionDetection::Check(Array<MapObjectTip>& mapTips, Player& player, MapScreenHelper& screenHelper, TimeManager &tManager)
{
    if (RadderMode::GRABBED == player.radderMode) {
        if (KeyW.pressed()) {
            player.MoveY(-player.delta / 2);
        }
        else if (KeyS.pressed()) {
            player.MoveY(player.delta / 2);
        }
        else if (KeySpace.pressed()) {
            player.radderMode = RadderMode::RELEASE;
            player.waitFlag = false;
        }
        player.groundY = player.pos.y;
    }
    else if (RadderMode::NONE == player.radderMode) {
        player.waitFlag = false;
    }
    CheckFoot(mapTips, player, screenHelper);
    if (player.waitFlag || RadderMode::GRABBED == player.radderMode) {
        return;
    }
    PlayerCheckWallInit(player);
    CheckSide(mapTips, player, screenHelper, tManager);
    //CheckHeadWall(mapTips, player, screenHelper);
}

void ObjectCollisionDetection::CheckSide(Array<MapObjectTip>& mapObjectTips, Player& player, MapScreenHelper& screenHelper, TimeManager& tManager)
{
    Vec2 screenOriginPosition(screenHelper.MoveMapObject(player.pos, mapObjectTips));
    for (auto i : step(mapObjectTips.size())) {
        MapObjectTip mapObjectTip = mapObjectTips[i];
        RectF mapObjectDetection(mapObjectTip.detection);
        mapObjectDetection = mapObjectDetection.movedBy(-screenOriginPosition);
        // プレイヤー
        Vec2 foot = player.detection.bottom().end;
        Vec2 left = player.detection.left().end;
        Vec2 right = player.detection.right().end;
        // 壁
        Vec2 topBlock = mapObjectDetection.top().end;
        Vec2 rightBlock = mapObjectDetection.right().end;
        Vec2 leftBlock = mapObjectDetection.left().end;

        double diff = (leftBlock.x - left.x) / 2;
        
        if (player.detection.intersects(mapObjectDetection)) {
            if (IsTouchedLeftWall(player, mapObjectDetection)) {
                if (KeyEnter.pressed()) {
                    player.ReplaceX(mapObjectTip.mapGridX - 16);
                }
                player.touchedLeftObjects.push_back(mapObjectTip.type);
                break;
            }
            if (IsTouchedRightWall(player, mapObjectDetection)) {
                player.touchedRightObjects.push_back(mapObjectTip.type);
                break;
            }
        }
    }
    if (!player.touchedLeftObjects.isEmpty() || !player.touchedRightObjects.isEmpty()) {
        if (KeyEnter.pressed()) {
            player.radderMode = RadderMode::GRABBED;
            player.waitFlag = true;
            player.groundY = player.pos.y;
            player.time = 0.0;
            player.shortJumpIndex = 0;
            player.jumpFlameCount = 0;
            player.jumpMode = JumpMode::UP;
            player.jumpFlag = false;
            player.jumpFallFlag = false;
            player.shortJumpYList.clear();
        }
    }

}

void ObjectCollisionDetection::CheckFoot(Array<MapObjectTip>& mapTips, Player& player, MapScreenHelper& screenHelper)
{
    Vec2 screenOriginPosition(screenHelper.MoveMapObject(player.pos, mapTips));
    bool detected = false;
    for (auto i : step(mapTips.size())) {
        MapObjectTip mapTip = mapTips[i];
        if (mapTip.type == RIGHT_SLOPE) {
            if (CheckRightDownSlope(player, mapTip, screenOriginPosition)) {
                break;
            }
        }
        else {
            MapObjectTip mapTip = mapTips[i];
            RectF mapDetection(mapTip.detection);
            mapDetection = mapDetection.movedBy(-screenOriginPosition);
            Vec2 mapPos = Vec2(
                mapTip.mapGridX - screenOriginPosition.x,
                mapTip.mapGridY - screenOriginPosition.y);
            if (player.detection.intersects(mapDetection.movedBy(0, -0.1))) { // (-0.1 ... -7)
                detected = true;
                Vec2 topBlock = mapDetection.top().end;
                Vec2 foot = player.detection.bottom().end;
                if ((mapTip.type == LOWERMOST
                    && player.detection.top().begin.y > mapDetection.top().begin.y)) {
                    detected = false;
                    break;
                }
                if (RadderMode::GRABBED == player.radderMode) {
                    break;
                }
                if (mapTip.type != TOP_ROCK || RadderMode::RELEASE == player.radderMode) {
                    continue;
                }
                if (mapTip.type == TOP_ROCK && KeyS.pressed() && KeyEnter.pressed()) {
                    break;
                }
                if (foot.y >= topBlock.y - 0.1) { // 地面にめり込んでいるなら
                    player.ReplaceY(player.pos.y - (foot.y - topBlock.y));
                    player.groundY = player.pos.y;
                    player.naturalFallFlag = false;
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
    }
    if (!detected) {
        bool a = 0;
        player.radderMode = RadderMode::NONE;
    }
}

bool ObjectCollisionDetection::IsTouchedLeftWall(Player player, RectF map)
{
    // プレイヤー
    Vec2 foot = player.detection.bottom().end;
    Vec2 left = player.detection.left().end;
    Vec2 right = player.detection.right().end;
    // 壁
    Vec2 topBlock = map.top().end;
    Vec2 rightBlock = map.right().end;
    Vec2 leftBlock = map.left().end;
    return foot.y > topBlock.y + 0.1 && left.x <= rightBlock.x && right.x > leftBlock.x;
}

bool ObjectCollisionDetection::IsTouchedRightWall(Player player, RectF map)
{
    Vec2 foot = player.detection.bottom().end;
    Vec2 left = player.detection.left().end;
    Vec2 right = player.detection.right().end;

    Vec2 topBlock = map.top().end;
    Vec2 rightBlock = map.right().end;
    Vec2 leftBlock = map.left().end;
    return foot.y > topBlock.y + 0.1 && left.x <= leftBlock.x && right.x > rightBlock.x;
}

bool ObjectCollisionDetection::CheckRightDownSlope(Player& player, MapObjectTip mapTip, Vec2 screenOriginPosition)
{
    Quad quadDetection(mapTip.quadDetection);
    quadDetection = quadDetection.movedBy(-screenOriginPosition);
    Triangle triDetection(quadDetection.p0.asPoint(), quadDetection.p1.asPoint(), quadDetection.p2.asPoint());
    bool detected = player.detection.movedBy(0, player.rightwardFlag ? 16 : 0).intersects(triDetection);
    Vec2 mapPos = Vec2(
        mapTip.mapGridX - screenOriginPosition.x,
        mapTip.mapGridY - screenOriginPosition.y);
    if (detected) {
        player.isSlope = true;
        Line left = player.detection.left();
        Vec2 begin(left.end.asPoint().movedBy(0, 0));
        Vec2 end(left.begin.asPoint().movedBy(0, player.rightwardFlag ? 16 : 0));
        auto detected = triDetection.intersectsAt(Line(begin, end));
        if (!detected.has_value()) {
            return false;
        }

        double upY = 0.0;
        if (player.walkFlag || player.jumpFallFlag) {
            if (detected.value().size() == 1) { // 辺１つ
                upY += detected.value()[0].y - player.detection.h;
                player.MoveY(player.rightwardFlag ? (upY - player.pos.y) : -(player.pos.y - upY));
            }
            else {
                if (player.rightwardFlag) {
                    upY += detected.value()[0].y;
                    player.ReplaceY(upY - player.detection.h);
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

void ObjectCollisionDetection::ActionByRightDownSlope(Player& player)
{
    if (player.walkFlag) {
        player.ReplaceY(player.pos.y + (player.rightwardFlag ? player.delta / 2 : -player.delta / 2));
        player.beforePos.y = player.pos.y;
    }
    InitActionBySlope(player);
}

void ObjectCollisionDetection::InitActionBySlope(Player& player)
{
    player.groundY = player.pos.y;
    player.naturalFallFlag = false;
    player.jumpFallFlag = false;
    player.afterDashFlag = false;
    player.isSlope = true;
    player.isSlopeUp = !player.rightwardFlag;
}
