#pragma once
#include "Siv3D.hpp"
#include "MapTip.hpp"
#include "Property.hpp"
#include "MapProperty.hpp"
#include "EnumManager.hpp"

/// <summary>
/// オブジェクトチップのクラス
/// </summary>
class ObjectTip : public MapTip
{
public:
	double w;
	double h;
	double deltaAmt;
	// オブジェクトの移動距離
	double moveAmt;
	// オブジェクトが往復する基準になる距離
	double turningMoveAmt;
	// ふれた時のダメージ
	int damage;
	// (敵)待機時間
	double waitTime;
	Direction direction;
	EnemyType enemyType;
	Polygon objectDetection;
	Quad quadDetection;
	Triangle triDetection;
public:
	ObjectTip();
	/// <summary>
	/// 敵キャラのオブジェクトを設定
	/// </summary>
	/// <param name="enemyType">敵キャラのタイプ</param>
	/// <param name="tip">位置</param>
	/// <param name="elem">XMLElementオブジェクト</param>
	ObjectTip(EnemyType enemyType, Point tip, XMLElement &elem);
	/// <summary>
	/// マップチップのオブジェクトを設定
	/// </summary>
	/// <param name="tip">位置</param>
	/// <param name="elem">XMLElementオブジェクト</param>
	ObjectTip(Point tip, XMLElement &elem);
	ObjectTip(int mapNumber, double width, double height, Point tip, XMLElement &elem);
	ObjectTip(MapType mapType, int mapNumber, double width, double height, Point tip, XMLElement &elem,
		double deltaAmt, double turningMoveAmt, Direction direction, int damage, double waitTime);
	static void SetObjectTip(Array<ObjectTip> objectMapTips, Texture mapTip1, Vec2& screenOriginPosition);
	RectF CreateCollision();
	Vec2 GetObjectTipXY(XMLElement& elem);
};