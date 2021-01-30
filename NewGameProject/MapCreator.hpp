#pragma once
# include "objectTip.hpp"

class MapTip;
class MapCreator
{
public:
	Array<MapTip> mapTips;
	Array<ObjectTip> objectTips;
public:
	MapCreator(Texture mapTexture);
	void CreateMapTips(Texture mapTexture);
	void CreateObjectTip();
	Grid<int> CreateMapGrid();
	MapObjectType GetMapObjectType(String mapObjectType);
	EnemyType GetEnemyType(String enemyType);
	void SetObjectTip(Texture allMap, Vec2& screenOriginPosition);
	Point CreateTipPoint(int imageNumber);
	bool IsNoCollision(int imageNumber);
};