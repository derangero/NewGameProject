# include "GameSprite.hpp"

GameSprite::GameSprite(Vec2 potision, Animation& anime) : anime(anime) // 
{
    this->potision = potision;
    this->animeNumber = 0;
}

void GameSprite::Draw()
{
    //anime.texture(0, 0, anime.width, anime.height).draw(potision);

    anime.texture(anime.width * animeNumber, anime.height * 0, anime.width, anime.height).draw(potision);  //なるべく計算式を書く
    animeNumber++;
    // 複数段（height）
    // ループ
    // スピード
    // フェードイン・フェードアウト・拡大・縮小など考える
    // パーティクル（放射状に）
}