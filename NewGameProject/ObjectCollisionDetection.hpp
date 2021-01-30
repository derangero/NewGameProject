#pragma once
#include "Siv3D.hpp"
#include "Player.hpp"
#include "objectTip.hpp"
#include "TimeManager.hpp"
#include "MapCreator.hpp"

class ObjectCollisionDetection
{
public:
	ObjectCollisionDetection();
	void PlayerCheckWallInit(Player& player);
	void Check(MapCreator& mapCreator, Player& player, MapScreenHelper& screenHelper, TimeManager& tManager);
	
	void CheckSide(Array<ObjectTip>& mapTips, Player& player, MapScreenHelper& screenHelper, TimeManager& tManager);
	void CheckSideAction(Player& player, ObjectTip objectTip);
	void CheckFoot(Array<ObjectTip>& mapTips, Player& player, MapScreenHelper& screenHelper);
	bool CheckRightDownSlope(Player& player, ObjectTip ObjectTip, Vec2 screenOriginPosition);
	void ActionByRightDownSlope(Player& player);
	void InitActionBySlope(Player& player);
	bool IsTouchedLeftWall(Player player, RectF map);
	bool IsTouchedRightWall(Player player, RectF map);
};

