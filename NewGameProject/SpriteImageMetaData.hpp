#pragma once
# include <Siv3D.hpp>

/// <summary>
/// スプライト画像のメタ情報を保持するクラスです。
/// </summary>
class SpriteImageMetaData {
public:
	int maxImageNumber;
	double interval;
	double coolTime;
	Array<Vec2> vecs;
	Array<Size> sizes;
public:
	SpriteImageMetaData();
	SpriteImageMetaData(int maxImageNumber, double interval, double coolTime, Array<Vec2> vecs, Array<Size> sizes);
};