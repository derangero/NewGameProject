#pragma once
#include "Siv3D.hpp"
#include "EnumManager.hpp"

class Object
{
public:
	/* ���݃t���O */
	bool isExists;
	/* ���x */
	double velocity;
	/* �ʒu */
	Vec2 pos;
	/* �����蔻�� */
	RectF hitBox;
	/* �i�s���� */
	Direction direction;
	/* �ėp�X�g�b�v�E�H�b�` */
	Stopwatch bulletSw;
	/* �摜(�X�v���C�g�p) */
	Texture spriteImage;
	/* �摜�ԍ� */
	int imageNumber;
	/* �摜 */
	TextureRegion image;
public:
	Object();
	void ClearPos();
	virtual ~Object();
};