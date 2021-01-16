#pragma once
#include "Siv3D.hpp"
#include "Player.hpp"
#include "MapObjectTip.hpp"
#include "TimeManager.hpp"

class ObjectCollisionDetection
{
public:
	ObjectCollisionDetection();
	void PlayerCheckWallInit(Player& player);
	void Check(Array<MapObjectTip>& mapTips, Player& player, MapScreenHelper& screenHelper, TimeManager& tManager);
	void CheckSide(Array<MapObjectTip>& mapTips, Player& player, MapScreenHelper& screenHelper, TimeManager& tManager);
	void CheckFoot(Array<MapObjectTip>& mapTips, Player& player, MapScreenHelper& screenHelper);
	bool CheckRightDownSlope(Player& player, MapObjectTip mapObjectTip, Vec2 screenOriginPosition);
	void ActionByRightDownSlope(Player& player);
	void InitActionBySlope(Player& player);
	bool IsTouchedLeftWall(Player player, RectF map);

	bool IsTouchedRightWall(Player player, RectF map);
};

