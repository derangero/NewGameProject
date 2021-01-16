#pragma once
# include <Siv3D.hpp>
# include "Player.hpp"
# include "TimeManager.hpp"
# include "BulletManager.hpp"
# include "Afterimage.hpp"
# include "AnimationBean.hpp"

/// <summary>
/// �v���C���[�̃A�N�V�����Ɋւ���A�j���[�V�����N���X�ł�
/// </summary>
class PlayerAnimeManager {
public:
	/* �����Ă��鎞�̃X�v���C�g�ԍ� */
	int standNumber;
	/* �����Ă��鎞�̃X�v���C�g�ԍ� */
	int runNumber;
	/* �W�����v���̃X�v���C�g�ԍ� */
	int jumpNumber;
	/* ���Ⴊ�ݎ��̃X�v���C�g�ԍ� */
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