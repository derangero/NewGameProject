#pragma once
# include <Siv3D.hpp>
class EffectMetaData
{
public:
    // 名前
    String name;
    // スプライトの最大横枚数
    int maxXCount;
    // スプライトの最大縦枚数
    int maxYCount;
    // 空白枚数
    int blanckCount;
    // 再生時間
    double effectingSf;
    /* 再生間隔の時間 */
    double intervalSf;
    // ループするかどうか
    bool loopFlag;
    // エフェクトのスプライト画像
    Texture effectBase;
public:
	EffectMetaData();
	EffectMetaData(String name, Texture effectBase, Array<double> properties);
};