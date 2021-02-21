#pragma once
# include <Siv3D.hpp>
# include "Player.hpp"
# include "TimeManager.hpp"
# include "MapTip.hpp"
# include "MapScreenHelper.hpp"
# include "BulletManager.hpp"
# include "MapProperty.hpp"
# include "MapCreator.hpp"

/// <summary>
///  プレイヤーの当たり判定クラスです
/// </summary>
class MapCollisionHelper {
	public:
		/* すべてのマップチップ(オブジェクトチップ含む) */
		Array<MapTip> allMapTip;
		MapCreator &mapCreator;
	public:
		MapCollisionHelper(MapCreator &mapCreator);
		void ActionObjectTip(Player& player, bool grabbed, ObjectTip& objectTip);
		void ActionJumpPad(Character& chara, RectF collision);
		void InitBeforeCheck(Character& player);
		void CheckCollision(Player &player, MapScreenHelper &screenHelper);
		void CheckCollision(Enemy &enmey, MapScreenHelper &screenHelper);
		void CheckBlockCollision(Player &player, MapScreenHelper &screenHelper);
		void CheckBlockCollisionSide(Player &player, MapScreenHelper &screenHelper);
		void CheckBlockCollisionBottom(Player &player, MapScreenHelper &screenHelper);
		void CheckSide(Player& player, MapScreenHelper& screenHelper);
		void CheckSide(Enemy& enemy, MapScreenHelper& screenHelper);
		void CheckSide(Character& chara, MapScreenHelper& screenHelper, Vec2 screenOriginPos);
		void CheckHead(Player& player, MapScreenHelper& screenHelper);
		void CheckFoot(Character &chara, MapScreenHelper& screenHelper);
		void CheckSideRadderAction(Player& player, ObjectTip objectTip, bool& grabbed);
		bool DecideWallTouched(Character& chara, RectF collision, MapTip& mapTip);
		bool DecideFootBlock(Character& chara, RectF collision);
		bool IsTouchedLeft(Character chara, RectF map);
		bool IsTouchedRight(Character chara, RectF map);
		bool IsTouchedHead(Player player, RectF map);
		bool IsSunk(Vec2 foot, Vec2 topBlock);
		void MoveOnMovingFloor(Character& chara, ObjectTip objectTip);
		Array<MapTip> GetTargetMapTips();
};