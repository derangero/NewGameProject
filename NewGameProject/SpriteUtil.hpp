#pragma once
#include "Siv3D.hpp"
#include "SpriteImageMetaData.hpp"

class SpriteUtil
{
public:
	static std::unordered_map<int, SpriteImageMetaData> GetEnemySpriteImageMetaDataMap(JSONReader json)
	{
		return GetSpriteImageMetaDataMap(json, false, MapType::NORMAL);
	}
	static std::unordered_map<int, SpriteImageMetaData> GetPlayerSpriteImageMetaDataMap(JSONReader json)
	{
		return GetSpriteImageMetaDataMap(json, true, MapType::NORMAL);
	}
	static std::unordered_map<int, SpriteImageMetaData> GetObjectSpriteImageMetaDataMap(JSONReader json, MapType objectType)
	{
		return GetSpriteImageMetaDataMap(json, true, objectType);
	}

	static std::unordered_map<int, SpriteImageMetaData> GetSpriteImageMetaDataMap(JSONReader json, bool isPlayer, MapType objectType)
	{
		std::unordered_map<int, SpriteImageMetaData> spriteImageMetaData;
		int index = 1;
		for (const auto jo : json.objectView()) {
			int maxImageNumber = jo.value[U"maxImageNumber"].get<int>();
			double interval = Parse<double>(jo.value[U"interval"].getString());
			double coolTime = Parse<double>(jo.value[U"coolTime"].getString());
			int status = !isPlayer ? jo.value[U"status"].get<int>() : 0;

			Array<Vec2> imageVecs;
			Array<Size> imageSizes;
			for (const auto imageVec : jo.value[U"vecs"].arrayView()) {
				imageVecs << imageVec.get<Vec2>();
			}
			for (const auto imageSize : jo.value[U"sizes"].arrayView()) {
				imageSizes << imageSize.get<Size>();
			}
			if (MapType::NORMAL == objectType) {
				spriteImageMetaData[!isPlayer ? status : index] = SpriteImageMetaData(maxImageNumber, interval, coolTime, imageVecs, imageSizes);
			}
			else {
				String jsonKeyName = jo.name;
				spriteImageMetaData[GetObjectType(jsonKeyName)] = SpriteImageMetaData(maxImageNumber, interval, coolTime, imageVecs, imageSizes);
			}
			index++;
		}
		return spriteImageMetaData;
	}

	static TextureRegion ExtractionImage(Texture allImage, SpriteImageMetaData icData, int imageNumber)
	{
		Vec2 targetVec2(icData.vecs[imageNumber]);
		Size targetSize(icData.sizes[imageNumber]);
		return allImage(targetVec2, targetSize);
	}

	static int GetObjectType(String jsonKeyName)
	{
		String name = jsonKeyName.split('_')[0];
		if (U"coin" == name) {
			return static_cast<int>(MapType::COIN);
		}
		else if (U"key" == name) {
			return static_cast<int>(MapType::KEY);
		}
		else {
			return 0;
		}
	}
};