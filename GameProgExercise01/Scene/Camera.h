#pragma once

namespace scene
{

	class Camera
	{
	public:
		Camera();
		void Initialise();
		void Update();
		void AdjustYRotation(float rotAmount);

	private:
		DirectX::XMVECTOR m_Centre;
		DirectX::XMVECTOR m_Offset;
		float m_yAngle = 0.0f;

	};
}