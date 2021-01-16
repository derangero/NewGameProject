#pragma once
#include "Siv3D.hpp"
#include "MapTip.hpp"
#include "Property.hpp"
#include "MapProperty.hpp"
#include "EnumManager.hpp"

class MapObjectTip : public MapTip
{
public:
	double w;
	double h;
	MapObjectType type;
	EnemyType enemyType;
	Polygon objectDetection;
	Quad quadDetection;
	Triangle triDetection;
	MapObjectTip();
	static void SetMapObjectTip(Array<MapObjectTip> objectMapTips, Texture mapTip1, Vec2& screenOriginPosition);
};