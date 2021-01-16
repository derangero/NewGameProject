#pragma once
#include "Siv3D.hpp"
class BulletData
{
public:
	int type;
	int damage;
	int hitBox_w;
	int hitBox_h;
	int generationCount;
	double velocity;
	double range;
public:
	BulletData();
};