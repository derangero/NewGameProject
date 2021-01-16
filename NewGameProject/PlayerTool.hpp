#pragma once
# include <Siv3D.hpp>
# include "EnumManager.hpp"

/// <summary>
/// �v���C���[�̓���N���X�ł�
/// </summary>
class PlayerTool {
public:
	double wireTime;
	RectF wire;
	BulletName bulletName;
	PlayerTool();
	void ExtendWire(Vec2 playerPos, RectF detection, double deltaTime);
};