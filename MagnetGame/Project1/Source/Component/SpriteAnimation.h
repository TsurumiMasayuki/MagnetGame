#pragma once
#include <string>
#include "Math\RectF.h"
#include "Math\Vec2.h"

class Timer;

//2D�X�v���C�g�p�A�j���[�V�����N���X
class SpriteAnimation
{
public:
	//�R���X�g���N�^
	SpriteAnimation(std::string textureName, float textureWidth, float textureHeight, float animTime, int animCount, int yPos = 0);
	~SpriteAnimation();

	//���Z�b�g
	void reset();
	//�X�V
	void update();

	//�e�N�X�`������Ԃ��܂��B
	std::string getTextureName();
	//�A�j���[�V�����̌��݂̐؂���ʒu��Ԃ��܂��B
	RectF getAnimRect();
	//Pivot��Ԃ��܂��B
	Vec2 getPivot();

private:
	std::string m_TextureName;	//�摜�̖��O

	Timer* m_pTimer;		//�摜�؂�ւ��Ԋu�p�^�C�}�[

	int m_XPos;				//�t���[����̌��݈ʒu(��)
	int m_YPos;				//�t���[����̌��݈ʒu(�c)

	int m_AnimCount;		//�t���[����

	float m_PivotX;			//�s�{�b�g
	float m_PivotY;			//�s�{�b�g

	float m_CellWidth;		//�؂���T�C�Y(��)
	float m_CellHeight;		//�؂���T�C�Y(�c)
	float m_TextureWidth;	//�摜�T�C�Y(��)
	float m_TextureHeight;	//�摜�T�C�Y(�c)
};