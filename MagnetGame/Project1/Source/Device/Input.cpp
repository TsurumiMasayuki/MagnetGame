#include "Input.h"
#include <sstream>
#include "Def\Screen.h"
#include "Device\Camera.h"
#include "Math\MathUtility.h"

BYTE Input::m_CurKeys[256];
BYTE Input::m_PreKeys[256];

JOYINFOEX Input::m_CurPadInfo;
JOYINFOEX Input::m_PrePadInfo;

#define PRESSED 0x80
#define JOYSTICK_CENTER 32767.0f
#define JOYSTICK_MAX 65535.0f

bool Input::isKeyUp(UINT key)
{
	return !(m_CurKeys[key] & PRESSED) && (m_PreKeys[key] & PRESSED);
}

bool Input::isKey(UINT key)
{
	return (m_CurKeys[key] & PRESSED) && (m_PreKeys[key] & PRESSED);
}

bool Input::isKeyDown(UINT key)
{
	return (m_CurKeys[key] & PRESSED) && !(m_PreKeys[key] & PRESSED);
}

Vec3 Input::getMousePosition()
{
	HWND hwnd = FindWindow("Project1", "Project1");

	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(hwnd, &cursorPos);

	return Vec3(
		cursorPos.x - Screen::getWindowWidth() * 0.5f,
		-cursorPos.y + Screen::getWindowHeight() * 0.5f,
		0);
}

Vec3 Input::getWorldMousePosition()
{
	return getMousePosition() - Camera::getPosition();
}

bool Input::isPadButtonUp(PAD_BUTTON button)
{
	return !(m_CurPadInfo.dwButtons & button) && (m_PrePadInfo.dwButtons & button);
}

bool Input::isPadButton(PAD_BUTTON button)
{
	return (m_CurPadInfo.dwButtons & button) && (m_PrePadInfo.dwButtons & button);
}

bool Input::isPadButtonDown(PAD_BUTTON button)
{
	return (m_CurPadInfo.dwButtons & button) && !(m_PrePadInfo.dwButtons & button);
}

Vec2 Input::getDPadValue()
{
	Vec2 axis;
	//�����͂���Ă�����
	if (m_CurPadInfo.dwPOV == JOY_POVLEFT)
	{
		axis.x = -1;
		axis.y = 0;
	}

	//�E���͂���Ă�����
	if (m_CurPadInfo.dwPOV == JOY_POVRIGHT)
	{
		axis.x = 1;
		axis.y = 0;
	}

	//����͂���Ă�����
	if (m_CurPadInfo.dwPOV == JOY_POVFORWARD)
	{
		axis.x = 0;
		axis.y = 1;
	}

	//����͂���Ă�����
	if (m_CurPadInfo.dwPOV == JOY_POVBACKWARD)
	{
		axis.x = 0;
		axis.y = -1;
	}

	return axis;
}

Vec2 Input::getLStickValue()
{
	Vec2 axis(0, 0);
	//-JOYSTICK_CENTER ~ +JOYSTICK_CENTER�̊Ԃɒl���C��
	float centeredX = (m_CurPadInfo.dwXpos - JOYSTICK_CENTER);
	float centeredY = (m_CurPadInfo.dwYpos - JOYSTICK_CENTER);

	//-1 ~ 1�̊Ԃɕϊ�
	if (centeredX != 0)
		axis.x = MathUtility::clamp(centeredX / JOYSTICK_CENTER, -1.0f, 1.0f);

	//-1 ~ 1�̊Ԃɕϊ�(Y�̏ꍇ�͕������t�ɂ���)
	if (centeredY != 0)
		axis.y = MathUtility::clamp(centeredY / JOYSTICK_CENTER, -1.0f, 1.0f) * -1.0f;

	return axis;
}

Vec2 Input::getRStickValue()
{
	Vec2 axis(0, 0);
	//-JOYSTICK_CENTER ~ +JOYSTICK_CENTER�̊Ԃɒl���C��
	float centeredZ = (m_CurPadInfo.dwZpos - JOYSTICK_CENTER);
	float centeredR = (m_CurPadInfo.dwRpos - JOYSTICK_CENTER);

	//-1 ~ 1�̊Ԃɕϊ�
	if (centeredZ != 0)
		axis.x = MathUtility::clamp(centeredZ / JOYSTICK_CENTER, -1.0f, 1.0f);

	//-1 ~ 1�̊Ԃɕϊ�(Y�̏ꍇ�͕������t�ɂ���)
	if (centeredR != 0)
		axis.y = MathUtility::clamp(centeredR / JOYSTICK_CENTER, -1.0f, 1.0f) * -1.0f;

	return axis;
}

void Input::update()
{
	//�O�t���[���̃L�[�{�[�h���͂��R�s�[
	memcpy_s(m_PreKeys, sizeof(m_PreKeys), m_CurKeys, sizeof(m_CurKeys));
	//���݂̃t���[���̃L�[�{�[�h���͂��擾
	GetKeyboardState(m_CurKeys);

	//�O�t���[���̏�Ԃ��R�s�[
	m_PrePadInfo = m_CurPadInfo;

	//�擾�������f�[�^�̃T�C�Y�w��(RETURNALL���w�肵�Ă���̂ō\���̂Ɠ���)
	m_CurPadInfo.dwSize = sizeof(JOYINFOEX);
	m_CurPadInfo.dwFlags = JOY_RETURNALL;

	bool noError = false;

	//�ڑ�����Ă���R���g���[���[��T��
	for (int i = 0; i < joyGetNumDevs(); i++)
	{
		//���Ȃ��ڑ�����Ă���R���g���[���[������������I��
		if (joyGetPosEx(i, &m_CurPadInfo) == JOYERR_NOERROR)
		{
			noError = true;
			break;
		}
	}

	//�ڑ�����Ă��Ȃ������珈���𒆒f
	if (!noError) return;

	Vec2 axis = getRStickValue();
}
