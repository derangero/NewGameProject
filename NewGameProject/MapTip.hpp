#pragma once
# include <Siv3D.hpp>
# include "EnumManager.hpp"

class MapCreator;
/// <summary>
/// �}�b�v�`�b�v�N���X�ł�
/// </summary>
class MapTip
{
public:
	/* ID */
	long id;
	bool isExists;
	bool falling;
	/* �ړ����� */
	TipMovingBy tipMovingBy;
	/* �}�b�v�̃^�C�v */
	MapType mapType;
	/* �}�b�v�ԍ� */
	int mapNumber;
	/* �ǂƂ��Ăӂ�܂��� */
	bool blockBehave;
	/* �`�b�v�ɐG�ꂽ���ǂ��� */
	bool touched;
	/* �`�b�v�̈ʒu */
	Point tip;
	Vec2 mapGrid;
	Texture mapTipTexture;
	/* �����蔻�� */
	RectF collision;
	/* �ړ��������� */
	Vec2 movedDistance;
public:
	MapTip();
	static void DrawMapTipTextures(Array<MapTip> mapTips, Texture tipTexture, Vec2& screenOriginPos, Font font);
	static Quad GetQuadForLeftSlope(Vec2 mapPos);
	void MoveX(double deltaX);
	void MoveY(double deltaY);
};
