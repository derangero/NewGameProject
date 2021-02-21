#pragma once
# include "Property.hpp"
# include "MapTip.hpp"
# include "objectTip.hpp"

/// <summary>
/// 全体マップからスクリーン(ゲーム画面)の位置補正を行うためのヘルパークラスです
/// </summary>
class MapScreenHelper {
public:
	MapScreenHelper();
	static Vec2 ChangeWorldToScreenPos(Vec2 pos);
	static Vec2 GetScreenOriginPosition(Vec2 pos);
	static Vec2 GetEnemyScreenOriginPos(Vec2 pos, Vec2 enemyOriginPos, Vec2 playerPos);
	static Vec2 MoveMapObject(Vec2 pos, Array<ObjectTip> &mapTips);
	static Vec2 FixPosition(Vec2 pos, Vec2 targetPos);
	static Vec2 FixPositionFromPlayerPos(Vec2 basePos, Vec2 targetPos);
	static Vec2 GetObjectPos(Vec2 objectPos, Vec2 playerPos);
	static bool IsMoveCameraX(double x);
	static bool IsMoveCameraY(double y);
	static bool IsMoveEnemyCameraX(double enemyX, double originX);
	static bool IsMoveEnemyCameraY(double enemyY, double originY);
};