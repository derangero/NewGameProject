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
	Vec2 imagePos;
	Circle circleHitBox;
	RectF hitBox;
	RectF scoutingRange;
	double scoutingMagnification;
	int imageNumber;
	double moveAmt;
	double velocity; // 1.0���(�v���C���[�Ɠ������x)�ł��B
	Vec2 playerPos; // �v���C���[�L�����Ƒ��ΓI�Ȉʒu�v�Z���������Ƃ��ɂ���̂�
	RectF playerHitBox;
	EnemyAnimeType animeType;
	EnemyAnimeType beforeAnimeType;
	/** ��_����̓���ł�*/
	AfterOnDamage afterOnDamage;
public:
	Enemy();
	void Init(Font font) override;
	static void InitEnemies(Array<Enemy>& _enemies, Vec2 playerPos, RectF playerHitBox, Font font);
	static void InitEnemy(Enemy& enemy, Vec2 playerPos, RectF playerHitBox, Font font);
	void EnemyAction(Array<Bullet>& bullets, Font font);
	void OnDamage(int damage, bool isRightHit) override;
	void State();
	void Move();
	void Attack(Array<Bullet>& bullets);
	bool HasDetectedPlayer();
	void TernIfNeeded();
	void MoveAction();
	void MoveX(double moveAmt) override;
	void MoveY(double moveAmt) override;
	void UpdateHitBox();
	static void UpdateHitBox(Enemy& enemy, Vec2 playerPos);
	static void UpdateHitBox(bool _isExists, CharaActionState _actionState, RectF& _hitBox, RectF& _scoutingRange,
		std::unordered_map<int, SpriteImageMetaData> spriteImageMetaDataMap,
		Vec2 _pos, Vec2 _playerPos, EnemyAnimeType _animeType, int _imageNumber, int _scoutingMagnification,
		bool _rightwardFlag, String _name);
};