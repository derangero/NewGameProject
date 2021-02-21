#pragma once
#include <Siv3D.hpp>

// �}�b�v�`�b�v�̉摜�����ɓW�J����Ă��鐔
constexpr auto MAP_IMAGE_WIDTH_MAX = 16;
// �}�b�v�`�b�v�̏c���T�C�Y
constexpr auto MAP_IMAGE_SQUARE_SIZE = 16;

// �W�����v��
// �X�v���C�g�摜��Y���W�w��(���_)
constexpr auto PLAYER_JUMP_SPRITE_Y = 385;
// �摜�T�C�Y
constexpr auto PLAYER_JUMP_SPRITE_SIZE = Vec2(46, 47);
// �X�v���C�g�؂�ւ�����
constexpr auto PLAYER_JUMP_SPRITE_CHANGE = 0.1;
// �㏸���̍ő�摜�ԍ�
constexpr auto PLAYER_JUMP_UP_MAX_IMAGE_NUMBER = 2;

// �_�b�V����
constexpr auto SPRITE_DASH_NUMBER = 4;
// �X�v���C�g�摜�̍��W�w��
constexpr auto PLAYER_DASH_SPRITE_POS = Vec2(263, 318);
// �摜�T�C�Y
constexpr auto PLAYER_DASH_SPRITE_SIZE = Vec2(52, 42);

// ������
// �X�v���C�g�摜��Y���W�w��(���_)
constexpr auto PLAYER_RUN_SPRITE_Y = 265;
// �摜�T�C�Y
constexpr auto PLAYER_RUN_SPRITE_SIZE = Vec2(63.75, 47);
// �X�v���C�g�؂�ւ�����
constexpr auto PLAYER_RUN_SPRITE_CHANGE = 0.05;

// ������
// �X�v���C�g�摜��Y���W�w��(���_)
constexpr auto PLAYER_STAND_SPRITE_Y = 175;
// �摜�T�C�Y
constexpr auto PLAYER_STAND_SPRITE_SIZE = Vec2(50, 55);
// �X�v���C�g�؂�ւ�����
constexpr auto PLAYER_STAND_SPRITE_CHANGE = 0.4;

// ���Ⴊ�ݎ�
constexpr auto CROUCH_MAX_IMAGE_NUMBER = 4;
// �X�v���C�g�摜��Y���W�w��(���_)
constexpr auto PLAYER_CROUCH_SPRITE_X = 88;
// �X�v���C�g�摜��Y���W�w��(���_)
constexpr auto PLAYER_CROUCH_SPRITE_Y = 456;
// �摜�T�C�Y
constexpr auto PLAYER_CROUCH_SPRITE_SIZE = Vec2(44, 48);
// �X�v���C�g�؂�ւ�����
constexpr auto PLAYER_CROUCH_SPRITE_CHANGE = 0.03;

// ��q���ݎ�
// �X�v���C�g�摜��Y���W�w��(���_)
constexpr auto PLAYER_GRAB_LADDER_SPRITE_Y = 1134;
// �摜�T�C�Y
constexpr auto PLAYER_GRAB_LADDER_SPRITE_SIZE = Vec2(21, 48);

// ���[�v�ˌ���
// �X�v���C�g�摜��Y���W�w��(���_)
constexpr auto BULLET_WARP_SPRITE_Y = 788;
// �摜�T�C�Y
constexpr auto BULLET_WARP_SPRITE_SIZE = Vec2(56, 54);
// �X�v���C�g�؂�ւ�����
constexpr auto BULLET_WARP_SPRITE_CHANGE = 0.03;
// �E�F�C�g�^�C��
constexpr auto BULLET_WARP_SPRITE_WAIT = 1.0;
// ���ˎ��̃X�v���C�g�摜
constexpr auto BULLET_WARP_FLASH_SPRITE_NUMBER = 2;
// �ő�X�v���C�g�摜
constexpr auto BULLET_WARP_MAX_SPRITE_NUMBER = 4;

// �U���P��
// �X�v���C�g�摜��Y���W�w��(���_)
constexpr auto ATTACK1_SPRITE_Y = 788;
// �摜�T�C�Y
constexpr auto ATTACK1_SPRITE_SIZE = Vec2(56, 54);
// �X�v���C�g�؂�ւ�����
constexpr auto ATTACK1_SPRITE_CHANGE = 0.03;
// �E�F�C�g�^�C��
constexpr auto ATTACK1_SPRITE_WAIT = 1.0;
// ���ˎ��̃X�v���C�g�摜
constexpr auto ATTACK1_FLASH_SPRITE_NUMBER = 2;
// �ő�X�v���C�g�摜
constexpr auto ATTACK1_MAX_SPRITE_NUMBER = 4;

// �U���Q��
// �X�v���C�g�摜��Y���W�w��(���_)
constexpr auto BULLET_ATTACK2_SPRITE_Y = 877;
// �摜�T�C�Y
constexpr auto BULLET_ATTACK2_SPRITE_SIZE = Vec2(49, 50);
// �C���p�̉摜���W
static Array<Vec2> BULLET_ATTACK2_FIX_SPRITE_VEC2S = {
	Vec2(0, 0), Vec2(0, 0), Vec2(8, 0), Vec2(8, 0), Vec2(8, 0), Vec2(8, 0), Vec2(0, 0)
};
// �X�v���C�g�؂�ւ�����
constexpr auto ATTACK2_SPRITE_CHANGE = 0.1;
// �E�F�C�g�^�C��
constexpr auto ATTACK2_SPRITE_WAIT = 4.0;
// �ő�X�v���C�g�摜
constexpr auto BULLET_ATTACK2_MAX_SPRITE_NUMBER = 6;

// �U��3��
// �X�v���C�g�摜��Y���W�w��(���_)
constexpr auto BULLET_ATTACK3_SPRITE_Y = 963;
// �摜�T�C�Y
constexpr auto BULLET_ATTACK3_SPRITE_SIZE = Vec2(48, 49);
// �ő�X�v���C�g�摜
constexpr auto BULLET_ATTACK3_MAX_SPRITE_NUMBER = 11;
// �C���p�̉摜�T�C�Y
static Array<Vec2> BULLET_ATTACK3_FIX_SPRITE_VEC2S = {
	Vec2(0, 0), Vec2(0, 0), Vec2(1, 0), Vec2(1, 0), Vec2(4, 0), Vec2(4, 0), Vec2(7, 0),
	Vec2(9, 0), Vec2(9, 0), Vec2(1, 0), Vec2(1, 0), Vec2(0, 0),
};
// �N�[���^�C��
constexpr auto ATTACK3_SPRITE_COOL = 3.0;

// ��_���[�W��
// �X�v���C�g�摜��Y���W�w��(���_)
constexpr auto PLAYER_ONDAMEGE_SPRITE_Y = 633;
// �摜�T�C�Y
constexpr auto PLAYER_ONDAMEGE_SPRITE_SIZE = Vec2(40, 53);
// �X�v���C�g�؂�ւ�����
constexpr auto PLAYER_ONDAMEGE_SPRITE_CHANGE = 0.02;
// ��_������
constexpr auto PLAYER_ONDAMEGE_SPRITE_WAIT = 1.5;
// ���G����
constexpr auto PLAYER_INVISIBLE_TIME = 4.0;
// �m�b�N�o�b�N���A�̂�����X�s�[�h�̔{��
constexpr auto PLAYER_SQUEEZE_A = 0.1;
// �ő�X�v���C�g�摜
constexpr auto PLAYER_ONDAMEGE_MAX_SPRITE_NUMBER = 3;

// �_�E����
// �C���p�̉摜�T�C�Y
static Array<Vec2> PLAYER_DOWN_SPRITE_FIX_VEC2_ARRAY = {
	Vec2(0, 15), Vec2(0, 7), Vec2(0, 7), Vec2(0, 7), Vec2(0, 0),
	Vec2(0, 0), Vec2(0, 0)
};
// �X�v���C�g�؂�ւ����x��x������{��
constexpr auto PLAYER_DOWN_SLOW_FOLD = 3.0;

// �v���C���[��HP
constexpr auto PLAYER_HP = 3;
// �v���C���[�̂Ђ�HP
constexpr auto PLAYER_DANGER_HP = 2;
// �v���C���[�̈ʒu(X)
constexpr auto PLAYER_STAND_POS_X = 400;
// �v���C���[�̈ʒu(Y)
constexpr auto PLAYER_STAND_POS_Y = 480;
// �v���C���[�̒��S�ƂȂ���W
constexpr auto PLAYER_STAND_POS = Vec2(PLAYER_STAND_POS_X, PLAYER_STAND_POS_Y);
// �J�����𓮂����Ȃ��(�E���ő�... 1200)
constexpr auto PLAYER_RIGHT_END_POS = Vec2(880, PLAYER_STAND_POS_Y);

// �v���C���[�̓����蔻��(����)
constexpr auto PLAYER_DETEC_H = 54.1;
// �v���C���[�̓����蔻��(��)
constexpr auto PLAYER_DETEC_W = 25;
// STAND���̉摜�ʒu�␳(X)
constexpr auto FIXED_STAND_RIGHT_X = -15;
constexpr auto FIXED_STAND_LEFT_X = -10;

// �摜�\���̕␳
// ���Ⴊ��
static Array<Vec2> PLAYER_CROUCH_SPRITE_FIX_VEC2_ARRAY = {
	Vec2(0, 0), Vec2(0, -10), Vec2(0, -7), Vec2(0, -12), Vec2(0, -14)
};
// ����
constexpr auto IMAGE_WALK_POS = Vec2(-18, 8);
// �W�����v
constexpr auto IMAGE_JUMP_LEFT_POS = Vec2(-20, 0);
constexpr auto IMAGE_JUMP_RIGHT_POS = Vec2(-3, 0);

// �v���C���[�̂��Ⴊ�ݎ��̓����蔻��(����)
constexpr auto PLAYER_CROUCH_DETEC_H = 30.1;
// �����蔻��̕␳�@���摜�������������ėL���ɂ���
constexpr auto PLAYER_FIXED_CROUCH_H = 24;

// �v���C���[�̃W�����v�̍���
constexpr int PLAYER_JUMP_HEIGHT = 110;
// �W�����v���̂䂪�݁i�T�C���J�[�u�j
constexpr double JUMP_DESTORTION = 1.5;
// �W�����v���̑��t���[����
constexpr int FLAME_BY_JUMP = 40;
// �W�����v���̗����J�n���_�̃t���[���J�E���g(���)
constexpr int FLAME_BY_FALING = 16;
// �W�����v���W���X�g�̑�̒��_������̃C���f�b�N�X
constexpr int ABOUT_TOP_JUMP_Y_INDEX = 11;
// Y���ړ����̌Œ�l
constexpr int MOVE_STANDARD_X = 200;
// �_�b�V���̋���
constexpr int DASH_DIST = 100;
// �_�b�V�����̂䂪��(cf.�T�C���J�[�u)
constexpr double DASH_DISTORTION = 0.5;
// �_�b�V�����̏c���V
constexpr double DASH_HEIGHT = 20.0;
// �_�b�V���̌v�Z�̂��߂̃�
constexpr double DASH_PI = 125_deg;
// �_�b�V���{�^�����������Ƃ��̉����{��
constexpr double DASH_ACCELERATION = 1.5;
// �~�����̉摜�ԍ�(0����)
constexpr int FALL_ANIME_NUMBER = 6;
// �}�b�v�̑��΃p�X
constexpr auto MAP_XML_PATH = U"map/test4.tmx";
// �X�N���[���T�C�Y�i�}�b�v�̍ő�T�C�Y�j
constexpr auto MAX_SCREEN_SIZE = Vec2(1920.0, 1280.0);
// �J�����̃|�W�V���� +16�͍��[�̍�������Ȃ��悤��
constexpr auto CAMERA_POS = Vec2(
	MAX_SCREEN_SIZE.x / 4.0 - 80 + 16, MAX_SCREEN_SIZE.y / 2.0 * 1.5 + 20);
// ������
constexpr auto FALL_AMT = 7;
// �W�����v���̎��Ԍo�ߒl
constexpr auto JUMP_BASE_TAME = 0.07;
// �W�����v�������n�܂�t���[���J�E���g
constexpr auto FALL_FLAME_COUNT = 20;
// �_�b�V���̊Ԋu����
constexpr auto DASH_WAIT_TIME = 0.4;

// ���C���[�o���b�g
// ���x
constexpr auto WIRE_BULLET_VELOCITY = 400.0;
// �˒�����
constexpr auto WIRE_BULLET_RANGE = 300.0;
// ���e���v���C���[�̈ړ����x
constexpr auto WIRE_BULLET_MOVE_SPEED = 10;

// �U���P�o���b�g
// ���x
constexpr auto ATTACK1_BULLET_VELOCITY = 450.0;
// �˒�����
constexpr auto ATTACK1_BULLET_RANGE = 500.0;

// �U��3�o���b�g�̊J�n�摜�ԍ�
constexpr auto SHOOT_ATTACK_3_START_IMAGE_NUMBET = 12;


// ���܂��Ȃ��n(FIXED:�������͂����肳���邱��)
// �I�u�W�F�N�g��Y�����}�C�i�X����B�i���̂�16px���ɂ���Ă���j
constexpr auto OBJECT_FIXED_Y = 16.0;

// �G�ڐG���̃_���[�W
constexpr auto ENEMY_HITBOX_DAMAGE = 1;

// �G�q�b�g�{�b�N�X�̃T�C�Y�����p
constexpr auto RESIZED_ENEMY_HITBOXES = Vec2(5, 5);

// �G�_�E�����̃A�j���[�V������������
constexpr auto ENEMY_DOWN_REMAINNING_TIME = 1.0;

constexpr auto OBJ_VELOCITY = 5.0;