#pragma once
#include "Property.hpp"
#include "EnumManager.hpp"
#include "Bullet.hpp"

class Character
{
public:
	/** �摜 */
	Texture allImage;
	/* �����蔻�� */
	RectF hitBox;
	/* �����蔻��(1�t���[���O) */
	RectF beforeHitBox;
	/* ���n�_ */
	double ground;
	/* ���ړ��� */
	double delta;
	/* �����ړ��� */
	double deltaAmt;
	/* �������ɏ���Ă���Ƃ��̉��Z���ړ��� */
	double deltaAmtOnMovingFloor;
	/* 1�t���[�����̌o�ߎ���(�b) */
	double deltaTime;
	/* �W�����v�� */
	double jumpHeight;
	/* �W�����v���̏d�� */
	Vec2 gravity;
	/* ������ */
	int hp;
	/* �󂯂��_���[�W */
	int damaged;
	/* ���݃t���O */
	bool isExists;
	/* �E�����t���O */
	bool rightwardFlag;
	/** ����󂯕t���t���O */
	bool isActive;
	/** ���G�t���O */
	bool isInvisible;
	/** �U��1���݃t���O */
	bool isAttack1;
	/** �ėp�t���O */
	bool flag;
	/** �E���Ƀq�b�g������ */
	bool isRightHit;
	/** �U�����󂯂��� */
	bool isOnDamage;
	/* �W�����v�����t���O */
	bool jumpFallFlag;
	/* �������[�h */
	CharaFallMode charaFallMode;
	/* �W�����v���[�h */
	JumpMode jumpMode;
	/* �_�b�V����t���O */
	bool afterDashFlag;
	/* �ǂ̕����̕ǂɐG�ꂽ�� */
	MapTipTouching wallTipTouching;
	/* �ǂ̕����̃I�u�W�F�N�g�ɐG�ꂽ�� */
	MapTipTouching objectTipTouching;
	/* �G�ꂽ�`�b�v�̎�� */
	MapType touchedMapType;
	/* �G�ꂽ�`�b�v��ID */
	long touchedObjectId;
	bool topWallFlag;
	bool topWallFlag2;
	/* �ꎞ�I�ɕǔ��菈���𖳎� */
	bool ignoreWall;
	/* �L�����̎�� */
	CharaType charaType;
	/* ����ł��鏰�̎�� */
	OnFloorType onFloorType;
	/* �ʒu */
	Vec2 pos;
	/* �␳�O�̈ʒu */
	Vec2 beforePos;
	/* �z�u���W */
	Vec2 originPos;
	/* ������ */
	CharaActionState actionState;
	/* �U����� */
	CharaAttackState attackState;
	/* �A�[�}�[�N���X */
	ArmorClass armorClass;
	/* �ėp�X�g�b�v�E�H�b�` */
	Stopwatch sw;
	/* �N�[���^�C���p�̃X�g�b�v�E�H�b�` */
	Stopwatch waitSw;
	/* �U���p�X�g�b�v�E�H�b�`1 */
	Stopwatch attackSw1;
	/* �ėp�^�C���J�E���g */
	double time;
	/* �摜�ԍ� */
	int imageNumber;
	/* �t�H���g */
	Font font;
	/** �X�v���C�g�摜�̃��^�f�[�^�}�b�v */
	std::unordered_map<int, SpriteImageMetaData> spriteImageMetaDataMap;
public:
	Character();
	virtual void Init(Font font);
	virtual void Action(Array<Bullet>& bullets);
	virtual void OnDamage(int damage, bool rightHit);
	virtual void KnockBack();
	virtual bool IsInvisible();
	virtual void MoveX(double moveAmt);
	virtual void MoveY(double moveAmt);
	bool IsMovingRightInFrame(Vec2 playerPos);
	bool IsFixLeftInFrame(Vec2 playerPos);
};