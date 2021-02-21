#include "Player.hpp"

Player::Player() :
		gameFinished(false),
		shortJumpIndex(0),
		waitCount(0),
		tempXBeforDash(0.0),
		jumpFlameCount(0),
		walkFlag(false),
		crouchFlag(false),
		jumpFlag(false),
		dashFlag(false),
		attack1Number(0),
		waitFlag(false),
		rememberYForSlope(0.0),
		rememberDeltaForSlope(0.0),
		isSlope(false),
		isSlopeUp(false),
		isShooted(false),
		radderMode(RadderMode::NONE),
		attackNumbers({ 0, 0, 0, 0 })
{
	this->charaType = CharaType::PLAYER;
	this->jumpMode = JumpMode::UP;
	this->jumpFallFlag = false;
	this->afterDashFlag = false;
	this->wallTipTouching != MapTipTouching::NONE;
	this->objectTipTouching != MapTipTouching::NONE;
	this->topWallFlag = false;
	this->charaFallMode = CharaFallMode::NATURAL_FALL;
	this->topWallFlag2 = false;
	// x�������炷
	this->hitBox = RectF(PLAYER_STAND_POS.x, PLAYER_STAND_POS.y, PLAYER_DETEC_W, PLAYER_DETEC_H);
	this->jumpHeight = PLAYER_JUMP_HEIGHT;
	this->allImage = Texture(U"image/LaraCroft.png");
	this->pos = Vec2(PLAYER_STAND_POS.x, PLAYER_STAND_POS.y);
	this->hp = PLAYER_HP;
	this->actionState = CharaActionState::WAIT;
	JSONReader imageJson(U"ini/playerImage.json");
	this->spriteImageMetaDataMap = SpriteUtil::GetPlayerSpriteImageMetaDataMap(imageJson);
}

/// <summary>
/// �v���C���[�̏����������ł�
/// </summary>
void Player::Init(Font font)
{
	if (!isExists) {
		return;
	}
	this->deltaTime = Scene::DeltaTime();
	this->delta = MOVE_STANDARD_X * deltaTime;
	InitDetection();
	waitCount = waitFlag ? waitCount + 1 : 0;
	this->font = font;
	OnDamageOver();
}

/// <summary>
/// ��_���d����̏����ł�
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
	}
}

/// <summary>
/// ��_�����̃m�b�N�o�b�N�����ł�
/// </summary>
void Player::KnockBack()
{
	if (CharaActionState::ON_DAMAGE_INVISIBLE == actionState) {
		MoveX((isRightHit ? -delta : delta) * PLAYER_SQUEEZE_A);
	}
}

/// <summary>
/// �v���C���[�L�����̓����蔻������������܂�
/// </summary>
void Player::InitDetection()
{
	double x = MapScreenHelper::IsMoveCameraX(pos.x) ? PLAYER_STAND_POS.x : pos.x;
	//TODO:Y���͗v�m�F
	double y = MapScreenHelper::IsMoveCameraY(pos.y) ? PLAYER_STAND_POS.y : pos.y;
	if (!crouchFlag) {
		RectF playerRect(x, y, PLAYER_DETEC_W, PLAYER_DETEC_H); // x�������炷
		hitBox = playerRect;
	}
	else {
		RectF playerRect(x, y - 0, PLAYER_DETEC_W, PLAYER_CROUCH_DETEC_H); // x�������炷
		hitBox = playerRect;
	}
}

/// <summary>
/// �v���C���[��X�����ړ����܂��B
/// </summary>
/// <param name="moveAmt">�ړ���</param>
void Player::MoveX(double moveAmt)
{
	pos.x = pos.x + moveAmt;
	hitBox.x = MapScreenHelper::IsMoveCameraX(pos.x)
		? PLAYER_STAND_POS.x
		: hitBox.x + moveAmt;
}

void Player::MoveY(double moveAmt)
{
	pos.y = pos.y + moveAmt;
	hitBox.y = MapScreenHelper::IsMoveCameraY(pos.y)
		// �i�����������Ƃ����闝�R�j
		// �J�����𓮂������}�b�v�𓮂����̂œ����蔻���
		// �Œ肵�Ȃ��Ƃ����Ȃ�����
		// ���΂ɃJ�������Œ肷��Ƃ��̓L�����𓮂����̂�
		// �����蔻��𓮂���
		? PLAYER_STAND_POS.y 
		: hitBox.y + moveAmt;
}
/// <summary>
/// �v���C���[��X����ύX���܂��B
/// </summary>
/// <param name="replaceXPos">�ύX�ʒu</param>
void Player::ReplaceX(double replaceXPos)
{
	pos.x = replaceXPos;
	hitBox.x = MapScreenHelper::IsMoveCameraX(replaceXPos)
			? PLAYER_STAND_POS.x
			: replaceXPos;
}

void Player::ReplaceY(double replaceYPos)
{
	pos.y = replaceYPos;
	hitBox.y = MapScreenHelper::IsMoveCameraY(replaceYPos)
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
	damaged += damage;
	//TODO: SE�炷
	if (hp <= 0) {
		actionState = CharaActionState::DOWN;
		jumpFallFlag = false;
		charaFallMode = CharaFallMode::NONE;
		isExists = false;
		hitBox = Rect();
		SpriteImageMetaData& icData(spriteImageMetaDataMap[(int)PlayerAnimeType::DOWN]);
		imageNumber = icData.maxImageNumber; // �X�v���C�g���t���ŕ\������̂�
	}
	else {
		actionState = CharaActionState::ON_DAMAGE_INVISIBLE;
		isInvisible = true;
		dashFlag = false;
		crouchFlag = false;
		//TODO:�v����
		//bulletMode = BulletMode::NONE;
		//bulletName = bulletName::NONE;
		waitSw.restart();
	}
	isActive = false;
	this->isRightHit = isRightHit;
}

Vec2 Player::GetDetectionPos(HitBoxDetection hitBoxDetection)
{
	switch (hitBoxDetection) {
	case HitBoxDetection::TOP_BEGIN:
		return hitBox.top().begin;
	case HitBoxDetection::BOTTOM_BEGIN:
		return hitBox.bottom().begin;
	case HitBoxDetection::BOTTOM_END:
		return hitBox.bottom().end;
	}
}

Vec2 Player::GetFootPos()
{
	Vec2 topBegin = hitBox.top().begin;
	Vec2 bottomBegin = hitBox.bottom().begin;
	Vec2 bottomEnd = hitBox.bottom().end;
	// ��_��񂪕K�v-> �߂�l����̃����o�֐��ɂ���
	double centerX = (bottomEnd.x + bottomBegin.x) / 2;
	Vec2 centerBottomBegin = Vec2(centerX, topBegin.y);
	Vec2 vertical = Vec2(centerBottomBegin.x, bottomEnd.y + 50);
	return vertical;
}

bool Player::IsFallOff()
{
	return hitBox.top().begin.y > Scene::Size().y;
}

bool Player::GetCoin(MapTip &objectTip)
{
	if (objectTip.isExists && MapType::COIN == objectTip.mapType) {
		objectTip.isExists = false;
		objectTip.collision = RectF();
		coinCount += 1;
		return true;
		// TODO:�T�E���h
	}
	return false;
}

void Player::Debug(Font font)
{
	Vec2 topBegin = GetDetectionPos(HitBoxDetection::TOP_BEGIN);
	Vec2 bottomBegin = GetDetectionPos(HitBoxDetection::BOTTOM_BEGIN);
	Vec2 bottomEnd = GetDetectionPos(HitBoxDetection::BOTTOM_END);
	// ��_��񂪕K�v-> �߂�l����̃����o�֐��ɂ���
	double centerX = (bottomEnd.x + bottomBegin.x) / 2;
	Vec2 centerBottomBegin = Vec2(centerX, topBegin.y);
	Vec2 vertical = GetFootPos();

	font(U"Player").draw(0, 0);
	font(U"TopX:", topBegin.x).draw(0, 20);
	font(U"TopY:", topBegin.y).draw(0, 40);
	font(U"FootX:", bottomBegin.x).draw(0, 60);
	font(U"FootY:", bottomBegin.y).draw(0, 80);
	String CharaFallDisplay = U"NONE";
	if (CharaFallMode::NATURAL_FALL == charaFallMode) {
		CharaFallDisplay = U"NATURAL_FALL";
	}
	else if (CharaFallMode::BROW_UP_A == charaFallMode) {
		CharaFallDisplay = U"BROW_UP_A";
	}
	font(U"CharaFall:", CharaFallDisplay).draw(0, 100);
	font(U"time:", time).draw(0, 120);
	Line(bottomBegin, bottomEnd).draw(Palette::Red); // ����
	Line(centerBottomBegin, vertical).draw(Palette::Red); // �c��

	String dispActionState = U"NONE";
	if (CharaActionState::WAIT == actionState) {
		dispActionState = U"WAIT";
	}
	else if (CharaActionState::ATTACK == actionState) {
		dispActionState = U"ATTACK";
	}
	else if (CharaActionState::DOWN == actionState) {
		dispActionState = U"DOWN";
	}
	else if (CharaActionState::MOVE == actionState) {
		dispActionState = U"MOVE";
	}
	else if (CharaActionState::ON_DAMAGE == actionState) {
		dispActionState = U"ON_DAMAGE";
	}
	else if (CharaActionState::ON_DAMAGE_INVISIBLE == actionState) {
		dispActionState = U"ON_DAMAGE_INVISIBLE";
	}
	font(U"PlayerActionState:", dispActionState).draw(0, 300);
	font(U"PlayerImageNumber:", imageNumber).draw(0, 340);
}

void Player::DrawDetection() {
	hitBox.draw(ColorF(1.0, 1.0, 1.0, 0.2));
}

/// <summary>
/// �����蔻������炵�܂�
/// </summary>
/// <param name="diffPosX">�ʒuX�ɕ␳���鐔�l</param>
/// <param name="diffPosY">�ʒuY�ɕ␳���鐔�l</param>
/// <param name="w">�ύX��̕�</param>
/// <param name="h">�ύX��̍���</param>
void Player::UpdateDetection(double diffPosX, double diffPosY, double w, double h) {
	//RectF playerRect(detection.x + diffPosX, detection.y + diffPosY, w, h); // x�������炷
	//detection = playerRect;
}
