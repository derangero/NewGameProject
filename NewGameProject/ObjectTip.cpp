# include "objectTip.hpp"

ObjectTip::ObjectTip()
{
    this->w = MAP_IMAGE_SQUARE_SIZE;
    this->h = MAP_IMAGE_SQUARE_SIZE;
    this->type = NONE;
    this->objectDetection = Polygon{ Vec2(0, 0) };
    this->quadDetection = Quad();
    this->triDetection = Triangle();

}

void ObjectTip::SetObjectTip(Array<ObjectTip> objectMapTips, Texture allMap, Vec2& screenOriginPosition)
{
    for (auto i : step(objectMapTips.size())) {
        //TODO: デバッグ用に当たり判定を可視化(実際の判定はPlayerCollisionDetectionクラスで行う)
        //mapTips[i].detection.movedBy(-screenOriginPosition).draw(ColorF(1.0, 1.0, 1.0, 0));
        ObjectTip objectMapTip = objectMapTips[i];
        RectF mapDetection = objectMapTip.detection;
        TextureRegion tip = allMap(objectMapTip.tip.x, objectMapTip.tip.y,
            MAP_IMAGE_SQUARE_SIZE, MAP_IMAGE_SQUARE_SIZE).resized(objectMapTip.w, objectMapTip.h);
        Vec2 mapPos = Vec2(
            objectMapTip.mapGrid.x - screenOriginPosition.x,
            objectMapTip.mapGrid.y - screenOriginPosition.y);
        // チップを描画する
        //objectMapTip.triDetection.movedBy(-screenOriginPosition).draw(ColorF(0.5, 0.5, 0.5, 0.5));
        if (objectMapTip.quadDetection.p0.x == 0.0) {
            tip.draw(mapPos.x, mapPos.y);
        }
        //objectMapTip.quadDetection.movedBy(-screenOriginPosition)(tip).draw();
        objectMapTip.quadDetection.movedBy(-screenOriginPosition).draw(ColorF(0.5, 0.5, 0.5, 0.5));
        objectMapTip.detection.movedBy(-screenOriginPosition).draw(ColorF(0.5, 0.5, 0.5, 0.5));
    }
}

Vec2 ObjectTip::GetObjectTipXY(XMLElement& elem)
{
    const double x = Parse<double>(elem.attribute(U"x").value());
    const double y = Parse<double>(elem.attribute(U"y").value()) - OBJECT_FIXED_Y;
    return Vec2(x, y);
}