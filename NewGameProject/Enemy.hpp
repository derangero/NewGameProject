#pragma once
# include "Character.hpp"
class EnemyAnimeManager;

class Enemy : public Character
{
public:
	/* ���� */
	String name;
	/* �^�C�v */
	int type;
	/* �摜 */
	TextureRegion image;
	/* �����蔻��(�~) */
	Circle circleHitBox;
	/* ���G�͈͂̋��� */
	int scoutingRange;
	/* (�ߐڍU��)�͈͂̋��� */
	int closeScoutingRange;
	/* ���G�͈� */
	RectF scoutingRangeArea;
	/* (�ߐڍU��)�͈� */
	RectF closeScoutingRangeArea;
	double moveAmt;
	/* ���x(1.0���(=�v���C���[�Ɠ������x)) */
	double velocity;
	/* �ǐՎ��̑��x */
	double chaseVelocity;
	/* �n��̍��W */
	double ground;
	/* �n��̍��W(�ێ��p) */
	double beforeGround;
	/* �W�����v����m�� */
	double randomJumpChance;
	/* �W�����v��� */
	JumpMode jumpMode;
	Vec2 playerPos; // �v���C���[�L�����Ƒ��ΓI�Ȉʒu�v�Z���������Ƃ��ɂ���̂�
	RectF playerHitBox;
	EnemyAnimeType animeType;
	EnemyAnimeType beforeAnimeType;
	/** ��_����̓���*/
	AfterOnDamage afterOnDamage;
	/** �U���^�C�v */
	EnemyAttackType attackType;
public:
	// TODO:�A���t�@�x�b�g���ɕ��ׂ� + �������ŏ��ɂȂ�悤��
	Enemy();
	void Attack(Array<Bullet>& bullets);
	void LongRangeAttack(Array<Bullet>& bullets);
	void CloseRangeAttack();
	void EndAttack1(SpriteImageMetaData simData, Array<Bullet>& bullets);
	void Init(Font font) override;
	static void InitEnemies(Array<Enemy>& _enemies, Vec2 playerPos, RectF playerHitBox, Font font);
	static void InitEnemy(Enemy& enemy, Vec2 playerPos, RectF playerHitBox, Font font);
	void ClearHitBox(Array<Bullet>& bullets);
	void KnockBack() override;
	void EnemyAction(Array<Bullet>& bullets, Font font);
	void OnDamage(int damage, bool isRightHit) override;
	void State();
	void Move();
	bool HasDetectedPlayer(RectF scouting);
	void TernIfNeeded();
	void MoveAction();
	void MoveX(double moveAmt) override;
	void MoveY(double moveAmt) override;
	CharaAttackState SelectAttackState();
	bool IsEndAttackMotion(SpriteImageMetaData metaData);
	void BeginAttack1();
	void UpdateHitBox();
	void UpdateHitBox(Enemy& enemy, Vec2 playerPos);
	void UpdateHitBox(bool _isExists, CharaActionState _actionState, RectF& _hitBox, RectF& _scoutingRangeArea,
		RectF& _closeScoutingRangeArea,
		std::unordered_map<int, SpriteImageMetaData> spriteImageMetaDataMap,
		Vec2 _pos, Vec2 _playerPos, EnemyAnimeType _animeType, int _imageNumber, int _scoutingRange, int _closeScoutingRange,
		bool _rightwardFlag, String _name);
	bool IsOutOfFrame(RectF _hitBox, Vec2 playerPos, Vec2 enemyPos);
	void ReplaceY(double replaceYPos);
	void ReplaceX(double replaceXPos);
};