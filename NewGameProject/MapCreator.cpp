#include "MapCreator.hpp"
#include "MapTip.hpp"
#include "MapObjectTip.hpp"
MapCreator::MapCreator()
{
}

/// <summary>
/// MapTipクラスの動的配列を取得します
/// </summary>
/// <param name="mapTexture">マップのテクスチャ</param>
/// <returns>MapTipクラスの動的配列</returns>
Array<MapTip> MapCreator::GetMapTips(Texture mapTexture)
{
    Array<MapTip> mapTips;
    Grid<int> mapGrid = MapCreator::CreateMapGrid();
    for (auto y : step(mapGrid.height()))
    {
        for (auto x : step(mapGrid.width()))
        {
            int imageNumber = mapGrid[y][x] - MAP_NUMBER_BASE;
            if (imageNumber > 0) { // 0はマップに何も描画しない箇所
                MapTip mapTip = MapTip();
                mapTip.tipX = (imageNumber > MAP_IMAGE_WIDTH_MAX ? imageNumber % MAP_IMAGE_WIDTH_MAX - 1 : 0) * MAP_IMAGE_SQUARE_SIZE; // 最大横幅
                mapTip.tipY = (imageNumber / MAP_IMAGE_WIDTH_MAX) * MAP_IMAGE_SQUARE_SIZE; // 横列の最大数を超えたら折り返す
                mapTip.mapGridX = x * MAP_IMAGE_SQUARE_SIZE;
                mapTip.mapGridY = y * MAP_IMAGE_SQUARE_SIZE;
                mapTip.mapNumber = imageNumber;
                mapTip.detection = !IsNoCollision(imageNumber)
                     ? RectF(x * MAP_IMAGE_SQUARE_SIZE, y * MAP_IMAGE_SQUARE_SIZE, MAP_IMAGE_SQUARE_SIZE)
                     : RectF(0, 0, 0);
                mapTips.push_back(mapTip);
            }
        }
    }
    return mapTips;
}
/// <summary>
/// マップのグリッドを作成します
/// </summary>
/// <returns>マップ用の可変長二次元配列</returns>
Grid<int> MapCreator::CreateMapGrid()
{
	// TMXファイルからXMLデータを読み込む
	const XMLReader xml(MAP_XML_PATH);
    if (!xml) // もし読み込みに失敗したら
    {
        throw Error(U"Failed to load `myGameTestMap.xml`");
    }
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
                            _ASSERT_EXPR(ParseOpt<int>(attribute.second), L"test");
                            width = Parse<int>(attribute.second);
                        }
                        else if (attribute.first == U"height") {
                            height = Parse<int>(attribute.second);
                            // U unicode
                            // L char32
                            _ASSERT_EXPR(false, L"test");
                        }
                    }
                    const String csv = elem2.text();
                    grid = Grid<int>(width, height);
                    int x = 0;
                    int y = 0;
                    for (auto imageNumber : csv.split(',')) {
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
            bool a = false;
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

Array<MapObjectTip> MapCreator::GetMapObjectTip()
{
    // TMXファイルからXMLデータを読み込む
    const XMLReader xml(MAP_XML_PATH);
    if (!xml) // もし読み込みに失敗したら
    {
        throw Error(U"Failed to load `myGameTestMap.xml`");
    }
    Array<MapObjectTip> mapObjectTips;
    for (auto elem = xml.firstChild(); elem; elem = elem.nextSibling())
    {
        // マップオブジェクトを利用する場合、MAP_OBJECT_NAMESにプロパティ名を設定する
        if (elem.name() == U"objectgroup" && MAP_OBJECT_NAMES.includes(elem.attribute(U"name").value())) {
             // elem.attribute(U"name") 時間かかる
            if (elem.attribute(U"name").value() == U"slope") {
                for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
                {
                    const int imageNumber = Parse<int>(elem2.attribute(U"name").value());
                    const String mapObjectType = elem2.attribute(U"type").value();
                    const double x = Parse<double>(elem2.attribute(U"x").value());
                    const double y = Parse<double>(elem2.attribute(U"y").value()) - OBJECT_FIXED_Y;
                    MapObjectTip mapObjectTip = MapObjectTip();
                    mapObjectTip.type = GetMapObjectType(mapObjectType);
                    // X, Y はVec2にまとめる
                    // メソッド化するとエラーを防げる
                    // バグではまったら反省、次回に活かす
                    mapObjectTip.tipX = (imageNumber > MAP_IMAGE_WIDTH_MAX ? imageNumber % MAP_IMAGE_WIDTH_MAX - 1 : 0) * MAP_IMAGE_SQUARE_SIZE; // 最大横幅
                    mapObjectTip.tipY = (imageNumber / MAP_IMAGE_WIDTH_MAX) * MAP_IMAGE_SQUARE_SIZE; // 横列の最大数を超えたら折り返す
                    mapObjectTip.mapGridX = x;
                    mapObjectTip.mapGridY = y;
                    mapObjectTip.detection = RectF(x - 8, y, MAP_IMAGE_SQUARE_SIZE + 16, MAP_IMAGE_SQUARE_SIZE);
                    Array<Vec2> posList;
                    for (auto elem3 = elem2.firstChild(); elem3; elem3 = elem3.nextSibling())
                    {
                        Array<String> strPolygonPosList = elem3.attribute(U"points").value().split(U' ');
                        for (auto i : step(strPolygonPosList.size())) {
                            Array<String> posArray = strPolygonPosList[i].split(U',');
                            auto x = Parse<double>(posArray[0]) + mapObjectTip.mapGridX;
                            auto y = Parse<double>(posArray[1]) + mapObjectTip.mapGridY + OBJECT_FIXED_Y;
                            posList.push_back(Vec2(x, y));
                        }
                    }
                    if (mapObjectTip.type == RIGHT_SLOPE) {
                        mapObjectTip.quadDetection = Quad(posList[0].movedBy(0.0, 0.0), posList[1],
                            posList[2], posList[3]);
                    }

                    mapObjectTips.push_back(mapObjectTip);
                }
            }
            else if (elem.attribute(U"name").value() == U"enemiesA") {
                for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
                {
                    const String enemyType = elem2.attribute(U"type").value();
                    const double x = Parse<double>(elem2.attribute(U"x").value());
                    const double y = Parse<double>(elem2.attribute(U"y").value()) - OBJECT_FIXED_Y;
                    MapObjectTip mapObjectTip = MapObjectTip();
                    mapObjectTip.enemyType = GetEnemyType(enemyType);
                    mapObjectTip.tipX = 64; // 最大横幅
                    mapObjectTip.tipY = 64; // 横列の最大数を超えたら折り返す
                    mapObjectTip.mapGridX = x;
                    mapObjectTip.mapGridY = y;
                    mapObjectTip.detection = RectF(x - 8, y, MAP_IMAGE_SQUARE_SIZE + 16, MAP_IMAGE_SQUARE_SIZE);
                    mapObjectTips.push_back(mapObjectTip);
                }
            }
            else {
                for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
                {
                    const String mapObjectType = elem2.attribute(U"type").value();
                    const int imageNumber = Parse<int>(elem2.attribute(U"gid").value());
                    const double x = Parse<double>(elem2.attribute(U"x").value());
                    //TODO:y軸がなぜか16px下にずれているので補正するが理由は不明
                    const double y = Parse<double>(elem2.attribute(U"y").value()) - 16;
                    MapObjectTip mapObjectTip = MapObjectTip();
                    mapObjectTip.w = Parse<double>(elem2.attribute(U"width").value());
                    mapObjectTip.h = Parse<double>(elem2.attribute(U"height").value());
                    mapObjectTip.type = GetMapObjectType(mapObjectType);
                    mapObjectTip.tipX = (imageNumber > MAP_IMAGE_WIDTH_MAX ? imageNumber % MAP_IMAGE_WIDTH_MAX - 1 : 0) * MAP_IMAGE_SQUARE_SIZE; // 最大横幅
                    mapObjectTip.tipY = (imageNumber / MAP_IMAGE_WIDTH_MAX) * MAP_IMAGE_SQUARE_SIZE; // 横列の最大数を超えたら折り返す
                    mapObjectTip.mapGridX = x;
                    mapObjectTip.mapGridY = y;
                    mapObjectTip.mapNumber = imageNumber;
                    if (mapObjectTip.type == LADDER || mapObjectTip.type == UPPERMOST) {
                        mapObjectTip.detection = RectF(x + 9, y, mapObjectTip.w - 20, mapObjectTip.h);

                    }
                    else if (mapObjectTip.type == TOP_ROCK) {
                        mapObjectTip.detection = RectF(x, y, mapObjectTip.w, mapObjectTip.h);
                    }
                    mapObjectTips.push_back(mapObjectTip);
                }
            }
        }
    }
    return mapObjectTips;
}

MapObjectType MapCreator::GetMapObjectType(String mapObjectType) {
    if (mapObjectType == U"UPPERMOST") {
        return UPPERMOST;
    }
    else if (mapObjectType == U"LADDER") {
        return LADDER;
    }
    else if (mapObjectType == U"LOWERMOST") {
        return LOWERMOST;
    }
    else if (mapObjectType == U"RIGHT_SLOPE") {
        return RIGHT_SLOPE;
    }
    else if (mapObjectType == U"RIGHT_SLOPE_UP") {
        return RIGHT_SLOPE_UP;
    }
    else if (mapObjectType == U"GRASS_A") {
        return GRASS_A;
    }
    else if (mapObjectType == U"TOP_ROCK") {
        return TOP_ROCK;
    }
    return MapObjectType::NONE;
}

EnemyType MapCreator::GetEnemyType(String enemyType) {
    if (enemyType == U"EYE") {
        return EnemyType::EYE;
    }
    return EnemyType::NONE;
}

// 再帰的に XML の要素を表示
void MapCreator::ShowElements(const XMLElement& element)
{
    for (auto e = element.firstChild(); e; e = e.nextSibling())
    {
        Print << U"<{}>"_fmt(e.name());

        if (const auto attributes = e.attributes())
        {
            Print << attributes;
        }

        if (const auto text = e.text())
        {
            Print << text;
        }
        ShowElements(e);
        Print << U"</{}>"_fmt(e.name());
    }
}

bool MapCreator::IsNoCollision(int imageNumber) {
    return NO_COLLISION_MAP.includes(imageNumber);
}