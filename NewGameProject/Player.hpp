#pragma once
# include "Character.hpp"
# include "MapScreenHelper.hpp"
# include "SpriteImageMetaData.hpp"
# include "SpriteUtil.hpp"

/// <summary>
/// �v���C���[�N���X�ł�
/// </summary>
class Player : public Character
{
public:
	/* �Q�[���N���A�̃t���O */
	bool gameFinished;
	/* �擾�����R�C�� */
	int coinCount;
	/* �W�����v���̃t���[�����J�E���g���邽�߂̕ϐ� */
	int jumpFlameCount;
	/* ����n�t���O */
	bool walkFlag;
	bool crouchFlag;
	bool jumpFlag;
	bool dashFlag;
	/* �ҋ@�t���O(�R�}���h���������Ȃ�) */
	bool waitFlag;
	/** �ҋ@�p�̃J�E���g*/
	int waitCount;
	/* �_�b�V�����̈ꎞ�ۑ��p */
	double tempXBeforDash;
	/* �U���P���̃X�v���C�g�ԍ� */
	int attack1Number;
	/* �A�j���[�V�����ԍ��Ǘ��p�̓��I�z�� */
	Array<int> attackNumbers;
	/* �Z���W�����v���̈ʒu�z��Ǘ��p�̃C���f�b�N�X */
	int shortJumpIndex;
	double rememberYForSlope;
	double rememberDeltaForSlope;
	bool isSlope;
	bool isSlopeUp;
	bool isShooted;
	/** �n�V�S���[�h */
	RadderMode radderMode;
	/** �ˌ����[�h */
	BulletMode bulletMode;
	/** �ˌ����Ă���o���b�g�� */
	BulletName bulletName;
	Array<MapType> touchedLeftObjects;
	Array<MapType> touchedRightObjects;
	Array<MapType> touchedTopObjects;
	Array<MapType> touchedBottomObjects;
	/* �W�����v�{�^����r���Řb�������̍��W�Ǘ����X�g */
	Array<double> shortJumpYList;
public:
	Player();
	void OnDamageOver();
	void Init(Font font) override;
	void KnockBack() override;
	void MoveX(double moveAmt) override;
	void MoveY(double moveAmt) override;
	void OnDamage(int damage, bool isRightHit) override;
	void DrawDetection();
	void UpdateDetection(double diffPosX, double diffPosY, double w, double h);
	void InitDetection();
	void ReplaceX(double replaceAmt);
	void ReplaceY(double replaceAmt);
	void ReplacePos(Vec2 replacePos);
	Vec2 GetDetectionPos(HitBoxDetection detection);
	Vec2 GetFootPos();
	bool IsFallOff();
	bool GetCoin(MapTip &mapTip);
	void Debug(Font font);
};