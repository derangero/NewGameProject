#pragma once
#include "Siv3D.hpp"
#include "MapTip.hpp"
#include "Property.hpp"
#include "MapProperty.hpp"
#include "EnumManager.hpp"

class ObjectTip : public MapTip
{
public:
	double w;
	double h;
	MapObjectType type;
	EnemyType enemyType;
	Polygon objectDetection;
	Quad quadDetection;
	Triangle triDetection;
	ObjectTip();
	static void SetObjectTip(Array<ObjectTip> objectMapTips, Texture mapTip1, Vec2& screenOriginPosition);
	Vec2 GetObjectTipXY(XMLElement& elem);
};