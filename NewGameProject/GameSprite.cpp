# include "GameSprite.hpp"

GameSprite::GameSprite(Vec2 potision, Animation& anime) : anime(anime) // 
{
    this->potision = potision;
    this->animeNumber = 0;
}

void GameSprite::Draw()
{
    //anime.texture(0, 0, anime.width, anime.height).draw(potision);

    anime.texture(anime.width * animeNumber, anime.height * 0, anime.width, anime.height).draw(potision);  //�Ȃ�ׂ��v�Z��������
    animeNumber++;
    // �����i�iheight�j
    // ���[�v
    // �X�s�[�h
    // �t�F�[�h�C���E�t�F�[�h�A�E�g�E�g��E�k���ȂǍl����
    // �p�[�e�B�N���i���ˏ�Ɂj
}