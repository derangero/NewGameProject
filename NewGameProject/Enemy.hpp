#pragma once
# include "Character.hpp"

class EnemyAnimeManager;
/// <summary>
/// �G�N���X�ł�
/// </summary>
class Enemy : public Character
{
public:
	String name;
	int type;
	TextureRegion image;
	RectF hitBox;
	Circle circleHitBox;
	int scoutingRange;
	int closeScoutingRange;
	RectF scoutingRangeArea;
	RectF closeScoutingRangeArea;
	int imageNumber;
	double moveAmt;
	/** ���x�ł�(1.0���(�v���C���[�Ɠ������x)�ł��B) */
	double velocity;
	/** �ǐՎ��̑��x�ł� */
	double chaseVelocity;
	Vec2 playerPos; // �v���C���[�L�����Ƒ��ΓI�Ȉʒu�v�Z���������Ƃ��ɂ���̂�
	RectF playerHitBox;
	EnemyAnimeType animeType;
	EnemyAnimeType beforeAnimeType;
	/** ��_����̓���ł�*/
	AfterOnDamage afterOnDamage;
	/** �U���^�C�v */
	EnemyAttackType attackType;
public:
	Enemy();
	void Init(Font font) override;
	void KnockBack() override;
	static void InitEnemies(Array<Enemy>& _enemies, Vec2 playerPos, RectF playerHitBox, Font font);
	static void InitEnemy(Enemy& enemy, Vec2 playerPos, RectF playerHitBox, Font font);
	void EnemyAction(Array<Bullet>& bullets, Font font);
	void OnDamage(int damage, bool isRightHit) override;
	void State();
	void Move();
	void Attack(Array<Bullet>& bullets);
	void LongRangeAttack(Array<Bullet>& bullets);
	void CloseRangeAttack();
	bool HasDetectedPlayer(RectF scouting);
	void TernIfNeeded();
	void MoveAction();
	void MoveX(double moveAmt) override;
	void MoveY(double moveAmt) override;
	CharaAttackState SelectAttackState();
	bool IsEndAttackMotion(SpriteImageMetaData metaData);
	void BeginAttack1();
	void EndAttack1(SpriteImageMetaData simData, Array<Bullet>& bullets);
	void UpdateHitBox();
	void UpdateHitBox(Enemy& enemy, Vec2 playerPos);
	void UpdateHitBox(bool _isExists, CharaActionState _actionState, RectF& _hitBox, RectF& _scoutingRangeArea,
		RectF& _closeScoutingRangeArea,
		std::unordered_map<int, SpriteImageMetaData> spriteImageMetaDataMap,
		Vec2 _pos, Vec2 _playerPos, EnemyAnimeType _animeType, int _imageNumber, int _scoutingRange, int _closeScoutingRange,
		bool _rightwardFlag, String _name);
	bool IsOutOfFrame(RectF _hitBox, Vec2 playerPos, Vec2 enemyPos);
};