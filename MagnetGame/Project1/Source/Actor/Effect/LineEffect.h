#pragma once
#include "Actor\GameObject.h"
#include "Math\Vec2.h"
#include "Utility\Color.h"

class Timer;

class LineEffect :
	public GameObject
{
public:
	LineEffect(IGameMediator* pGameMediator, float lineAngle, float particleAngle, float effectTime, float lineLength, int particleCount, Color color);
	~LineEffect();

	virtual void start() override;
	virtual void update() override;

private:
	float m_LineAngle;			//�����L�т����
	float m_ParticleAngle;		//�p�[�e�B�N�������ł�������
	int m_ParticleCount;		//�p�[�e�B�N���̔�����
	int m_MaxParticleCount;		//�p�[�e�B�N���̃g�[�^��������
	float m_ParticleInterval;	//�p�[�e�B�N���̔����Ԋu(����)
	Timer* m_pTimer;			//�p�[�e�B�N���̔����Ԋu(����)
	Color m_Color;				//�F
};