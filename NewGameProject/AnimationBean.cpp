#include "AnimationBean.hpp"

/// <summary>
/// コンストラクタです。
/// </summary>
/// <param name="imageNumber">画像番号(０始まり)</param>
/// <param name="imageVirticalNumber">スプライト画像の縦軸番号(０始まり)</param>
/// <param name="maxImageNumber">最後の画像番号(０始まり)</param>
/// <param name="interval">スプライトをきりかえる間隔時間</param>
/// <param name="endMode">アニメーション終了時のモード</param>
/// <param name="sw">ストップウォッチ</param>
AnimationBean::AnimationBean(int imageNumber, int imageVirticalNumber, int maxImageNumber,
	double interval, AnimationEndMode endMode, Stopwatch & sw) :
	imageNumber(imageNumber),
	imageVirticalNumber(imageVirticalNumber),
	maxImageNumber(maxImageNumber),
	interval(interval),
	endMode(endMode),
	sw(sw) {}

AnimationBean::AnimationBean(int imageNumber, int maxImageNumber, double interval, AnimationEndMode endMode, Stopwatch& sw) :
	imageNumber(imageNumber),
	maxImageNumber(maxImageNumber),
	interval(interval),
	endMode(endMode),
	sw(sw) {}

AnimationBean::AnimationBean(int imageNumber, Array<double> option, AnimationEndMode endMode,
	Stopwatch &sw) :
	imageNumber(imageNumber),
	imageVirticalNumber(option[0]),
	maxImageNumber(option[1]),
	interval(option[2]),
	endMode(endMode),
	sw(sw) {}

AnimationBean::AnimationBean(int maxImageNumber, double interval, Stopwatch& sw) :
	maxImageNumber(maxImageNumber),
	interval(interval),
	sw(sw) {}

AnimationBean AnimationBean::InitAnimationBean(Enemy &enemy, SpriteImageMetaData imageMetaData)
{
	EnemyAnimeType animeType = static_cast<EnemyAnimeType>(enemy.animeType);
	switch (animeType) {
	case EnemyAnimeType::NONE:
	case EnemyAnimeType::WAIT:
	case EnemyAnimeType::WALK:
		return AnimationBean(enemy.imageNumber, imageMetaData.maxImageNumber, imageMetaData.interval, AnimationEndMode::REPEAT, enemy.sw);
	case EnemyAnimeType::ON_DAMAGE:
	case EnemyAnimeType::DOWN:
	case EnemyAnimeType::ATTACK1:
	case EnemyAnimeType::ATTACK2:
	case EnemyAnimeType::ATTACK3:
	case EnemyAnimeType::ATTACK4:
		return AnimationBean(enemy.imageNumber, imageMetaData.maxImageNumber, imageMetaData.interval, AnimationEndMode::STOP, enemy.sw);
	}
}

AnimationBean AnimationBean::InitAnimationBean(Bullet &bullet)
{
	return AnimationBean(bullet.imageNumber, 5, 7, 0.1, AnimationEndMode::VANISH, bullet.bulletSw);
}
