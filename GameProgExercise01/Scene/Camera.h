#pragma once

class Camera
{
	public:
		struct ConstantBuffer
		{
			DirectX::XMMATRIX cameraMatrix;
		};
		static_assert((sizeof(ConstantBuffer) % 16) == 0, "Constant buffer must always be 16-byte aligned");

		void Initialise();
		void Update();

	private:
		DirectX::XMFLOAT4X4 m_cameraMatrix;
};