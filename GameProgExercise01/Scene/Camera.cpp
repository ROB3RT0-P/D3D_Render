#include "GameProgExercise01.h"
#include "DX\DeviceResources.h"
#include "Camera.h"

class Camera
{
	void Initialise()
	{
		// Initialize the view matrix
		static const DirectX::XMVECTORF32 eye = { 5.0f, -5.0f, -4.0f, 0.0f };
		static const DirectX::XMVECTORF32 at = { 0.0f, 0.0f, 0.0f, 0.0f };
		static const DirectX::XMVECTORF32 up = { 0.0f, 1.0f, 0.0f, 0.0f };
		XMStoreFloat4x4(&m_viewMatrix, XMMatrixLookAtLH(eye, at, up));
	}
	
	void Update()
	{
	//XMMatrixRotationRollPitchYaw
	}
};