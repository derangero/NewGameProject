#pragma once
# include <Siv3D.hpp>
# include "Player.hpp"
# include "TimeManager.hpp"
# include "MapTip.hpp"
# include "MapScreenHelper.hpp"
# include "BulletManager.hpp"
# include "MapProperty.hpp"

/// <summary>
///  プレイヤーの当たり判定クラスです
/// </summary>
class MapCollisionDetection {
	public:
		MapCollisionDetection();
		void PlayerCheckWallInit(Player& player);
		void CheckWall(Array<MapTip> &mapTips, Player &player, MapScreenHelper &screenHelper);
		void CheckSideWall(Array<MapTip>& mapTips, Player& player, MapScreenHelper& screenHelper);
		void CheckHeadWall(Array<MapTip>& mapTips, Player& player, MapScreenHelper& screenHelper);
		void CheckFootWall(Array<MapTip>& mapTips, Player& player, MapScreenHelper& screenHelper);
		bool IsTouchedLeftWall(Player player, RectF map);
		bool IsTouchedRightWall(Player player, RectF map);
		bool IsTouchedHeadWall(Player player, RectF map);
		Triangle GetTriangleForLeftSlope(Vec2 mapPos);
		void ActionByLeftSlope(Player& player);
		void InitActionByLeftSlope(Player& player);
		bool CheckSlopeLeft22HalfA(Player& player, Vec2 mapPos);
		bool CheckSlopeLeft22HalfB(Player& player, Vec2 mapPos);
		bool CheckSlopeLeft22HalfC(Player& player, Vec2 mapPos);
};