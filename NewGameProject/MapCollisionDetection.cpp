#include "MapCollisionDetection.hpp"

MapCollisionDetection::MapCollisionDetection()
{
}

void MapCollisionDetection::PlayerCheckWallInit(Player& player)
{
    player.naturalFallFlag = true;
    player.leftWallFlag = false;
    player.rightWallFlag = false;
    player.topWallFlag = false;
}

void MapCollisionDetection::CheckWall(Array<MapTip>& mapTips, Player& player, MapScreenHelper& screenHelper)
{
    if (player.waitFlag) {
        return;
    }
    PlayerCheckWallInit(player);
    CheckSideWall(mapTips, player, screenHelper);
    CheckHeadWall(mapTips, player, screenHelper);
    CheckFootWall(mapTips, player, screenHelper);
}

/// <summary>
/// �L�������[�̓����蔻����s���܂��B
/// ���������͈ꎞ�I�ɒn�ʂɂ߂荞�ތ`�ɂȂ�̂Ńt���O�������܂�
/// </summary>
/// <param name="mapTips">�}�b�v�`�b�v�N���X�̃��X�g</param>
/// <param name="player">�v���C���[�N���X</param>
/// <param name="screenHelper">�}�b�v�w���p�[�N���X</param>
void MapCollisionDetection::CheckSideWall(Array<MapTip>& mapTips, Player& player, MapScreenHelper& screenHelper)
{
    Vec2 screenOriginPosition(MapScreenHelper::ChangeWorldToScreenPos(player.pos));
    for (MapTip &mapTip : mapTips) {
        RectF mapDetection(mapTip.detection);
        mapDetection = mapDetection.movedBy(-screenOriginPosition);
        if (mapTip.mapNumber == 114) { //TODO:�⓹�p�B��Œ萔�ɂ��邱��
            continue;
        }
        if (player.detection.intersects(mapDetection)) {
            if (IsTouchedLeftWall(player, mapDetection)) {
                player.leftWallFlag = true;
                mapTip.isTouched = true;
                break;
            }
            else if (IsTouchedRightWall(player, mapDetection)) {
                player.rightWallFlag = true;
                mapTip.isTouched = true;
                break;
            }
        }
        mapTip.isTouched = false;
    }


    if (player.leftWallFlag || player.rightWallFlag) {
        if (BulletMode::WARP == player.bulletMode) {
            player.ReplacePos(player.beforePos);
        }
        else {
            player.ReplaceX(player.beforePos.x);
        }

        player.dashFlag = false;
    }
}

void MapCollisionDetection::CheckHeadWall(Array<MapTip>& mapTips, Player& player, MapScreenHelper& screenHelper)
{
    Vec2 screenOriginPosition(MapScreenHelper::ChangeWorldToScreenPos(player.pos));
    for (MapTip &mapTip : mapTips) {
        RectF map(mapTip.detection);
        map = map.movedBy(-screenOriginPosition);
        if (mapTip.mapNumber == 172 || mapTip.mapNumber == SLOPE_LEFT_22_5_A || mapTip.mapNumber == SLOPE_LEFT_22_5_B || mapTip.mapNumber == SLOPE_LEFT_22_5_C) {
            continue;
        }

        if (player.detection.intersects(map)) {
            if (IsTouchedHeadWall(player, map)) {
                player.topWallFlag = true;
                mapTip.isTouched = true;
            }
        }
        mapTip.isTouched = false;
    }
    if (player.topWallFlag) {
        player.topWallFlag2 = true;
        player.ReplaceY(player.beforePos.y);
    }
}

void MapCollisionDetection::CheckFootWall(Array<MapTip>& mapTips, Player& player, MapScreenHelper& screenHelper)
{
    Vec2 screenOriginPosition(MapScreenHelper::ChangeWorldToScreenPos(player.pos));
    for (MapTip &mapTip : mapTips) {
        RectF mapDetection(mapTip.detection);
        mapDetection = mapDetection.movedBy(-screenOriginPosition);
        Vec2 mapPos = Vec2(
            mapTip.mapGridX - screenOriginPosition.x,
            mapTip.mapGridY - screenOriginPosition.y);
        if (player.detection.intersects(mapDetection.movedBy(0, -0.1))) { // (-0.1 ... -7)
            Vec2 topBlock = mapDetection.top().end;
            Vec2 foot = player.detection.bottom().end;
            if (mapTip.mapNumber == 114) {
                
                if (foot.y >= mapDetection.bottom().end.y) {
                    double diff1 = mapDetection.bottom().end.y - foot.y;
                    player.ReplaceY(player.pos.y - diff1 - 8);
                    player.groundY = player.pos.y;
                }
                player.naturalFallFlag = false;
                player.jumpFallFlag = false;
                player.afterDashFlag = false;
                break;

            } else if (foot.y >= topBlock.y - 0.1) { // �n�ʂɂ߂荞��ł���Ȃ�
                player.ReplaceY(player.pos.y - (foot.y - topBlock.y));
                player.groundY = player.pos.y;
                player.naturalFallFlag = false;
                player.jumpFallFlag = false;
                player.afterDashFlag = false;
                player.isSlope = false;
                player.isSlopeUp = false;
                mapTip.isTouched = true;
                break; // �Q�ȏ�̃u���b�N���܂������ꍇ���l��
            }
        }
    }
}

bool MapCollisionDetection::IsTouchedLeftWall(Player player, RectF map)
{
    // �v���C���[
    Vec2 foot = player.detection.bottom().end;
    Vec2 left = player.detection.left().end;
    Vec2 right = player.detection.right().end;
    // ��
    Vec2 topBlock = map.top().end;
    Vec2 rightBlock = map.right().end;
    Vec2 leftBlock = map.left().end;
    return foot.y > topBlock.y + 0.1 && left.x <= rightBlock.x && right.x > rightBlock.x;
}

bool MapCollisionDetection::IsTouchedRightWall(Player player, RectF map)
{
    Vec2 foot = player.detection.bottom().end;
    Vec2 left = player.detection.left().end;
    Vec2 right = player.detection.right().end;

    Vec2 topBlock = map.top().end;
    Vec2 rightBlock = map.right().end;
    Vec2 leftBlock = map.left().end;
    return foot.y > topBlock.y + 0.1 && left.x <= leftBlock.x && right.x > leftBlock.x;
}

bool MapCollisionDetection::IsTouchedHeadWall(Player player, RectF map)
{
    Vec2 head = player.detection.top().end;
    Vec2 foot = player.detection.bottom().end;
    Vec2 bottomBlock = map.bottom().end;
    Vec2 rightBlock = map.right().end;
    Vec2 leftBlock = map.left().end;
    return head.y < bottomBlock.y + 0.1 && foot.y > bottomBlock.y && leftBlock.x < rightBlock.x;
}

/// <summary>
/// ���o��X���[�v�̓����蔻��p��Triangle���擾���܂��B
/// </summary>
/// <param name="mapPos">�}�b�v�`�b�v�̈ʒu</param>
/// <returns>Triangle�I�u�W�F�N�g</returns>
Triangle MapCollisionDetection::GetTriangleForLeftSlope(Vec2 mapPos)
{
    return Triangle(mapPos.movedBy(0, 8), mapPos.movedBy(16, 16), mapPos.movedBy(0, 16));
}

void MapCollisionDetection::ActionByLeftSlope(Player &player)
{
    if (player.walkFlag) {
        player.ReplaceY(player.pos.y + (player.rightwardFlag ? player.delta / 2 : -player.delta / 2));
        player.beforePos.y = player.pos.y;
    }
    InitActionByLeftSlope(player);
}

void MapCollisionDetection::InitActionByLeftSlope(Player& player)
{
    player.groundY = player.pos.y;
    player.naturalFallFlag = false;
    player.jumpFallFlag = false;
    player.afterDashFlag = false;
    player.isSlope = true;
    player.isSlopeUp = !player.rightwardFlag;
}

bool MapCollisionDetection::CheckSlopeLeft22HalfA(Player& player, Vec2 mapPos)
{
    Quad quad = MapTip::GetQuadForLeftSlope(mapPos);
    if (player.detection.intersects(quad)) {
        ActionByLeftSlope(player);
        return true;
    }
    return false;
}

bool MapCollisionDetection::CheckSlopeLeft22HalfB(Player& player, Vec2 mapPos)
{
    Triangle tri2 = GetTriangleForLeftSlope(mapPos).draw(Palette::Aqua);
    if (player.detection.intersects(tri2)) { // (-0.1 ... -7)
        ActionByLeftSlope(player);
        return true;
    }
    return false;
}

bool MapCollisionDetection::CheckSlopeLeft22HalfC(Player& player, Vec2 mapPos)
{
    Triangle tri2 = GetTriangleForLeftSlope(mapPos).draw(Palette::Aqua);
    if (player.detection.intersects(tri2)) { // (-0.1 ... -7)
        InitActionByLeftSlope(player);
        Vec2 foot = player.detection.bottom().end;
        // �X���[�v������Ƃ��ɏ��ɒ��񂾂�
        if (player.rightwardFlag && tri2.p1.y < foot.y) {
            double diff = foot.y - tri2.p1.y;
            player.ReplaceY(player.pos.y - diff);
            player.groundY = player.pos.y;
            player.isSlope = false;
        }
        return true;
    }
    return false;
}
