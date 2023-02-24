#pragma once
#include "DX\DeviceResources.h"

class Ground  final : public DX::IDeviceNotify
{
public:
    static const UINT NumVertices = 9;

    void Render();
    void SetupTriangle();

private:

	
    virtual void OnDeviceLost() {}
    virtual void OnDeviceRestored() {}

    ID3D11InputLayout*      m_spInputLayout;
    ID3D11Buffer*           m_spVertexBuffer;
    ID3D11VertexShader*     m_spVertexShader;
    ID3D11PixelShader*      m_spPixelShader;
};

struct Vertex
{
    DirectX::XMFLOAT4 position;
    DirectX::XMFLOAT4 color;
};