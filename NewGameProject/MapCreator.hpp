#pragma once
# include <Siv3D.hpp>
# include "MapTip.hpp"
# include "MapObjectTip.hpp"
# include "Property.hpp"
# include "MapProperty.hpp"
# include "Enemy.hpp"

class MapTip;
class MapCreator {
public:
	MapCreator();
	static Grid<int> CreateMapGrid();
	static Array<MapTip> GetMapTips(Texture mapTip1);
	static Array<MapObjectTip> GetMapObjectTip();
	void ShowElements(const XMLElement& element);
	static bool IsNoCollision(int imageNumber);
	static MapObjectType GetMapObjectType(String mapObjectType);
	static EnemyType GetEnemyType(String enemyType);
};