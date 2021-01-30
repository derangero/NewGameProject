#include "SpriteImageMetaData.hpp"

SpriteImageMetaData::SpriteImageMetaData()
{
}

SpriteImageMetaData::SpriteImageMetaData(int maxImageNumber, double interval, double coolTime, Array<Vec2> vecs, Array<Size> sizes) :
	maxImageNumber(maxImageNumber),
	interval(interval),
	coolTime(coolTime),
	vecs(vecs),
	sizes(sizes)
	{}
