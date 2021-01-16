#pragma once
#include "Siv3D.hpp"
#include "EnumManager.hpp"

class Object
{
public:
	/* 存在フラグ */
	bool isExists;
	/* 速度 */
	double velocity;
	/* 位置 */
	Vec2 pos;
	/* あたり判定 */
	RectF hitBox;
	/* 進行方向 */
	Direction direction;
	/* 汎用ストップウォッチ */
	Stopwatch bulletSw;
	/* 画像(スプライト用) */
	Texture spriteImage;
	/* 画像番号 */
	int imageNumber;
	/* 画像 */
	TextureRegion image;
public:
	Object();
	void ClearPos();
	virtual ~Object();
};