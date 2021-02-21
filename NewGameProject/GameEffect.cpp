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
            // 1��nx(ny)�������遨UV���W
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
        for (size_t i = 0; i < effectDrawSize; i++) { //nx * ny��
            // �E�ӁE�E�E�������i�߂ΐi�ނقǏ������Ȃ�
            // ���ӁE�E�E���Ԍo�߂���قǑ傫���Ȃ�
            // �o�ߎ��� - �������̌o�ߎ���(�����Ă���)�@�����@�p���~���b(�w��) / nx�������� * i
            //if ((Time::GetMillisec() - time) >= effectingSf / effectDrawSize * i) {
            double a = Time::GetMillisec() - time;
            if (time >= effectingSf / effectDrawSize * i) {
                index = i; // �\������摜��index
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
