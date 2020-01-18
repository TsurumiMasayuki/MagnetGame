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
	float m_LineAngle;			//線が伸びる方向
	float m_ParticleAngle;		//パーティクルが飛んでいく方向
	int m_ParticleCount;		//パーティクルの発生数
	int m_MaxParticleCount;		//パーティクルのトータル発生数
	float m_ParticleInterval;	//パーティクルの発生間隔(距離)
	Timer* m_pTimer;			//パーティクルの発生間隔(時間)
	Color m_Color;				//色
};