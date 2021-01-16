#pragma once
#include "Enemy.hpp"
#include "SpriteProperty.hpp"

/// <summary>
/// �A�j���[�V�����Ɋւ������ێ�����N���X�ł��B
/// </summary>
class AnimationBean {
public:
	int imageNumber;
	int imageVirticalNumber;
	int maxImageNumber;
	double interval;
	AnimationEndMode endMode;
	Stopwatch &sw;
	AnimationBean(int imageNumber, int imageVirticalNumber, int maxImageNumber, double interval, AnimationEndMode endMode, Stopwatch &sw);
	AnimationBean(int imageNumber, int maxImageNumber, double interval, AnimationEndMode endMode, Stopwatch &sw);
	AnimationBean(int imageNumber, Array<double> option, AnimationEndMode endMode, Stopwatch &sw);
	AnimationBean(int imageMaxNumber, double interval, Stopwatch& sw);
	AnimationBean(int imageNumber, AnimationEndMode endMode, Stopwatch& sw);
	static AnimationBean InitAnimationBean(Enemy &enemy, SpriteImageMetaData imageMetaData);
	static AnimationBean InitAnimationBean(Bullet& bullet);
};