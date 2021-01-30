#pragma once
#include "Property.hpp"
#include "EnumManager.hpp"
#include "Bullet.hpp"

class Character
{
public:
	/** �摜 */
	Texture allImage;
	/* ���n�_ */
	double groundY;
	/* ���ړ��� */
	double delta;
	/* �����ړ��� */
	double deltaAmt;
	/* 1�t���[�����̌o�ߎ���(�b) */
	double deltaTime;
	/* ������ */
	int hp;
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
	/* �ʒu */
	Vec2 pos;
	/* �␳�O�̈ʒu */
	Vec2 beforePos;
	/* ������ */
	CharaActionState actionState;
	/* �U����� */
	CharaAttackState attackState;
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