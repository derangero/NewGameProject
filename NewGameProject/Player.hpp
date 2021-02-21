#pragma once
# include "Character.hpp"
# include "MapScreenHelper.hpp"
# include "SpriteImageMetaData.hpp"
# include "SpriteUtil.hpp"

/// <summary>
/// プレイヤークラスです
/// </summary>
class Player : public Character
{
public:
	/* ゲームクリアのフラグ */
	bool gameFinished;
	/* 取得したコイン */
	int coinCount;
	/* ジャンプ時のフレームをカウントするための変数 */
	int jumpFlameCount;
	/* 動作系フラグ */
	bool walkFlag;
	bool crouchFlag;
	bool jumpFlag;
	bool dashFlag;
	/* 待機フラグ(コマンドをうけつけない) */
	bool waitFlag;
	/** 待機用のカウント*/
	int waitCount;
	/* ダッシュ時の一時保存用 */
	double tempXBeforDash;
	/* 攻撃１時のスプライト番号 */
	int attack1Number;
	/* アニメーション番号管理用の動的配列 */
	Array<int> attackNumbers;
	/* 短いジャンプ時の位置配列管理用のインデックス */
	int shortJumpIndex;
	double rememberYForSlope;
	double rememberDeltaForSlope;
	bool isSlope;
	bool isSlopeUp;
	bool isShooted;
	/** ハシゴモード */
	RadderMode radderMode;
	/** 射撃モード */
	BulletMode bulletMode;
	/** 射撃しているバレット名 */
	BulletName bulletName;
	Array<MapType> touchedLeftObjects;
	Array<MapType> touchedRightObjects;
	Array<MapType> touchedTopObjects;
	Array<MapType> touchedBottomObjects;
	/* ジャンプボタンを途中で話した時の座標管理リスト */
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