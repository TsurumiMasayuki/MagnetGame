#include "Camera.h"
#include "Def\Screen.h"
#include <DirectXMath.h>

Vec3 Camera::m_Position = Vec3::zero();
DirectX::XMMATRIX Camera::viewMatrix2D;
DirectX::XMMATRIX Camera::viewMatrix3D;
DirectX::XMMATRIX Camera::projMatrix;
DirectX::XMMATRIX Camera::orthoMatrix;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::init()
{
	//2D�p
	//�J�����̍��W
	DirectX::XMVECTOR vEyePt = { m_Position.x, m_Position.y, -10.0f, 0 };
	//�J������������W
	DirectX::XMVECTOR vLookatPt = DirectX::XMVectorSet(m_Position.x, m_Position.y, 0.0f, 0.0f);
	//�J�����̉�]�̎�
	DirectX::XMVECTOR vUpVec = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//����s��
	viewMatrix2D = DirectX::XMMatrixLookAtLH(vEyePt, vLookatPt, vUpVec);

	//���s���e�̍s��
	orthoMatrix = DirectX::XMMatrixOrthographicLH(Screen::getWindowWidth(), Screen::getWindowHeight(), 1.0f / (100.0f - 0.3f), 100.0f);

	//3D�p
	////�J�����̍��W
	//DirectX::XMVECTOR vEyePt = {m_Position.x, m_Position.y, m_Position.z, 0};
	////�J������������W
	//DirectX::XMVECTOR vLookatPt = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	////�J�����̉�]�̎�
	//DirectX::XMVECTOR vUpVec = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	////����s��
	//DirectX::XMMATRIX view3D = DirectX::XMMatrixLookAtLH(vEyePt, vLookatPt, vUpVec);
	//DirectX::XMStoreFloat4x4(&viewMatrix3D, view3D);

	//�������e�̍s��
}

void Camera::update()
{
	//2D�p
	//�J�����̍��W
	DirectX::XMVECTOR vEyePt = { m_Position.x, m_Position.y, -10.0f, 0 };
	//�J������������W
	DirectX::XMVECTOR vLookatPt = DirectX::XMVectorSet(m_Position.x, m_Position.y, 0.0f, 0.0f);
	//�J�����̉�]�̎�
	DirectX::XMVECTOR vUpVec = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//����s��
	viewMatrix2D = DirectX::XMMatrixLookAtLH(vEyePt, vLookatPt, vUpVec);

	//���s���e�̍s��
	orthoMatrix = DirectX::XMMatrixOrthographicLH(Screen::getWindowWidth(), Screen::getWindowHeight(), 1.0f / (100.0f - 0.3f), 100.0f);
}

void Camera::reset()
{
	m_Position = Vec3::zero();
}

void Camera::setPosition(Vec3 position)
{
	m_Position = position;
}

Vec3 Camera::getPosition()
{
	return m_Position;
}

DirectX::XMMATRIX Camera::getViewProjMatrix()
{
	return DirectX::XMMATRIX();
}

DirectX::XMMATRIX Camera::getViewOrthoMatrix()
{
	return viewMatrix2D * orthoMatrix;
}
