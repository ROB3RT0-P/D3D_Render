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
		void AdjustHeight(float adjustedHeight);

	private:
		DirectX::XMVECTOR m_centre;
		DirectX::XMVECTOR m_offset;
		DirectX::XMVECTOR m_up;
		DirectX::XMVECTORF32 m_origin;
		float m_yAngle;
	};
}