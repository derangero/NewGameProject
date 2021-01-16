#pragma once
# include <Siv3D.hpp>

/// <summary>
/// �X�v���C�g�摜�̃��^����ێ�����N���X�ł��B
/// </summary>
class SpriteImageMetaData {
public:
	int maxImageNumber;
	double interval;
	Array<Vec2> vecs;
	Array<Size> sizes;
public:
	SpriteImageMetaData();
	SpriteImageMetaData(int maxImageNumber, double interval, Array<Vec2> vecs, Array<Size> sizes);
};