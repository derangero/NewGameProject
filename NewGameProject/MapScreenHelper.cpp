#include "MapScreenHelper.hpp"

MapScreenHelper::MapScreenHelper()
{
}

/// <summary>
/// �J�������W����X�N���[�����W�̌��_�ɕϊ����܂��i�����W�j
/// </summary>
/// <param name="pos">�ϊ�������W</param>
/// <returns>�ϊ��������W</returns>
Vec2 MapScreenHelper::ChangeWorldToScreenPos(Vec2 pos)
{
    Vec2 screenOriginPosition = GetScreenOriginPosition(pos);
    return screenOriginPosition;
}

Vec2 MapScreenHelper::GetScreenOriginPosition(Vec2 pos) {
    // �J�������Œ肷�邵�Ȃ���

    double movedX = IsMoveCameraX(pos.x) ? PLAYER_STAND_POS.x - pos.x : 0;
    double movedY = IsMoveCameraY(pos.y) ? PLAYER_STAND_POS.y - pos.y : 0;
    // Scene::Width() -> 800
    // Scene::Height() -> 600
    Vec2 screenOriginPosition(
        (CAMERA_POS.x - Scene::Width() / 2.0) - movedX,
        (CAMERA_POS.y - Scene::Height() / 2.0) - movedY); 

    return screenOriginPosition;
};

Vec2 MapScreenHelper::GetEnemyScreenOriginPos(Vec2 enemyPos, Vec2 enemyOriginPos, Vec2 playerPos) {
    double movedX = IsMoveEnemyCameraX(enemyPos.x, enemyOriginPos.x)
            ? enemyOriginPos.x - enemyPos.x
            : 0;
    double movedY = IsMoveEnemyCameraY(enemyPos.y, enemyOriginPos.y)
            ? enemyOriginPos.y - enemyPos.y
            : 0;
    double playerMovedX = IsMoveCameraX(playerPos.x) ? PLAYER_STAND_POS.x - playerPos.x : 0;
    double playerMovedY = IsMoveCameraY(playerPos.y) ? PLAYER_STAND_POS.y - playerPos.y : 0;
    Vec2 screenOriginPosition(
        (CAMERA_POS.x - Scene::Width() / 2.0) - movedX - playerMovedX,
        (CAMERA_POS.y - Scene::Height() / 2.0) - movedY - playerMovedY);

    return screenOriginPosition;
};

Vec2 MapScreenHelper::MoveMapObject(Vec2 pos, Array<ObjectTip>& mapTips)
{
    Vec2 screenOriginPosition = GetScreenOriginPosition(pos);
    for (auto mapTip : mapTips) {
        //mapTips[i].detection.movedBy(-screenOriginPosition);
    }
    return screenOriginPosition;
}

Vec2 MapScreenHelper::FixPosition(Vec2 pos, Vec2 targetPos)
{
    return targetPos.movedBy(-GetScreenOriginPosition(pos));
};

Vec2 MapScreenHelper::FixPositionFromPlayerPos(Vec2 basePos, Vec2 targetPos)
{
    double movedX = IsMoveCameraX(basePos.x) ? basePos.x - PLAYER_STAND_POS.x : 0;
    double movedY = IsMoveCameraY(basePos.y) ? basePos.y - PLAYER_STAND_POS.y : 0;
    return Vec2(targetPos.x - movedX, targetPos.y - movedY);
}
Vec2 MapScreenHelper::GetObjectPos(Vec2 objectPos, Vec2 playerPos)
{
    Vec2 screenOriginPosition2(MapScreenHelper::ChangeWorldToScreenPos(objectPos));
    Vec2 result = MapScreenHelper::FixPositionFromPlayerPos(
        playerPos, objectPos.movedBy(0, -screenOriginPosition2.y));
    return result;

}
bool MapScreenHelper::IsMoveCameraX(double playerX)
{
    bool isLeftMoveCameraX = PLAYER_STAND_POS.x <= playerX;
    bool isRightMoveCameraX = MAX_SCREEN_SIZE.x - CAMERA_POS.x >= playerX;
    return isLeftMoveCameraX && isRightMoveCameraX;
};

bool MapScreenHelper::IsMoveCameraY(double playerY)
{
    // TODO: y�ɃL�����̍������l������K�v���邩��
    return  0 > playerY;
    //return  -(CAMERA_POS.y - Scene::Height() / 2.0) < playerY;
};

bool MapScreenHelper::IsMoveEnemyCameraX(double enemyX, double originX)
{
    bool isLeftMoveCameraX = originX <= enemyX;
    bool isRightMoveCameraX = MAX_SCREEN_SIZE.x - CAMERA_POS.x >= enemyX;
    return isLeftMoveCameraX && isRightMoveCameraX;
};

bool MapScreenHelper::IsMoveEnemyCameraY(double enemyY, double originX)
{
    // TODO: y�ɃL�����̍������l������K�v���邩��
    return  0 > enemyY;
    //return  -(CAMERA_POS.y - Scene::Height() / 2.0) < playerY;
};