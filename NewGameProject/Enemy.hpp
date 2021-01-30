#pragma once
# include "Character.hpp"

class EnemyAnimeManager;
/// <summary>
/// 敵クラスです
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
	/** 速度です(1.0が基準(プレイヤーと同じ速度)です。) */
	double velocity;
	/** 追跡時の速度です */
	double chaseVelocity;
	Vec2 playerPos; // プレイヤーキャラと相対的な位置計算をしたいときにいるので
	RectF playerHitBox;
	EnemyAnimeType animeType;
	EnemyAnimeType beforeAnimeType;
	/** 被ダメ後の動作です*/
	AfterOnDamage afterOnDamage;
	/** 攻撃タイプ */
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