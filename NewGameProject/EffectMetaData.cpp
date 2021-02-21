#include "EffectMetaData.hpp"

EffectMetaData::EffectMetaData()
{}

EffectMetaData::EffectMetaData(String name, Texture effectBase, Array<double> properties) :
	name(name),
	effectBase(effectBase),
	maxXCount(properties[0]),
	maxYCount(properties[1]),
	blanckCount(properties[2]),
	effectingSf(properties[3]),
	loopFlag(properties[4]),
	intervalSf(properties[5])
{}
