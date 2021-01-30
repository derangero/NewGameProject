#pragma once
# include <Siv3D.hpp>

class MapCreator;
/// <summary>
/// マップチップクラスです
/// </summary>
class MapTip
{
public:
	Point tip;
	Vec2 mapGrid;
	int mapNumber;
	bool isTouched;
	Texture mapTipTexture;
	RectF detection;
public:
	MapTip();
	static void DrawMapTipTextures(Array<MapTip> mapTips, Texture mapTip1, Vec2& screenOriginPosition, Font font);
	static Quad GetQuadForLeftSlope(Vec2 mapPos);
};
