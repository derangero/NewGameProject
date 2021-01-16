#include "SpriteImageMetaData.hpp"

SpriteImageMetaData::SpriteImageMetaData()
{
}

SpriteImageMetaData::SpriteImageMetaData(int maxImageNumber, double interval, Array<Vec2> vecs, Array<Size> sizes) :
	maxImageNumber(maxImageNumber),
	interval(interval),
	vecs(vecs),
	sizes(sizes)
	{}
