#pragma once
#include "Enemy.hpp"
#include "SpriteProperty.hpp"

/// <summary>
/// アニメーションに関する情報を保持するクラスです。
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