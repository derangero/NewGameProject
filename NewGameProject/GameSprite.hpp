#pragma once
# include <Siv3D.hpp>
# include "Animation.hpp"

class GameSprite
{
public:
    Vec2 potision;
    Animation& anime;// ���̃A�j���[�V������\�����邩 ���Q�ƌ^�̓������g�p�����炷 
    int animeNumber;    // �ω�����
    GameSprite(Vec2 potision, Animation& anime);
    void Draw();
};
