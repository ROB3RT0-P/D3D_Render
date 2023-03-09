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
		DirectX::XMVECTOR m_centre;
		DirectX::XMVECTOR m_offset;
		float m_yAngle;
	};
}