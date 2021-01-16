#pragma once
# include <Siv3D.hpp>

class MapCreator;
/// <summary>
/// マップチップクラスです
/// </summary>
class MapTip {
public:
	MapTip();
	int tipX;
	int tipY;
	double mapGridX;
	double mapGridY;
	int mapNumber;
	bool isTouched;
	Texture mapTipTexture;
	RectF detection;
	static void DrawMapTipTextures(Array<MapTip> mapTips, Texture mapTip1, Vec2& screenOriginPosition, Font font);
	static ColorF GetColorF(MapTip mapTip);
	static Quad GetQuadForLeftSlope(Vec2 mapPos);
};
