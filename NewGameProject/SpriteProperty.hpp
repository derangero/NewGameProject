#pragma once
#include <Siv3D.hpp>

/// スプライト画像の縦軸番号(０始まり)
/// 最後の画像番号(０始まり)
/// スプライトをきりかえる間隔時間

const static Array<double> EYE_MOVE
{
	4, 7, 0.05
};
const static Array<double> EYE_ATTACK_A
{
	2, 5, 0.3
};
const static Array<double> EYE_DOWN
{
	3, 3, 0.05
};
const static Array<double> EYE_ON_DAMAGE
{
	6, 3, 0.1
};
