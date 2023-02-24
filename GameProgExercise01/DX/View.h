#pragma once

namespace DX
{

	class DeviceResources;

	class View
	{
	public:
		struct ConstantBuffer
		{
			DirectX::XMMATRIX worldMatrix;
			DirectX::XMMATRIX viewMatrix;
			DirectX::XMMATRIX projectionMatrix;
		};
		static_assert((sizeof(ConstantBuffer) % 16) == 0, "Constant buffer must always be 16-byte aligned");

		View(DeviceResources* const deviceResources);
		~View();

		void							Initialise();
		void							Refresh();
		void							Shutdown();

	private:
		DeviceResources* m_deviceResources;
		ID3D11Buffer* m_constantBuffer;

		DirectX::XMFLOAT4X4				m_worldMatrix;
		DirectX::XMFLOAT4X4				m_viewMatrix;
		DirectX::XMFLOAT4X4				m_projectionMatrix;
	};

} // namespace DX