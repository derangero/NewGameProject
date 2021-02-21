#pragma once
#include "Siv3D.hpp"
#include "MapTip.hpp"
#include "Property.hpp"
#include "MapProperty.hpp"
#include "EnumManager.hpp"

/// <summary>
/// �I�u�W�F�N�g�`�b�v�̃N���X
/// </summary>
class ObjectTip : public MapTip
{
public:
	double w;
	double h;
	double deltaAmt;
	// �I�u�W�F�N�g�̈ړ�����
	double moveAmt;
	// �I�u�W�F�N�g�����������ɂȂ鋗��
	double turningMoveAmt;
	// �ӂꂽ���̃_���[�W
	int damage;
	// (�G)�ҋ@����
	double waitTime;
	Direction direction;
	EnemyType enemyType;
	Polygon objectDetection;
	Quad quadDetection;
	Triangle triDetection;
public:
	ObjectTip();
	/// <summary>
	/// �G�L�����̃I�u�W�F�N�g��ݒ�
	/// </summary>
	/// <param name="enemyType">�G�L�����̃^�C�v</param>
	/// <param name="tip">�ʒu</param>
	/// <param name="elem">XMLElement�I�u�W�F�N�g</param>
	ObjectTip(EnemyType enemyType, Point tip, XMLElement &elem);
	/// <summary>
	/// �}�b�v�`�b�v�̃I�u�W�F�N�g��ݒ�
	/// </summary>
	/// <param name="tip">�ʒu</param>
	/// <param name="elem">XMLElement�I�u�W�F�N�g</param>
	ObjectTip(Point tip, XMLElement &elem);
	ObjectTip(int mapNumber, double width, double height, Point tip, XMLElement &elem);
	ObjectTip(MapType mapType, int mapNumber, double width, double height, Point tip, XMLElement &elem,
		double deltaAmt, double turningMoveAmt, Direction direction, int damage, double waitTime);
	static void SetObjectTip(Array<ObjectTip> objectMapTips, Texture mapTip1, Vec2& screenOriginPosition);
	RectF CreateCollision();
	Vec2 GetObjectTipXY(XMLElement& elem);
};