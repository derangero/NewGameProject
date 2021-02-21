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
/// マップチップを描画します。
/// </summary>
/// <param name="mapTips">MapTipクラスの動的配列</param>
/// <param name="allMapTip">マップ画像</param>
/// <param name="screenOriginPosition">スクロール計算用のVec2</param>
void MapTip::DrawMapTipTextures(Array<MapTip> mapTips, Texture allMap, Vec2 &screenOriginPosition, Font font)
{
    for (MapTip &mapTip : mapTips) {
        //TODO: デバッグ用に当たり判定を可視化(実際の判定はPlayerCollisionDetectionクラスで行う)
        ColorF frameColor = mapTip.touched ? ColorF(0.4, 0.2, 0.7, 0.9) : ColorF(1.0, 1.0, 1.0, 0.5);
        mapTip.collision.movedBy(-screenOriginPosition).drawFrame(1, 1, frameColor);
        
        RectF mapDetection = mapTip.collision;
        TextureRegion tip = allMap(mapTip.tip.x, mapTip.tip.y, MAP_IMAGE_SQUARE_SIZE, MAP_IMAGE_SQUARE_SIZE);
        Vec2 mapPos = Vec2(
            mapTip.mapGrid.x - screenOriginPosition.x,
            mapTip.mapGrid.y - screenOriginPosition.y);
        // チップを描画する
        font(mapTip.mapNumber).draw(mapPos);
        //tip.draw(mapPos.x, mapPos.y, GetColorF(mapTip));
    }

}

/// <summary>
/// 左登りスロープの当たり判定用のQuadを取得します。
/// これは22.5度の判定を構築するための左パーツです。
/// 22.5度スロープはQuadパーツ(A)とTriangleパーツ(B)を合わせて表現します。
/// また、Triangleパーツ(C)は(B)の代わりに地面接着部分に使用します。
/// </summary>
/// <param name="mapPos">マップチップの位置</param>
/// <returns>Triangleオブジェクト</returns>
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
//    //TO REFINE:坂道のマップチップが無かったので苦肉の策
//    // 正方形->長方形にしてひし形にし座標を左下にずらす
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
