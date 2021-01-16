#pragma once
#include "Object.hpp"
#include "MapScreenHelper.hpp"
#include "SpriteImageMetaData.hpp"

class AnimationBean;
class TimeManager;

class Bullet : public Object {
public:
	/* ���O */
	BulletName name;
	/* ���˂����L�����̖��O */
	String owner;
	/* �摜 */
	TextureRegion image;
	/* �ʒu */
	Vec2 pos;
	/* ���ˈʒu */
	Vec2 startPos;
	/* ���e�ʒu */
	Vec2 endPos;
	/* ���x */
	double velocity;
	/* �_���[�W */
	int damage;
	/* �˒� */
	double range;
	/* �o�ߋ��� */
	Vec2 distance;
	/* �i�s���� */
	Direction direction;
	/* ����t���O */
	bool isHit;
	/* �X�g�b�v�E�H�b�` */
	Stopwatch bulletSw;
	/* �摜�ԍ����X�g */
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