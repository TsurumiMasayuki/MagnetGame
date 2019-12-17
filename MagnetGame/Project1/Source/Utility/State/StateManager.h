#pragma once
#include "Utility\State\IState.h"

class StateManager
{
public:
	virtual ~StateManager();
	//�X�V����
	virtual void update();
	//�X�e�[�g���Z�b�g
	virtual void setState(IState* newState);
	//�X�e�[�g�������I�ɕύX(�����A�o�������͌Ă΂�Ȃ�)
	void forceSetState(IState* newState);

protected:
	IState* m_pCurrentState;
};