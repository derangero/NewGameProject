#pragma once
# include <Siv3D.hpp>
# include "EffectProperty.hpp"
# include "EffectMetaData.hpp"
class GameEffect
{
public:
	/* エフェクトの名前 */
	String name;
	/* エフェクトを描画するか */
	bool drawFlag;
	/* エフェクトをループするか */
	bool loopFlag;
	/* 再生時間を管理するための変数 */
	double time;
	/* 再生時間 */
	double effectingSf;
	/* 再生間隔の時間 */
	double intervalSf;
	/* エフェクトのスプライト */
	Texture effectBase;
	/* 描画位置 */
	Vec2 pos;
	/* エフェクトのスプライト(1枚づつ分解してリスト化) */
	Array<TextureRegion> effectTextures;
	/* エフェクトを実際に描画する枚数 */
	int effectDrawSize;
	/* 汎用ストップウォッチ */
	Stopwatch sw;
public:
	GameEffect();
	GameEffect(EffectMetaData effectMetaData);
	void StartDraw(Vec2 pos);
	void Draw(Vec2 pos);
};