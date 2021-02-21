#pragma once
# include <Siv3D.hpp>
# include "EnumManager.hpp"

class MapCreator;
/// <summary>
/// マップチップクラスです
/// </summary>
class MapTip
{
public:
	/* ID */
	long id;
	bool isExists;
	bool falling;
	/* 移動中か */
	TipMovingBy tipMovingBy;
	/* マップのタイプ */
	MapType mapType;
	/* マップ番号 */
	int mapNumber;
	/* 壁としてふるまうか */
	bool blockBehave;
	/* チップに触れたかどうか */
	bool touched;
	/* チップの位置 */
	Point tip;
	Vec2 mapGrid;
	Texture mapTipTexture;
	/* あたり判定 */
	RectF collision;
	/* 移動した距離 */
	Vec2 movedDistance;
public:
	MapTip();
	static void DrawMapTipTextures(Array<MapTip> mapTips, Texture tipTexture, Vec2& screenOriginPos, Font font);
	static Quad GetQuadForLeftSlope(Vec2 mapPos);
	void MoveX(double deltaX);
	void MoveY(double deltaY);
};
