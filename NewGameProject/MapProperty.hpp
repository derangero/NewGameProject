#pragma once
# include <Siv3D.hpp>

static Array<String> MAP_OBJECT_NAMES = {
	U"ladder_1", U"grass", U"slope"
};
static Array<String> ENEMY_NAMES = {
	U"enemiesA"
};

// 背景用(当たり判定なし)
static Array<int> NO_COLLISION_MAP = {
	0
};

// 傾斜用（左方向）
constexpr auto SLOPE_45_LEFT_MAP = 172;

// 傾斜用（22.5度 左方向A...Quad）
constexpr auto SLOPE_LEFT_22_5_A = 164;
// 傾斜用（22.5度 左方向B...Triangle）
constexpr auto SLOPE_LEFT_22_5_B = 165;
// 傾斜用（22.5度 左方向C...地面と接着する）
// 地面に
constexpr auto SLOPE_LEFT_22_5_C = 166;

constexpr auto MAP_NUMBER_BASE = 2372;
