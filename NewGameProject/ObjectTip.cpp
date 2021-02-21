# include "objectTip.hpp"

ObjectTip::ObjectTip() :
    w(MAP_IMAGE_SQUARE_SIZE),
    h(MAP_IMAGE_SQUARE_SIZE),
    objectDetection(Polygon{ Vec2(0, 0) })
{
    this->isExists = true;
}


ObjectTip::ObjectTip(EnemyType enemyType, Point tip, XMLElement &elem)
{
    this->isExists = true;
    this->mapType = MapType::NORMAL;
    this->enemyType = enemyType;
    this->tip = tip;
    this->mapGrid = GetObjectTipXY(elem);
    this->collision = CreateCollision();
}

ObjectTip::ObjectTip(Point tip, XMLElement& elem)
{
    this->isExists = true;
    this->tip = tip;
    this->mapGrid = GetObjectTipXY(elem);
    this->collision = CreateCollision();
}

ObjectTip::ObjectTip(int mapNumber, double width, double height, Point tip, XMLElement &elem)
{
    this->isExists = true;
    this->mapType = mapType;
    this->mapNumber = mapNumber;
    this->w = width;
    this->h = height;
    this->tip = tip;
    this->mapGrid = GetObjectTipXY(elem);
    if (mapType == MapType::LADDER || mapType == MapType::UPPERMOST) {
        this->collision = RectF(mapGrid.x + 9, mapGrid.y, w - 20, h);
    }
    else if (mapType == MapType::TOP_ROCK) {
        this->collision = RectF(mapGrid.x, mapGrid.y, w, h);
    }
    else {
        this->collision = RectF(mapGrid.x, mapGrid.y, w, h);
    }
}

ObjectTip::ObjectTip(MapType _mapType, int mapNumber, double width, double height, Point tip, XMLElement &elem,
    double deltaAmt, double turningMoveAmt, Direction direction, int damage, double waitTime)
{
    this->isExists = true;
    this->mapType = _mapType;
    this->mapNumber = mapNumber;
    this->w = width;
    this->h = height;
    this->tip = tip;
    this->mapGrid = GetObjectTipXY(elem);
    this->deltaAmt = deltaAmt;
    this->moveAmt = 0.0;
    this->turningMoveAmt = turningMoveAmt;
    this->direction = direction;
    this->damage = damage;
    this->waitTime = waitTime;
    //if (_mapType == MapType::LADDER || _mapType == MapType::UPPERMOST || _mapType == MapType::LOWERMOST) {
    //    this->collision = RectF(mapGrid.x + 9, mapGrid.y, w - 20, h);
    //}
    //else {
    //    this->collision = RectF(mapGrid.x, mapGrid.y, w, h);
    //}
    this->collision = RectF(mapGrid.x, mapGrid.y, w, h);
}

RectF ObjectTip::CreateCollision()
{
    return RectF(mapGrid.x - 8, mapGrid.y, MAP_IMAGE_SQUARE_SIZE + 16, MAP_IMAGE_SQUARE_SIZE);
}

void ObjectTip::SetObjectTip(Array<ObjectTip> objectMapTips, Texture allMap, Vec2& screenOriginPosition)
{
    for (ObjectTip objectMapTip : objectMapTips) {
        if (!objectMapTip.isExists) {
            continue;
        }
        //TODO: デバッグ用に当たり判定を可視化(実際の判定はPlayerCollisionDetectionクラスで行う)
        //mapTips[i].detection.movedBy(-screenOriginPosition).draw(ColorF(1.0, 1.0, 1.0, 0));
        RectF mapDetection = objectMapTip.collision;
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
        objectMapTip.collision.movedBy(-screenOriginPosition).draw(ColorF(0.5, 0.5, 0.5, 0.5));
    }
}

Vec2 ObjectTip::GetObjectTipXY(XMLElement& elem)
{
    const double x = Parse<double>(elem.attribute(U"x").value());
    const double y = Parse<double>(elem.attribute(U"y").value()) - OBJECT_FIXED_Y;
    return Vec2(x, y);
}