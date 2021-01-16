#include "Player.hpp"

Player::Player() :
		jumpMode(UP),
		shortJumpIndex(0),
		waitCount(0),
		tempXBeforDash(0.0),
		jumpFlameCount(0),
		walkFlag(false),
		crouchFlag(false),
		jumpFlag(false),
		jumpFallFlag(false),
		dashFlag(false),
		afterDashFlag(false),
		leftWallFlag(false),
		rightWallFlag(false),
		topWallFlag(false),
		naturalFallFlag(true),
		topWallFlag2(false),
		attack1Number(0),
		waitFlag(false),
		rememberYForSlope(0.0),
		rememberDeltaForSlope(0.0),
		isSlope(false),
		isSlopeUp(false),
		isShooted(false),
		radderMode(RadderMode::NONE),
		detection(RectF(PLAYER_STAND_POS.x, PLAYER_STAND_POS.y, PLAYER_DETEC_W, PLAYER_DETEC_H)),// x軸をずらす
		attackNumbers({ 0, 0, 0, 0 }),
		bulletName(BulletName::NONE)
{
	this->allImage = Texture(U"image/LaraCroft.png");
	this->pos = Vec2(PLAYER_STAND_POS.x, PLAYER_STAND_POS.y);
	this->hp = PLAYER_HP;
	this->actionState = CharaActionState::WAIT;
	JSONReader imageJson(U"ini/playerImage.json");
	this->spriteImageMetaDataMap = SpriteUtil::GetPlayerSpriteImageMetaDataMap(imageJson);
}

/// <summary>
/// プレイヤーの初期化処理です
/// </summary>
void Player::Init(Font font)
{
	OnDamageOver();
	this->deltaTime = Scene::DeltaTime();
	this->delta = MOVE_STANDARD_X * deltaTime;
	InitDetection();
	waitCount = waitFlag ? waitCount + 1 : 0;
	this->font = font;
}

/// <summary>
/// 被ダメ硬直後の処理です
/// </summary>
void Player::OnDamageOver()
{
	if (waitSw.isRunning()) {
		if (!isActive && waitSw.sF() >= PLAYER_ONDAMEGE_SPRITE_WAIT) {
			isActive = true;
			imageNumber = 0;
			actionState = CharaActionState::WAIT;
		}
		else if (isInvisible && waitSw.sF() >= PLAYER_INVISIBLE_TIME) {
			isInvisible = false;
			waitSw.pause();
		}
		KnockBack();
	}
}

/// <summary>
/// 被ダメ時のノックバック処理です
/// </summary>
void Player::KnockBack()
{
	if (CharaActionState::ON_DAMAGE_INVISIBLE == actionState) {
		MoveX((isRightHit ? -delta : delta) * PLAYER_SQUEEZE_A);
	}
}

/// <summary>
/// プレイヤーキャラの当たり判定を初期化します
/// </summary>
void Player::InitDetection()
{
	double x = MapScreenHelper::IsMoveCameraX(pos.x) ? PLAYER_STAND_POS.x : pos.x;
	//TODO:Y軸は要確認
	double y = MapScreenHelper::IsMoveCameraY(pos.y) ? PLAYER_STAND_POS.y : pos.y;
	RectF playerRect(x, y, PLAYER_DETEC_W, PLAYER_DETEC_H); // x軸をずらす
	detection = playerRect;
}

/// <summary>
/// プレイヤーのX軸を移動します。
/// </summary>
/// <param name="moveAmt">移動量</param>
void Player::MoveX(double moveAmt)
{
	pos.x = pos.x + moveAmt;
	detection.x = MapScreenHelper::IsMoveCameraX(pos.x)
		? PLAYER_STAND_POS.x
		: detection.x + moveAmt;
}

void Player::MoveY(double moveAmt)
{
	pos.y = pos.y + moveAmt;
	detection.y = MapScreenHelper::IsMoveCameraY(pos.y)
		// （こういうことをする理由）
		// カメラを動かす→マップを動かすので当たり判定を
		// 固定しないといけないから
		// 反対にカメラを固定するときはキャラを動かすので
		// 当たり判定を動かす
		? PLAYER_STAND_POS.y 
		: detection.y + moveAmt;
}
/// <summary>
/// プレイヤーのX軸を変更します。
/// </summary>
/// <param name="replaceXPos">変更位置</param>
void Player::ReplaceX(double replaceXPos)
{
	pos.x = replaceXPos;
	detection.x = MapScreenHelper::IsMoveCameraX(replaceXPos)
			? PLAYER_STAND_POS.x
			: replaceXPos;
}

void Player::ReplaceY(double replaceYPos)
{
	pos.y = replaceYPos;
	detection.y = MapScreenHelper::IsMoveCameraY(replaceYPos)
		? PLAYER_STAND_POS.y
		: replaceYPos;
}

void Player::ReplacePos(Vec2 replacePos)
{
	pos = replacePos;
}

void Player::OnDamage(int damage, bool isRightHit)
{
	if (isInvisible) {
		return;
	}
	hp -= damage;
	//TODO: SE鳴らす
	waitSw.restart();
	if (hp <= 0) {
		actionState = CharaActionState::DOWN;
	}
	else {
		actionState = CharaActionState::ON_DAMAGE_INVISIBLE;
	}
	isActive = false;
	isInvisible = true;
	this->isRightHit = isRightHit;
}

Vec2 Player::GetDetectionPos(HitBoxDetection hitBoxDetection)
{
	switch (hitBoxDetection) {
	case HitBoxDetection::TOP_BEGIN:
		return detection.top().begin;
	case HitBoxDetection::BOTTOM_BEGIN:
		return detection.bottom().begin;
	case HitBoxDetection::BOTTOM_END:
		return detection.bottom().end;
	}
}

Vec2 Player::GetFootPos()
{
	Vec2 topBegin = detection.top().begin;
	Vec2 bottomBegin = detection.bottom().begin;
	Vec2 bottomEnd = detection.bottom().end;
	// 一点情報が必要-> 戻り値ありのメンバ関数にする
	double centerX = (bottomEnd.x + bottomBegin.x) / 2;
	Vec2 centerBottomBegin = Vec2(centerX, topBegin.y);
	Vec2 vertical = Vec2(centerBottomBegin.x, bottomEnd.y + 50);
	return vertical;
}

void Player::Debug(Font font)
{
	Vec2 topBegin = GetDetectionPos(HitBoxDetection::TOP_BEGIN);
	Vec2 bottomBegin = GetDetectionPos(HitBoxDetection::BOTTOM_BEGIN);
	Vec2 bottomEnd = GetDetectionPos(HitBoxDetection::BOTTOM_END);
	// 一点情報が必要-> 戻り値ありのメンバ関数にする
	double centerX = (bottomEnd.x + bottomBegin.x) / 2;
	Vec2 centerBottomBegin = Vec2(centerX, topBegin.y);
	Vec2 vertical = GetFootPos();

	font(U"Player").draw(0, 0);
	font(U"TopX:", topBegin.x).draw(0, 20);
	font(U"TopY:", topBegin.y).draw(0, 40);
	font(U"FootX:", bottomBegin.x).draw(0, 60);
	font(U"FootY:", bottomBegin.y).draw(0, 80);
	Line(bottomBegin, bottomEnd).draw(Palette::Red); // 横線
	Line(centerBottomBegin, vertical).draw(Palette::Red); // 縦線
}

void Player::DrawDetection() {
	detection.draw(ColorF(1.0, 1.0, 1.0, 0.2));
}

/// <summary>
/// 当たり判定をずらします
/// </summary>
/// <param name="diffPosX">位置Xに補正する数値</param>
/// <param name="diffPosY">位置Yに補正する数値</param>
/// <param name="w">変更後の幅</param>
/// <param name="h">変更後の高さ</param>
void Player::UpdateDetection(double diffPosX, double diffPosY, double w, double h) {
	RectF playerRect(PLAYER_STAND_POS.x + diffPosX, PLAYER_STAND_POS.y + diffPosY, w, h); // x軸をずらす
	detection = playerRect;
}
