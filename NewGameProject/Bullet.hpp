#pragma once
#include "Object.hpp"
#include "MapScreenHelper.hpp"
#include "SpriteImageMetaData.hpp"

class AnimationBean;
class TimeManager;

class Bullet : public Object {
public:
	/* 名前 */
	BulletName name;
	/* 発射したキャラの名前 */
	String owner;
	/* 画像 */
	TextureRegion image;
	/* 位置 */
	Vec2 pos;
	/* 発射位置 */
	Vec2 startPos;
	/* 着弾位置 */
	Vec2 endPos;
	/* 速度 */
	double velocity;
	/* ダメージ */
	int damage;
	/* 射程 */
	double range;
	/* 経過距離 */
	Vec2 distance;
	/* 進行方向 */
	Direction direction;
	/* 判定フラグ */
	bool isHit;
	/* ストップウォッチ */
	Stopwatch bulletSw;
	/* 画像番号リスト */
	Array<int> imageNumbers;
public:
	Bullet();
	void InitImageNumbers();
	//virtual ~Bullet();
	void Update(Vec2 &playerPos, RectF &playerDetection);
	void Draw(Vec2& playerPos, RectF& detection);
	void Draw(Vec2& playerPos, RectF& playerDetection, BulletName bulletName, Texture playerImage,
		std::unordered_map<int, SpriteImageMetaData> imageCoordinateMap, TimeManager& timeMngr);
	Vec2 GetBulletPos(Vec2& playerPos, RectF& playerDetection);
	void ChangeNSprite(AnimationBean& aniBean, Array<int>& imageNumbers, int n);
};