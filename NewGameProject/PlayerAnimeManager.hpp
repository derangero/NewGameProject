#pragma once
# include <Siv3D.hpp>
# include "Player.hpp"
# include "TimeManager.hpp"
# include "BulletManager.hpp"
# include "Afterimage.hpp"
# include "AnimationBean.hpp"

/// <summary>
/// プレイヤーのアクションに関するアニメーションクラスです
/// </summary>
class PlayerAnimeManager {
public:
	/* 歩いている時のスプライト番号 */
	int standNumber;
	/* 走っている時のスプライト番号 */
	int runNumber;
	/* ジャンプ時のスプライト番号 */
	int jumpNumber;
	/* しゃがみ時のスプライト番号 */
	int crouchNumber;
	TimeManager timeManager;
	PlayerAnimeManager();
	void Draw(Player& player, TimeManager& timeManager, Effect &effect);
	void Run(Player& player, TimeManager& timeManager);
	void Jump(Player& player, TimeManager& timeManager, Effect& _effect);
	void Dash(Player& player, TimeManager& timeManager);
	void Stand(Player& player, TimeManager& timeManager);
	void Crouch(Player& player, TimeManager& timeManager);
	void GrabLadder(Player& player, TimeManager& tManager);
	void BulletMotion(Player& player, TimeManager& timeManager);
	void BulletWarp(Player& player, TimeManager& timeManager);
	void BulletAttack2(Player& player, TimeManager& timeManager);
	void BulletAttack3(Player& player, TimeManager& timeManager);
	void OnDamage(Player& player, TimeManager& timeManager);
	bool DrawFallAnime(Player& player);
	void ChangeRunSprite(Player player, SpriteImageMetaData icData, TimeManager& timeManager);
	void ChangeJumpSprite(Player player, SpriteImageMetaData icData, TimeManager& timeManager);
	void ChangeStandSprite(Player player, SpriteImageMetaData icData, TimeManager& timeManager);
	void ChangeCrouchSprite(Player player, SpriteImageMetaData icData, TimeManager& timeManager);
	void ChangeAttack1Sprite(Player &player, AnimationBean& aniBean);
	void ChangeAttackNSprite(Player &player, AnimationBean& aniBean, int n);
	void DrawPlayerImage(Player player, TextureRegion playerImage, Vec2 leftFixed, Vec2 rightFixed);
	void DrawPlayerStandImage(Player player, TextureRegion playerImage);
	Vec2 GetMapPlayerPos(Player player);
	void DrawPlayerAfterImage(Player player, TextureRegion playerImage, TimeManager& timeManager, Effect& _effect);
	ColorF GetPlayerColor(Player player);
	void ChangeOnDamageSprite(Player& player, SpriteImageMetaData icData, TimeManager& timeManager);
	TextureRegion ExtractionImage(Player player, SpriteImageMetaData icData, int imageNumber);
};