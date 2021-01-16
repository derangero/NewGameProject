#pragma once
# include <Siv3D.hpp>

static Array<String> MAP_OBJECT_NAMES = {
	U"ladder_1", U"grass", U"slope"
};
static Array<String> ENEMY_NAMES = {
	U"enemiesA"
};

// �w�i�p(�����蔻��Ȃ�)
static Array<int> NO_COLLISION_MAP = {
	0
};

// �X�Ηp�i�������j
constexpr auto SLOPE_45_LEFT_MAP = 172;

// �X�Ηp�i22.5�x ������A...Quad�j
constexpr auto SLOPE_LEFT_22_5_A = 164;
// �X�Ηp�i22.5�x ������B...Triangle�j
constexpr auto SLOPE_LEFT_22_5_B = 165;
// �X�Ηp�i22.5�x ������C...�n�ʂƐڒ�����j
// �n�ʂ�
constexpr auto SLOPE_LEFT_22_5_C = 166;

constexpr auto MAP_NUMBER_BASE = 2372;
