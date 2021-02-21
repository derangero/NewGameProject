#include "MapCreator.hpp"
#include "MapTip.hpp"
#include "ObjectTip.hpp"

MapCreator::MapCreator(Texture mapTexture) :
    getAllCoin(false),
    keyAppearance(false),
    backGround_0(U"image/backGround/background_0.png"),
    backGround_1(U"image/backGround/background_1.png"),
    backGround_2(U"image/backGround/background_2.png"),
    objectSprite(Texture(U"image/objectSprite.png"))
{
    for (MapType mapType : { MapType::COIN })
    {
        objectImageNumberMap[static_cast<int>(mapType)] = 0;
        objectStopWatchMap[static_cast<int>(mapType)] = Stopwatch();
    }
    CreateMapTips(mapTexture);
    CreateObjectTip();
}

/// <summary>
/// MapTipクラスの動的配列を作成します
/// </summary>
/// <param name="mapTexture">マップ画像</param>
void MapCreator::CreateMapTips(Texture mapTexture)
{
    Grid<int> mapGrid = MapCreator::CreateMapGrid();
    for (int y : step(mapGrid.height()))
    {
        for (int x : step(mapGrid.width()))
        {
            int imageNumber = mapGrid[y][x] - MAP_NUMBER_BASE;
            if (imageNumber > 0) { // 0はマップに何も描画しない箇所
                MapTip mapTip;
                mapTip.tip = CreateTipPoint(imageNumber);
                mapTip.mapNumber = imageNumber;
                double mapGridX = x * MAP_IMAGE_SQUARE_SIZE;
                double mapGridY = y * MAP_IMAGE_SQUARE_SIZE;
                mapTip.mapGrid = Vec2(mapGridX, mapGridY);
                mapTip.collision = !IsNoCollision(imageNumber)
                     ? RectF(x * MAP_IMAGE_SQUARE_SIZE, y * MAP_IMAGE_SQUARE_SIZE, MAP_IMAGE_SQUARE_SIZE)
                     : RectF(0, 0, 0);
                this->mapTips.push_back(mapTip);
            }
        }
    }
}

/// <summary>
/// マップのグリッドを作成します
/// </summary>
/// <returns>マップ用の可変長二次元配列</returns>
Grid<int> MapCreator::CreateMapGrid()
{
	// TMXファイルからXMLデータを読み込む
	const XMLReader xml(MAP_XML_PATH);
    _ASSERT_EXPR(xml, L"Failed to load `myGameTestMap.xml`");
    Grid<int> grid(0, 0);
    // TiledMapEditorのマップデータを取得
    for (auto elem = xml.firstChild(); elem; elem = elem.nextSibling())
    {
        const String name = elem.name();
        const String text = elem.text();
        if (name == U"layer")
        {
            for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
            {
                const String name2 = elem2.name();
                if (name2 == U"data")
                {
                    const auto attributes = elem2.parent().attributes();
                    int width = 0;
                    int height = 0;
                    for (auto attribute : attributes) {
                        if (attribute.first == U"width") {
                            width = Parse<int>(attribute.second);
                        }
                        else if (attribute.first == U"height") {
                            height = Parse<int>(attribute.second);
                        }
                    }
                    grid = Grid<int>(width, height);
                    const String csv = elem2.text();
                    int x = 0;
                    int y = 0;
                    for (String imageNumber : csv.split(',')) {
                        grid[x][y++] = Parse<int>(imageNumber); // タイルドマップエディターの情報をGridクラスに変換（画像番号を代入）
                        if (y >= width) {
                            x++;
                            y = 0;
                        }
                    }
                }
            }
        }
        else if (name == U"objectgroup") {
            auto elem3 = elem.attribute(U"name").value();
            for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
            {
                const String name2 = elem2.name();
                const String text2 = elem2.text();
            }
        }
    }
    return grid;
}

void MapCreator::CreateObjectTip()
{
    const XMLReader xml(MAP_XML_PATH);
    _ASSERT_EXPR(xml, L"Failed to load `myGameTestMap.xml`");
    String jsonURI = U"ini/";
    JSONReader objectImageJson(jsonURI.append(U"objectImage").append(U".json"));
    spriteMetaDataMap.merge(SpriteUtil::GetObjectSpriteImageMetaDataMap(objectImageJson, MapType::KEY));
    for (auto elem = xml.firstChild(); elem; elem = elem.nextSibling())
    {
        if (elem.name() != U"objectgroup") {
            continue;
        }
        auto GetElemValue = [&](String key) {
            return elem.attribute(key).value();
        };
        ObjectTip objectTip;
        String elemName = GetElemValue(U"name");
        bool created = false;
        for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
        {
            MapType mapType = GetMapType(elem2.attribute(U"type").value());
            if (MapType::NORMAL == mapType) {
                continue;
            }
            created = CreateEnemy(objectTip, elemName, elem2);
            created = CreatePieceObject(objectTip, elemName, elem2, mapType);
            if (!created) {
                CreateObject(objectTip, elemName, elem2, mapType);
            }
            for (auto elem3 = elem2.firstChild(); elem3; elem3 = elem3.nextSibling())
            {
                for (auto elem4 = elem3.firstChild(); elem4; elem4 = elem4.nextSibling())
                {
                    if (elem4.attribute(U"name").value() == U"blockBehave") {
                        objectTip.blockBehave = Parse<bool>(elem4.attribute(U"value").value());
                    }
                }
            }
            objectTip.id = Parse<long>(elem2.attribute(U"id").value());
            this->objectTips.push_back(objectTip);
        }
    }
}

bool MapCreator::CreateEnemy(ObjectTip &objectTip, String elemName, XMLElement &elem2)
{
    if (elemName != U"enemiesA") {
        return false;
    }
    const String enemyType = elem2.attribute(U"type").value();
    objectTip = ObjectTip(GetEnemyType(enemyType), Point(64, 64), elem2);
    return true;
}

/// <summary>
/// あたり判定を加工する必要のあるオブジェクトを作成します
/// </summary>
/// <param name="objectTip">オブジェクトチップ</param>
/// <param name="elemName">オブジェクトの名前</param>
/// <param name="elem2">ネストレベル２のXML</param>
/// <returns>作成したかどうか</returns>
bool MapCreator::CreatePieceObject(ObjectTip &objectTip, String elemName, XMLElement &elem2, MapType mapType)
{
    if (elemName != U"pieceObject") {
        return false;
    }
    int hitBoxX = 0;
    int hitBoxY = 0;
    for (auto elem3 = elem2.firstChild(); elem3; elem3 = elem3.nextSibling())
    {
        for (auto elem4 = elem3.firstChild(); elem4; elem4 = elem4.nextSibling())
        {
            if (elem4.attribute(U"name").value() == U"hitBoxX") {
                hitBoxX = Parse<int>(elem4.attribute(U"value").value());
            }
            else if (elem4.attribute(U"name").value() == U"hitBoxY") {
                hitBoxY = Parse<int>(elem4.attribute(U"value").value());
            }
        }
    }
    objectTip.mapType = mapType;
    objectTip.tip = Point(hitBoxX, hitBoxY);// 最大横幅, 横列の最大数を超えたら折り返す
    objectTip.mapGrid = objectTip.GetObjectTipXY(elem2);
    objectTip.collision = RectF(objectTip.mapGrid.x, objectTip.mapGrid.y, hitBoxX, hitBoxY);
    return true;
}

void MapCreator::CreateObject(ObjectTip &objectTip, String elemName, XMLElement &elem2, MapType _mapType)
{
    int mapNumber = Parse<int>(elem2.attribute(U"gid").value());
    auto deltaAmt = 0.0;
    auto turningMoveAmt = 0.0;
    String direction = U"";
    auto damage = 0;
    double waitTime = 0.0;
    for (auto elem3 = elem2.firstChild(); elem3; elem3 = elem3.nextSibling())
    {
        for (auto elem4 = elem3.firstChild(); elem4; elem4 = elem4.nextSibling())
        {
            if (elem4.attribute(U"name").value() == U"deltaAmt") {
                deltaAmt = Parse<double>(elem4.attribute(U"value").value());
            }
            else if (elem4.attribute(U"name").value() == U"turningMoveAmt") {
                turningMoveAmt = Parse<double>(elem4.attribute(U"value").value());
            }
            else if (elem4.attribute(U"name").value() == U"direction") {
                direction = elem4.attribute(U"value").value();
            }
            else if (elem4.attribute(U"name").value() == U"damage") {
                damage = Parse<int>(elem4.attribute(U"value").value());
            }
            else if (elem4.attribute(U"name").value() == U"waitTime") {
                waitTime = Parse<int>(elem4.attribute(U"value").value());
            }
        }
    }
    objectTip = ObjectTip(
        _mapType,
        mapNumber,
        Parse<double>(elem2.attribute(U"width").value()),
        Parse<double>(elem2.attribute(U"height").value()),
        CreateTipPoint(mapNumber),
        elem2,
        deltaAmt,
        turningMoveAmt,
        GetDirection(direction),
        damage,
        waitTime);
}

Direction MapCreator::GetDirection(String direction)
{
    if (direction == U"UP") {
        return Direction::UP;
    }
    else if (direction == U"DOWN") {
        return Direction::DOWN;
    }
    else if (direction == U"LEFT") {
        return Direction::LEFT;
    }
    else if (direction == U"RIGHT") {
        return Direction::RIGHT;
    }
    return Direction::NONE;
}

MapType MapCreator::GetMapType(String mapType) {
    // TODO:もっとすっきりしたやり方はないだろうか？
    if (mapType == U"UPPERMOST") {
        return MapType::UPPERMOST;
    }
    else if (mapType == U"LADDER") {
        return MapType::LADDER;
    }
    else if (mapType == U"LOWERMOST") {
        return MapType::LOWERMOST;
    }
    else if (mapType == U"RIGHT_SLOPE") {
        return MapType::RIGHT_SLOPE;
    }
    else if (mapType == U"RIGHT_SLOPE_UP") {
        return MapType::RIGHT_SLOPE_UP;
    }
    else if (mapType == U"TOP_ROCK") {
        return MapType::TOP_ROCK;
    }
    else if (mapType == U"AIR_BROW_UP") {
        return MapType::AIR_BROW_UP;
    }
    else if (mapType == U"MOVE_FLOOR_A") {
        return MapType::MOVE_FLOOR_A;
    }
    else if (mapType == U"DAMAGE_FLOOR_A") {
        return MapType::DAMAGE_FLOOR_A;
    }
    else if (mapType == U"ENEMY_WAIT_A") {
        return MapType::ENEMY_WAIT_A;
    }
    else if (mapType == U"COIN") {
        return MapType::COIN;
    }
    else if (mapType == U"KEY") {
        return MapType::KEY;
    }
    else if (mapType == U"MOVABLE_OBJ_A") {
        return MapType::MOVABLE_OBJ_A;
    }
    return MapType::NORMAL;
}

EnemyType MapCreator::GetEnemyType(String enemyType) {
    if (enemyType == U"EYE") {
        return EnemyType::EYE;
    }
    return EnemyType::NONE;
}

bool MapCreator::IsNoCollision(int imageNumber) {
    return NO_COLLISION_MAP.includes(imageNumber);
}

void MapCreator::DrawBackGround()
{
    DrawBackGround(backGround_0);
    DrawBackGround(backGround_1);
    DrawBackGround(backGround_2);
}

void MapCreator::DrawBackGround(Texture image)
{
    image.resized(800, 600).draw(Vec2(0, 0));
}

double MapCreator::GetObjectMoveXAmt(ObjectTip &objectTip)
{
    double deltaXAmt = 0.0;
    if (Direction::RIGHT == objectTip.direction) {
        deltaXAmt = objectTip.deltaAmt;
    }
    if (Direction::LEFT == objectTip.direction) {
        deltaXAmt = -(objectTip.deltaAmt);
    }
    return deltaXAmt;
}

double MapCreator::GetObjectMoveYAmt(ObjectTip &objectTip)
{
    double deltaYAmt = 0.0;
    if (Direction::UP == objectTip.direction) {
        deltaYAmt = -(objectTip.deltaAmt);
    }
    if (Direction::DOWN == objectTip.direction) {
        deltaYAmt = objectTip.deltaAmt;
    }
    return deltaYAmt;
}

void MapCreator::DrawObjectTip(Texture allMap, Vec2& screenOriginPosition, TimeManager timeManager, Player& player)
{
    int coinCount = 0;
    double deltaAmt = 0.0;
    for (ObjectTip &objectTip : objectTips) {
        //TODO: デバッグ用に当たり判定を可視化(実際の判定はPlayerCollisionDetectionクラスで行う)
        //mapTips[i].detection.movedBy(-screenOriginPosition).draw(ColorF(1.0, 1.0, 1.0, 0));
        //RectF mapDetection = objectTip.detection;
        Vec2 mapPos = Vec2(
            objectTip.mapGrid.x - screenOriginPosition.x,
            objectTip.mapGrid.y - screenOriginPosition.y);
        if (objectTip.mapType == MapType::COIN || objectTip.mapType == MapType::KEY) {
            SpriteImageMetaData metaData = spriteMetaDataMap[static_cast<int>(objectTip.mapType)];
            int &objectImageNumber = objectImageNumberMap[static_cast<int>(objectTip.mapType)];
            Stopwatch &objectStopWatch = objectStopWatchMap[static_cast<int>(objectTip.mapType)];
            TextureRegion tip = SpriteUtil::ExtractionImage(objectSprite, metaData, objectImageNumber);
            if (objectTip.mapType == MapType::COIN && objectTip.isExists) {
                tip.scaled(0.25).draw(mapPos.x, mapPos.y);
                objectTip.collision = RectF(objectTip.collision.pos, tip.scaled(0.25).size);
                coinCount += 1;
            }
            else if(objectTip.mapType == MapType::KEY) {
                objectTip.isExists = keyAppearance;
                if (keyAppearance && !player.gameFinished) {
                   tip.draw(mapPos.x, mapPos.y);
                }
                if (objectTip.isExists) {
                    objectTip.collision = RectF(keyAppearance
                            ? objectTip.collision.pos
                            : Vec2::Zero(),
                        tip.size);
                }
            }
            timeManager.IncrementNumberByRepeat(objectImageNumber, metaData.maxImageNumber, metaData.interval, objectStopWatch);
        }
        else if (MapType::MOVE_FLOOR_A == objectTip.mapType) {
            double deltaXAmt = GetObjectMoveXAmt(objectTip);
            double deltaYAmt = GetObjectMoveYAmt(objectTip);
            objectTip.tip.x += deltaXAmt;
            objectTip.mapGrid.x += deltaXAmt;
            objectTip.tip.y += deltaYAmt;
            objectTip.mapGrid.y += deltaYAmt;
            TextureRegion tip = allMap(objectTip.tip.x, objectTip.tip.y,
                MAP_IMAGE_SQUARE_SIZE, MAP_IMAGE_SQUARE_SIZE).resized(objectTip.w, objectTip.h);
            if (objectTip.quadDetection.p0.x == 0.0) {
                tip.draw(mapPos.x + objectTip.deltaAmt, mapPos.y);
            }
            objectTip.collision.pos.x += deltaXAmt;
            objectTip.collision.pos.y += deltaYAmt;
            objectTip.collision = RectF(objectTip.collision.pos , tip.size);
            objectTip.moveAmt += deltaXAmt + deltaYAmt;
            if (Direction::RIGHT == objectTip.direction && objectTip.moveAmt > objectTip.turningMoveAmt) {
                objectTip.direction = Direction::LEFT;
                objectTip.moveAmt = 0.0;
            } else if (Direction::LEFT == objectTip.direction && objectTip.moveAmt < -(objectTip.turningMoveAmt)) {
                objectTip.direction = Direction::RIGHT;
                objectTip.moveAmt = 0.0;
            } else if (Direction::UP == objectTip.direction && objectTip.moveAmt < -(objectTip.turningMoveAmt)) {
                objectTip.direction = Direction::DOWN;
                objectTip.moveAmt = 0.0;
            } else if (Direction::DOWN == objectTip.direction && objectTip.moveAmt > objectTip.turningMoveAmt) {
                objectTip.direction = Direction::UP;
                objectTip.moveAmt = 0.0;
            }
        }
        else if (MapType::MOVABLE_OBJ_A == objectTip.mapType) {
            //double deltaXAmt = 0.0;
            //if (Direction::RIGHT == objectTip.direction) {
            //    deltaXAmt = objectTip.deltaAmt;
            //}
            //else if (Direction::LEFT == objectTip.direction) {
            //    deltaXAmt = -(objectTip.deltaAmt);
            //}
            //objectTip.tip.x += deltaXAmt;
            //objectTip.mapGrid.x += deltaXAmt;
            //TextureRegion tip = allMap(objectTip.tip.x, objectTip.tip.y,
            //    MAP_IMAGE_SQUARE_SIZE, MAP_IMAGE_SQUARE_SIZE).resized(objectTip.w, objectTip.h);
            //if (objectTip.quadDetection.p0.x == 0.0) {
            //    tip.draw(mapPos.x + objectTip.deltaAmt, mapPos.y);
            //}
            //objectTip.collision.pos.x += deltaXAmt;
            //objectTip.collision = RectF(objectTip.collision.pos, tip.size);
            //objectTip.moveAmt += deltaXAmt;
        }
        else {
            TextureRegion tip = allMap(objectTip.tip.x, objectTip.tip.y,
                MAP_IMAGE_SQUARE_SIZE, MAP_IMAGE_SQUARE_SIZE).resized(objectTip.w, objectTip.h);
            if (objectTip.quadDetection.p0.x == 0.0) {
                tip.draw(mapPos.x, mapPos.y);
            }
        }
        // チップを描画する
        //objectMapTip.triDetection.movedBy(-screenOriginPosition).draw(ColorF(0.5, 0.5, 0.5, 0.5));
        //objectMapTip.quadDetection.movedBy(-screenOriginPosition)(tip).draw();
        objectTip.quadDetection.movedBy(-screenOriginPosition).draw(ColorF(0.5, 0.5, 0.5, 0.5));
        objectTip.collision.movedBy(-screenOriginPosition).draw(ColorF(0.5, 0.5, 0.5, 0.5));
    }
    this->getAllCoin = coinCount == 0;
}

Point MapCreator::CreateTipPoint(int imageNumber)
{
    int tipX = (imageNumber > MAP_IMAGE_WIDTH_MAX ? imageNumber % MAP_IMAGE_WIDTH_MAX - 1 : 0) * MAP_IMAGE_SQUARE_SIZE; // 最大横幅
    int tipY = (imageNumber / MAP_IMAGE_WIDTH_MAX) * MAP_IMAGE_SQUARE_SIZE; // 横列の最大数を超えたら折り返す

    return Point(tipX, tipY);
}