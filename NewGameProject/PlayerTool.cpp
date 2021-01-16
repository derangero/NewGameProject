#include "PlayerTool.hpp"

PlayerTool::PlayerTool() :
	wireTime(0.0),
	bulletName(BulletName::NONE)
{}

void PlayerTool::ExtendWire(Vec2 playerPos, RectF detection, double deltaTime)
{
	/*Vec2 linePos(detection.x + detection.w + 30, +(detection.y + 5));
	Vec2 fixedPos = MapScreenHelper::FixPosition(playerPos, linePos);
	wireTime += deltaTime * 900;
	double a = detection.x + detection.w + Min(wireTime, 100.0);
	double b = detection.y - Min(wireTime, 100.0);
	Line(detection.x + detection.w, detection.y, a, b)
		.draw(4,Palette::Blue);

	if (wireTime > 100) {
		const double theta = 2 * 30_deg + (Scene::Time() * 20) * 30_deg;
		const Vec2 pos = OffsetCircular(Vec2(a, b), 100.0, theta);
		Circle(pos, 20).draw(ColorF(0.25));
	}*/

}
