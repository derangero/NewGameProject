#pragma once
# include <Siv3D.hpp>
# include "Animation.hpp"

class GameSprite
{
public:
    Vec2 potision;
    Animation& anime;// 何のアニメーションを表示するか ※参照型はメモリ使用を減らす 
    int animeNumber;    // 変化する
    GameSprite(Vec2 potision, Animation& anime);
    void Draw();
};
