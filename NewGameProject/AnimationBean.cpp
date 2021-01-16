#include "AnimationBean.hpp"

/// <summary>
/// �R���X�g���N�^�ł��B
/// </summary>
/// <param name="imageNumber">�摜�ԍ�(�O�n�܂�)</param>
/// <param name="imageVirticalNumber">�X�v���C�g�摜�̏c���ԍ�(�O�n�܂�)</param>
/// <param name="maxImageNumber">�Ō�̉摜�ԍ�(�O�n�܂�)</param>
/// <param name="interval">�X�v���C�g�����肩����Ԋu����</param>
/// <param name="endMode">�A�j���[�V�����I�����̃��[�h</param>
/// <param name="sw">�X�g�b�v�E�H�b�`</param>
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
