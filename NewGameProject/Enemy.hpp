#pragma once
# include "Character.hpp"
class EnemyAnimeManager;

class Enemy : public Character
{
public:
	/* 名称 */
	String name;
	/* タイプ */
	int type;
	/* 画像 */
	TextureRegion image;
	/* 当たり判定(円) */
	Circle circleHitBox;
	/* 索敵範囲の距離 */
	int scoutingRange;
	/* (近接攻撃)範囲の距離 */
	int closeScoutingRange;
	/* 索敵範囲 */
	RectF scoutingRangeArea;
	/* (近接攻撃)範囲 */
	RectF closeScoutingRangeArea;
	double moveAmt;
	/* 速度(1.0が基準(=プレイヤーと同じ速度)) */
	double velocity;
	/* 追跡時の速度 */
	double chaseVelocity;
	/* 地上の座標 */
	double ground;
	/* 地上の座標(保持用) */
	double beforeGround;
	/* ジャンプする確率 */
	double randomJumpChance;
	/* ジャンプ状態 */
	JumpMode jumpMode;
	Vec2 playerPos; // プレイヤーキャラと相対的な位置計算をしたいときにいるので
	RectF playerHitBox;
	EnemyAnimeType animeType;
	EnemyAnimeType beforeAnimeType;
	/** 被ダメ後の動作*/
	AfterOnDamage afterOnDamage;
	/** 攻撃タイプ */
	EnemyAttackType attackType;
public:
	// TODO:アルファベット順に並べる + 命名が最小になるように
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