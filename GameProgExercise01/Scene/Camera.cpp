#include "GameProgExercise01.h"
#include "DX\DeviceResources.h"
#include "Camera.h"

#include "GameProgExercise01.h"
#include "Camera.h"

#include "Core.h"
#include "DX\View.h"

#include "Utils\Timers.h"

using namespace DirectX;
namespace scene
{
	Camera::Camera():m_yAngle(XM_PI * 0.5f)
	{
		m_centre = XMVectorZero();
		m_offset = XMVectorZero();
	}

	void Camera::Initialise()
	{
		m_offset = XMVectorSet(10.0f, 5.0f, 0.0f, 1.0f);
		m_origin.v = { 1.5f, 1.0f, 2.0f };
		m_up = XMVECTOR{ 0.0f, 1.0f, 0.0f, 1.0f };
	}

	void Camera::Update()
	{
		// Create a rotation matrix describing a rotation around the Y axis
		const XMMATRIX rotationY = XMMatrixRotationY(m_yAngle);

		// Rotate our offset (offset is along the x-axis)
		const XMVECTOR rotatedOffset = XMVector3Transform(m_offset, rotationY);

		XMVECTOR eyePosition = rotatedOffset + m_origin.v;
		XMMATRIX viewMatrix = XMMatrixLookAtLH(eyePosition, m_origin.v, m_up);

		const Core* const core = Core::Get();
		DX::View* view = core->GetView();
		XMFLOAT4X4 viewMatrixAsFloat4x4;
		XMStoreFloat4x4(&viewMatrixAsFloat4x4, viewMatrix);
		view->SetViewMatrix(viewMatrixAsFloat4x4);
	}

	void Camera::AdjustYRotation(float rotAmount)
	{
		float timeStep = utils::Timers::GetFrameTime();
		m_yAngle += (rotAmount * timeStep);
	}

	void Camera::AdjustHeight(float adjustedHeight)
	{
		float timeStep = utils::Timers::GetFrameTime();
		m_origin.f[1] += (adjustedHeight * timeStep);
	}
}