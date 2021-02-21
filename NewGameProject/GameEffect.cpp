#include "GameEffect.hpp"

GameEffect::GameEffect()
{
}

GameEffect::GameEffect(EffectMetaData effectMetaData) :
    name(effectMetaData.name),
    drawFlag(false),
    loopFlag(effectMetaData.loopFlag),
    effectBase(effectMetaData.effectBase),
    time(0.0),
    effectingSf(effectMetaData.effectingSf),
    intervalSf(effectMetaData.intervalSf)
{
    for (int ny = 0; ny < effectMetaData.maxYCount; ny++) {
        for (int nx = 0; nx < effectMetaData.maxXCount; nx++) {
            // 1をnx(ny)分割する→UV座標
            TextureRegion effectTexture = effectBase.uv(
                1.0 / effectMetaData.maxXCount * nx,
                1.0 / effectMetaData.maxYCount * ny,
                1.0 / effectMetaData.maxXCount,
                1.0 / effectMetaData.maxYCount);
           effectTextures.push_back(effectTexture);
        }
    }
    this->effectDrawSize = int32(effectTextures.size()) - effectMetaData.blanckCount;
}

void GameEffect::StartDraw(Vec2 pos)
{
    if (!drawFlag) {
        drawFlag = true;
    }
    Draw(pos);
}

void GameEffect::Draw(Vec2 pos)
{
    if (drawFlag && (!sw.isRunning() || sw.sF() > intervalSf)) {
        time += Scene::DeltaTime();
        size_t index = 0;
        for (size_t i = 0; i < effectDrawSize; i++) { //nx * ny回数
            // 右辺・・・枚数が進めば進むほど小さくなる
            // 左辺・・・時間経過するほど大きくなる
            // 経過時間 - 発動時の経過時間(増えていく)　＞＝　継続ミリ秒(指定) / nx総分割数 * i
            //if ((Time::GetMillisec() - time) >= effectingSf / effectDrawSize * i) {
            double a = Time::GetMillisec() - time;
            if (time >= effectingSf / effectDrawSize * i) {
                index = i; // 表示する画像のindex
            }
        }
        effectTextures[index].drawAt(pos, ColorF(1.0, 1.0));
        if (time > effectingSf) {
            if (!loopFlag) {
                drawFlag = false;
            }
            sw.restart();
            time = 0.0;
        }
    }
}
