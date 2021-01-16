#pragma once
# include <Siv3D.hpp>
# include "EnumManager.hpp"

/// <summary>
/// プレイヤーの道具クラスです
/// </summary>
class PlayerTool {
public:
	double wireTime;
	RectF wire;
	BulletName bulletName;
	PlayerTool();
	void ExtendWire(Vec2 playerPos, RectF detection, double deltaTime);
};