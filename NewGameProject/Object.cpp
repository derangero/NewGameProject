#include "Object.hpp"

Object::Object() :
	isExists(false), velocity(0.0), imageNumber(0)
{
}

void Object::ClearPos()
{
	pos = Vec2::Zero();
	hitBox = RectF();
}

Object::~Object()
{
}
