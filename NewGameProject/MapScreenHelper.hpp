#pragma once
# include "Property.hpp"
# include "MapTip.hpp"
# include "MapObjectTip.hpp"

/// <summary>
/// 全体マップからスクリーンの位置補正を行うためのヘルパークラスです
/// </summary>
class MapScreenHelper {
public:
	MapScreenHelper();
	static Vec2 ChangeWorldToScreenPos(Vec2 pos);
	static Vec2 GetScreenOriginPosition(Vec2 pos);
	static Vec2 MoveMapObject(Vec2 pos, Array<MapObjectTip> &mapTips);
	static Vec2 FixPosition(Vec2 pos, Vec2 targetPos);
	static Vec2 FixPositionFromPlayerPos(Vec2 basePos, Vec2 targetPos);
	static Vec2 GetObjectPos(Vec2 objectPos, Vec2 playerPos);
	static bool IsMoveCameraX(double x);
	static bool IsMoveCameraY(double y);
};