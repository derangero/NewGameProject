#pragma once
#include "Siv3D.hpp"
#include "Player.hpp"
#include "objectTip.hpp"
#include "TimeManager.hpp"
#include "MapCreator.hpp"

class ObjectCollisionHelper
{
public:
	ObjectCollisionHelper();
	void PlayerCheckWallInit(Player& player);
	void Check(MapCreator& mapCreator, Player& player, MapScreenHelper& screenHelper, TimeManager& tManager);
	void CheckSide(Array<ObjectTip>& mapTips, Player& player, MapScreenHelper& screenHelper, TimeManager& tManager);
	void CheckSideAction(Player& player, ObjectTip objectTip);
	void CheckFoot(Array<ObjectTip>& mapTips, Player& player, MapScreenHelper& screenHelper);
	void CheckHead(Array<ObjectTip>& mapTips, Player& player, MapScreenHelper& screenHelper);
	bool CheckRightDownSlope(Player& player, ObjectTip ObjectTip, Vec2 screenOriginPosition);
	void ActionByRightDownSlope(Player& player);
	void InitActionBySlope(Player& player);
	bool IsTouchedHeadWall(Player player, RectF collision);
	bool IsTouchedByPlayerLeft(Player player, RectF map);
	bool IsTouchedByPlayerRight(Player player, RectF map);
	bool IsSunk(Vec2 foot, Vec2 topBlock);
	void MovePlayerOnMovingFloor(Player& player, ObjectTip touchedObjectTip);
};

