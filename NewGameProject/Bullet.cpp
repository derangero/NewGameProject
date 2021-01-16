#include "Bullet.hpp"
#include "AnimationBean.hpp"
#include "TimeManager.hpp"

Bullet::Bullet() :
	pos(PLAYER_STAND_POS),
	startPos(PLAYER_STAND_POS),
	isHit(false),
	distance(Vec2::Zero())
{
	InitImageNumbers();
}

void Bullet::InitImageNumbers()
{
	imageNumbers = { 0, 0, 0, SHOOT_ATTACK_3_START_IMAGE_NUMBET };
}

void Bullet::Update(Vec2& playerPos, RectF& detection)
{
	pos.x = Direction::LEFT == direction
		? pos.x - (Scene::DeltaTime() * velocity)
		: pos.x + (Scene::DeltaTime() * velocity);
	hitBox = image.region(GetBulletPos(playerPos, detection));
}

// playerImage�Ƀo���b�g�摜������̂�
void Bullet::Draw(Vec2& playerPos, RectF& detection)
{
	image.draw(GetBulletPos(playerPos, detection));
}

// playerImage�Ƀo���b�g�摜������̂�
void Bullet::Draw(Vec2& playerPos, RectF& detection, BulletName bulletMode, Texture playerImage,
	std::unordered_map<int, SpriteImageMetaData> imageCoordinateMap, TimeManager& timeMngr)
{
	if (name == BulletName::ATTACK_3) {
		SpriteImageMetaData icData(imageCoordinateMap[(int)PlayerAnimeType::SHOOT_ATTACK_3]);
		Vec2 targetVec2(icData.vecs[imageNumbers[3]]);
		Size targetSize(icData.sizes[imageNumbers[3]]);
		playerImage(targetVec2, targetSize).draw(GetBulletPos(playerPos, detection));

		AnimationBean ani(16, 0.05, timeMngr.bulletAttack3SpriteSw);
		ChangeNSprite(ani, imageNumbers, 3);
	}
	else {
		image.draw(GetBulletPos(playerPos, detection));
	}
}

void Bullet::ChangeNSprite(AnimationBean& aniBean, Array<int>& imageNumbers, int n)
{
	int & imageNumber = imageNumbers[n];
	aniBean.sw.start();
	if (aniBean.sw.sF() >= aniBean.interval) {
		imageNumber += 1;
		if (imageNumber > aniBean.maxImageNumber) {
			imageNumber = aniBean.maxImageNumber;
		}
		aniBean.sw.reset();
	}
}
/// <summary>
/// �o���b�g�̈ʒu���擾���܂��B�v���C���[�̈ړ��ʂ��l�����ĕ␳���s���܂��B
/// </summary>
/// <param name="player">�v���C���[�N���X</param>
/// <returns></returns>
Vec2 Bullet::GetBulletPos(Vec2& playerPos, RectF& _detection)
{
	double fixedX = Direction::RIGHT == direction
			? _detection.w
			: -_detection.w;
	double fixedY = (_detection.h / 2) - 20;
	// TODO ��肭�ˌ����[�V�����ɍ����悤�ɗv����
	return MapScreenHelper::FixPositionFromPlayerPos(playerPos, pos).movedBy(fixedX, fixedY);
}