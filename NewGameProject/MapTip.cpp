# include "MapTip.hpp"
# include "MapCreator.hpp"

MapTip::MapTip() : mapGridX(0), mapGridY(0), tipX(0.0), tipY(0.0), mapNumber(0),
    isTouched(false) {
}

/// <summary>
/// �}�b�v�`�b�v��`�悵�܂��B
/// </summary>
/// <param name="mapTips">MapTip�N���X�̓��I�z��</param>
/// <param name="allMapTip">�}�b�v�摜</param>
/// <param name="screenOriginPosition">�X�N���[���v�Z�p��Vec2</param>
void MapTip::DrawMapTipTextures(Array<MapTip> mapTips, Texture allMap, Vec2 &screenOriginPosition, Font font)
{
    for (auto i : step(mapTips.size())) {
        //TODO: �f�o�b�O�p�ɓ����蔻�������(���ۂ̔����PlayerCollisionDetection�N���X�ōs��)
        ColorF frameColor = mapTips[i].isTouched ? ColorF(0.4, 0.2, 0.7, 0.9) : ColorF(1.0, 1.0, 1.0, 0.5);
        mapTips[i].detection.movedBy(-screenOriginPosition).drawFrame(1, 1, frameColor);
        
        MapTip mapTip = mapTips[i];
        RectF mapDetection = mapTip.detection;
        TextureRegion tip = allMap(mapTip.tipX, mapTip.tipY, MAP_IMAGE_SQUARE_SIZE, MAP_IMAGE_SQUARE_SIZE);
        Vec2 mapPos = Vec2(
            mapTip.mapGridX - screenOriginPosition.x,
            mapTip.mapGridY - screenOriginPosition.y);
        // �`�b�v��`�悷��
        font(mapTip.mapNumber).draw(mapPos);
        //tip.draw(mapPos.x, mapPos.y, GetColorF(mapTip));
    }

}

ColorF MapTip::GetColorF(MapTip mapTip) {
    return MapCreator::IsNoCollision(mapTip.mapNumber)
        ? ColorF(1.0)
        : ColorF(1.0, 1.0, 1.0, 0.7);
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
