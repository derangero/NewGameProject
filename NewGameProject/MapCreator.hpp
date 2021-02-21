#pragma once
# include "ObjectTip.hpp"
# include "SpriteUtil.hpp"
# include "TimeManager.hpp"

class MapTip;
class MapCreator
{
public:
	bool getAllCoin;
	bool keyAppearance;
	Texture objectSprite;
	Texture backGround_0;
	Texture backGround_1;
	Texture backGround_2;
	Array<MapTip> mapTips;
	Array<ObjectTip> objectTips;
	std::unordered_map<int, SpriteImageMetaData> spriteMetaDataMap;
	std::unordered_map<int, int> objectImageNumberMap;
	std::unordered_map<int, Stopwatch> objectStopWatchMap;
public:
	MapCreator(Texture mapTexture);
	void CreateMapTips(Texture mapTexture);
	void CreateObjectTip();
	bool CreateEnemy(ObjectTip& objectTip, String elemName, XMLElement& elem2);
	bool CreatePieceObject(ObjectTip& objectTip, String elemName, XMLElement& elem2, MapType mapType);
	void CreateObject(ObjectTip& objectTip, String elemName, XMLElement& elem2, MapType mapType);
	Grid<int> CreateMapGrid();
	MapType GetMapType(String mapType);
	EnemyType GetEnemyType(String enemyType);
	double GetObjectMoveXAmt(ObjectTip& objectTip);
	double GetObjectMoveYAmt(ObjectTip& objectTip);
	void DrawObjectTip(Texture allMap, Vec2& screenOriginPosition, TimeManager timeManager, Player &player);
	Point CreateTipPoint(int imageNumber);
	bool IsNoCollision(int imageNumber);
	void DrawBackGround();
	void DrawBackGround(Texture image);
	Direction GetDirection(String direction);
};