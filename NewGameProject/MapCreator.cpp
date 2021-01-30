#include "MapCreator.hpp"
#include "MapTip.hpp"
#include "ObjectTip.hpp"

MapCreator::MapCreator(Texture mapTexture)
{
    CreateMapTips(mapTexture);
    CreateObjectTip();
}

/// <summary>
/// MapTip�N���X�̓��I�z����쐬���܂�
/// </summary>
/// <param name="mapTexture">�}�b�v�摜</param>
void MapCreator::CreateMapTips(Texture mapTexture)
{
    Grid<int> mapGrid = MapCreator::CreateMapGrid();
    for (int y : step(mapGrid.height()))
    {
        for (int x : step(mapGrid.width()))
        {
            int imageNumber = mapGrid[y][x] - MAP_NUMBER_BASE;
            if (imageNumber > 0) { // 0�̓}�b�v�ɉ����`�悵�Ȃ��ӏ�
                MapTip mapTip;
                mapTip.tip = CreateTipPoint(imageNumber);
                mapTip.mapNumber = imageNumber;
                double mapGridX = x * MAP_IMAGE_SQUARE_SIZE;
                double mapGridY = y * MAP_IMAGE_SQUARE_SIZE;
                mapTip.mapGrid = Vec2(mapGridX, mapGridY);
                mapTip.detection = !IsNoCollision(imageNumber)
                     ? RectF(x * MAP_IMAGE_SQUARE_SIZE, y * MAP_IMAGE_SQUARE_SIZE, MAP_IMAGE_SQUARE_SIZE)
                     : RectF(0, 0, 0);
                this->mapTips.push_back(mapTip);
            }
        }
    }
}

/// <summary>
/// �}�b�v�̃O���b�h���쐬���܂�
/// </summary>
/// <returns>�}�b�v�p�̉ϒ��񎟌��z��</returns>
Grid<int> MapCreator::CreateMapGrid()
{
	// TMX�t�@�C������XML�f�[�^��ǂݍ���
	const XMLReader xml(MAP_XML_PATH);
    _ASSERT_EXPR(xml, L"Failed to load `myGameTestMap.xml`");
    Grid<int> grid(0, 0);
    // TiledMapEditor�̃}�b�v�f�[�^���擾
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
                        grid[x][y++] = Parse<int>(imageNumber); // �^�C���h�}�b�v�G�f�B�^�[�̏���Grid�N���X�ɕϊ��i�摜�ԍ������j
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
    // TMX�t�@�C������XML�f�[�^��ǂݍ���
    const XMLReader xml(MAP_XML_PATH);
    _ASSERT_EXPR(xml, L"Failed to load `myGameTestMap.xml`");
    //Array<ObjectTip> objectTips;
    for (auto elem = xml.firstChild(); elem; elem = elem.nextSibling())
    {
        // �}�b�v�I�u�W�F�N�g�𗘗p����ꍇ�AMAP_OBJECT_NAMES�Ƀv���p�e�B����ݒ肷��
        if (elem.name() == U"objectgroup" && MAP_OBJECT_NAMES.includes(elem.attribute(U"name").value())) {
            if (elem.attribute(U"name").value() == U"slope") {
                for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
                {
                    const int imageNumber = Parse<int>(elem2.attribute(U"name").value());
                    const String mapObjectType = elem2.attribute(U"type").value();
                    ObjectTip objectTip;
                    objectTip.type = GetMapObjectType(mapObjectType);
                    objectTip.tip = CreateTipPoint(imageNumber);
                    objectTip.mapGrid = objectTip.GetObjectTipXY(elem2);
                    objectTip.detection = RectF(objectTip.mapGrid.x - 8, objectTip.mapGrid.y, MAP_IMAGE_SQUARE_SIZE + 16, MAP_IMAGE_SQUARE_SIZE);
                    Array<Vec2> posList;
                    for (auto elem3 = elem2.firstChild(); elem3; elem3 = elem3.nextSibling())
                    {
                        Array<String> strPolygonPosList = elem3.attribute(U"points").value().split(U' ');
                        for (auto i : step(strPolygonPosList.size())) {
                            Array<String> posArray = strPolygonPosList[i].split(U',');
                            auto x = Parse<double>(posArray[0]) + objectTip.mapGrid.x;
                            auto y = Parse<double>(posArray[1]) + objectTip.mapGrid.y + OBJECT_FIXED_Y;
                            posList.push_back(Vec2(x, y));
                        }
                    }
                    if (objectTip.type == RIGHT_SLOPE) {
                        objectTip.quadDetection = Quad(posList[0].movedBy(0.0, 0.0), posList[1],
                            posList[2], posList[3]);
                    }

                    this->objectTips.push_back(objectTip);
                }
            }
            else if (elem.attribute(U"name").value() == U"enemiesA") {
                for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
                {
                    // TODO:�g�p���邩�s��
                    const String enemyType = elem2.attribute(U"type").value();
                    ObjectTip objectTip;
                    objectTip.enemyType = GetEnemyType(enemyType);
                    objectTip.tip = Point(64, 64);// �ő剡��, ����̍ő吔�𒴂�����܂�Ԃ�
                    objectTip.mapGrid = objectTip.GetObjectTipXY(elem2);
                    objectTip.detection = RectF(objectTip.mapGrid.x - 8, objectTip.mapGrid.y, MAP_IMAGE_SQUARE_SIZE + 16, MAP_IMAGE_SQUARE_SIZE);
                    this->objectTips.push_back(objectTip);
                }
            }
            else {
                //TODO: �n�V�S�@������
                for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
                {
                    const String mapObjectType = elem2.attribute(U"type").value();
                    ObjectTip objectTip;
                    objectTip.mapNumber = Parse<int>(elem2.attribute(U"gid").value());
                    objectTip.w = Parse<double>(elem2.attribute(U"width").value());
                    objectTip.h = Parse<double>(elem2.attribute(U"height").value());
                    objectTip.type = GetMapObjectType(mapObjectType);
                    objectTip.tip = CreateTipPoint(objectTip.mapNumber);
                    objectTip.mapGrid = objectTip.GetObjectTipXY(elem2);
                    if (objectTip.type == LADDER || objectTip.type == UPPERMOST) {
                        objectTip.detection = RectF(objectTip.mapGrid.x + 9, objectTip.mapGrid.y, objectTip.w - 20, objectTip.h);
                    }
                    else if (objectTip.type == TOP_ROCK) {
                        objectTip.detection = RectF(objectTip.mapGrid.x, objectTip.mapGrid.y, objectTip.w, objectTip.h);
                    }
                    this->objectTips.push_back(objectTip);
                }
            }
        }
    }
}

MapObjectType MapCreator::GetMapObjectType(String mapObjectType) {
    // TODO:�����Ƃ������肵�������͂Ȃ����낤���H
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

bool MapCreator::IsNoCollision(int imageNumber) {
    return NO_COLLISION_MAP.includes(imageNumber);
}

void MapCreator::SetObjectTip(Texture allMap, Vec2& screenOriginPosition)
{
    for (ObjectTip objectTip : objectTips) {
        //TODO: �f�o�b�O�p�ɓ����蔻�������(���ۂ̔����PlayerCollisionDetection�N���X�ōs��)
        //mapTips[i].detection.movedBy(-screenOriginPosition).draw(ColorF(1.0, 1.0, 1.0, 0));
        RectF mapDetection = objectTip.detection;
        TextureRegion tip = allMap(objectTip.tip.x, objectTip.tip.y,
            MAP_IMAGE_SQUARE_SIZE, MAP_IMAGE_SQUARE_SIZE).resized(objectTip.w, objectTip.h);
        Vec2 mapPos = Vec2(
            objectTip.mapGrid.x - screenOriginPosition.x,
            objectTip.mapGrid.y - screenOriginPosition.y);
        // �`�b�v��`�悷��
        //objectMapTip.triDetection.movedBy(-screenOriginPosition).draw(ColorF(0.5, 0.5, 0.5, 0.5));
        if (objectTip.quadDetection.p0.x == 0.0) {
            tip.draw(mapPos.x, mapPos.y);
        }
        //objectMapTip.quadDetection.movedBy(-screenOriginPosition)(tip).draw();
        objectTip.quadDetection.movedBy(-screenOriginPosition).draw(ColorF(0.5, 0.5, 0.5, 0.5));
        objectTip.detection.movedBy(-screenOriginPosition).draw(ColorF(0.5, 0.5, 0.5, 0.5));
    }
}

Point MapCreator::CreateTipPoint(int imageNumber)
{
    int tipX = (imageNumber > MAP_IMAGE_WIDTH_MAX ? imageNumber % MAP_IMAGE_WIDTH_MAX - 1 : 0) * MAP_IMAGE_SQUARE_SIZE; // �ő剡��
    int tipY = (imageNumber / MAP_IMAGE_WIDTH_MAX) * MAP_IMAGE_SQUARE_SIZE; // ����̍ő吔�𒴂�����܂�Ԃ�

    return Point(tipX, tipY);
}