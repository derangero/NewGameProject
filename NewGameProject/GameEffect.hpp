#pragma once
# include <Siv3D.hpp>
# include "EffectProperty.hpp"
# include "EffectMetaData.hpp"
class GameEffect
{
public:
	/* �G�t�F�N�g�̖��O */
	String name;
	/* �G�t�F�N�g��`�悷�邩 */
	bool drawFlag;
	/* �G�t�F�N�g�����[�v���邩 */
	bool loopFlag;
	/* �Đ����Ԃ��Ǘ����邽�߂̕ϐ� */
	double time;
	/* �Đ����� */
	double effectingSf;
	/* �Đ��Ԋu�̎��� */
	double intervalSf;
	/* �G�t�F�N�g�̃X�v���C�g */
	Texture effectBase;
	/* �`��ʒu */
	Vec2 pos;
	/* �G�t�F�N�g�̃X�v���C�g(1���Â������ă��X�g��) */
	Array<TextureRegion> effectTextures;
	/* �G�t�F�N�g�����ۂɕ`�悷�閇�� */
	int effectDrawSize;
	/* �ėp�X�g�b�v�E�H�b�` */
	Stopwatch sw;
public:
	GameEffect();
	GameEffect(EffectMetaData effectMetaData);
	void StartDraw(Vec2 pos);
	void Draw(Vec2 pos);
};