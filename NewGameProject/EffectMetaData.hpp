#pragma once
# include <Siv3D.hpp>
class EffectMetaData
{
public:
    // ���O
    String name;
    // �X�v���C�g�̍ő剡����
    int maxXCount;
    // �X�v���C�g�̍ő�c����
    int maxYCount;
    // �󔒖���
    int blanckCount;
    // �Đ�����
    double effectingSf;
    /* �Đ��Ԋu�̎��� */
    double intervalSf;
    // ���[�v���邩�ǂ���
    bool loopFlag;
    // �G�t�F�N�g�̃X�v���C�g�摜
    Texture effectBase;
public:
	EffectMetaData();
	EffectMetaData(String name, Texture effectBase, Array<double> properties);
};