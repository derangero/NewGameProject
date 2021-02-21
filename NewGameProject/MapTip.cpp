# include "MapTip.hpp"
# include "MapCreator.hpp"

MapTip::MapTip() :
    isExists(true),
    falling(true),
    movedDistance(Vec2::Zero()),
    tipMovingBy(TipMovingBy::NONE),
    mapType(MapType::NORMAL),
    mapNumber(0),
    blockBehave(true),
    touched(false)
{}

/// <summary>
/// �}�b�v�`�b�v��`�悵�܂��B
/// </summary>
/// <param name="mapTips">MapTip�N���X�̓��I�z��</param>
/// <param name="allMapTip">�}�b�v�摜</param>
/// <param name="screenOriginPosition">�X�N���[���v�Z�p��Vec2</param>
void MapTip::DrawMapTipTextures(Array<MapTip> mapTips, Texture allMap, Vec2 &screenOriginPosition, Font font)
{
    for (MapTip &mapTip : mapTips) {
        //TODO: �f�o�b�O�p�ɓ����蔻�������(���ۂ̔����PlayerCollisionDetection�N���X�ōs��)
        ColorF frameColor = mapTip.touched ? ColorF(0.4, 0.2, 0.7, 0.9) : ColorF(1.0, 1.0, 1.0, 0.5);
        mapTip.collision.movedBy(-screenOriginPosition).drawFrame(1, 1, frameColor);
        
        RectF mapDetection = mapTip.collision;
        TextureRegion tip = allMap(mapTip.tip.x, mapTip.tip.y, MAP_IMAGE_SQUARE_SIZE, MAP_IMAGE_SQUARE_SIZE);
        Vec2 mapPos = Vec2(
            mapTip.mapGrid.x - screenOriginPosition.x,
            mapTip.mapGrid.y - screenOriginPosition.y);
        // �`�b�v��`�悷��
        font(mapTip.mapNumber).draw(mapPos);
        //tip.draw(mapPos.x, mapPos.y, GetColorF(mapTip));
    }

}

/// <summary>
/// ���o��X���[�v�̓����蔻��p��Quad���擾���܂��B
/// �����22.5�x�̔�����\�z���邽�߂̍��p�[�c�ł��B
/// 22.5�x�X���[�v��Quad�p�[�c(A)��Triangle�p�[�c(B)�����킹�ĕ\�����܂��B
/// �܂��ATriangle�p�[�c(C)��(B)�̑���ɒn�ʐڒ������Ɏg�p���܂��B
/// </summary>
/// <param name="mapPos">�}�b�v�`�b�v�̈ʒu</param>
/// <returns>Triangle�I�u�W�F�N�g</returns>
Quad MapTip::GetQuadForLeftSlope(Vec2 mapPos)
{
    return Quad(mapPos, mapPos.movedBy(16, 8), mapPos.movedBy(16, 16), mapPos.movedBy(0, 16));
}

void MapTip::MoveX(double deltaX)
{
    tip.x += deltaX;
    mapGrid.x += deltaX;
    collision.x += deltaX;
}

void MapTip::MoveY(double deltaY)
{
    tip.y += deltaY;
    mapGrid.y += deltaY;
    collision.y += deltaY;
}

//if (mapTip.mapNumber == SLOPE_45_LEFT_MAP) {
//    //TO REFINE:�⓹�̃}�b�v�`�b�v�����������̂ŋ���̍�
//    // �����`->�����`�ɂ��ĂЂ��`�ɂ����W�������ɂ��炷
//    tip.resized(22, 16)
//        .rotated(45_deg)
//        .draw(mapPos.x - 8, mapPos.y + 6, GetColorF(mapTip));
//}
//else if (mapTip.mapNumber == SLOPE_LEFT_22_5_A) {
//    Quad quad = MapTip::GetQuadForLeftSlope(mapPos);
//    quad(tip).draw();
//}
//else if (mapTip.mapNumber == SLOPE_LEFT_22_5_B || mapTip.mapNumber == SLOPE_LEFT_22_5_C) {
//    tip.resized(20, 8)
//        .rotated(25_deg)
//        .draw(mapPos.x - 4, mapPos.y + 11, GetColorF(mapTip));
//}
//else {
