#include "GameProgExercise01.h"
#include "Core.h"
#include "Flower.h"

/*

void Flower::SetupTriangle()
{
    Core* const core = Core::Get();

    DX::DeviceResources* const deviceResources = core->GetDeviceResources();

    HRESULT hr = 0;

    auto device = deviceResources->GetD3DDevice();

    void* vertShaderData;
    void* pxShaderData;

    DWORD size = 0;

    // Load and create the vertex shader.
    HANDLE vsHandle = file::GetFileData("VertexShader.cso", &vertShaderData, &size);


    hr = device->CreateVertexShader(vertShaderData, size,
        nullptr, &m_spVertexShader);
    ASSERT_HANDLE(hr);

    // Create input layout.
    static const D3D11_INPUT_ELEMENT_DESC s_inputElementDesc[2] =
    {
        { "SV_Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA,  0 },
        { "COLOR",       0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA , 0 },
    };


    hr = device->CreateInputLayout(s_inputElementDesc, _countof(s_inputElementDesc),
        vertShaderData, size,
        &m_spInputLayout);
    ASSERT_HANDLE(hr);

    file::CloseFile(vsHandle);

    // Handle loading and creating the pixel shader
    HANDLE pxHandle = file::GetFileData("PixelShader.cso", &pxShaderData, &size);

    hr = device->CreatePixelShader(pxShaderData, size,
        nullptr, &m_spPixelShader);
    ASSERT_HANDLE(hr);

    file::CloseFile(pxHandle);

    // Create vertex buffer.
    static const Vertex s_vertexData[NumVertices] =
    {
        { { 0.0f,   0.25f,  0.5f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },  // Top
        { { 0.25f,  -0.5f,  0.5f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },  // Right
        { { -0.25f, -0.5f,  0.5f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },  // Left

    };

    D3D11_SUBRESOURCE_DATA initialData = {};
    initialData.pSysMem = s_vertexData;

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.ByteWidth = sizeof(s_vertexData);
    bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.StructureByteStride = sizeof(Vertex);


    hr = device->CreateBuffer(&bufferDesc, &initialData,
        &m_spVertexBuffer);
    ASSERT_HANDLE(hr);
}



void Flower::Render()
{
    Core* const core = Core::Get();

    DX::DeviceResources* const deviceResources = core->GetDeviceResources();

    auto context = deviceResources->GetD3DDeviceContext();

    // Set input assembler state.
    context->IASetInputLayout(m_spInputLayout);

    UINT strides = sizeof(Vertex);
    UINT offsets = 0;
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->IASetVertexBuffers(0, 1, &m_spVertexBuffer, &strides, &offsets);

    // Set shaders.
    context->VSSetShader(m_spVertexShader, nullptr, 0);
    context->GSSetShader(nullptr, nullptr, 0);
    context->PSSetShader(m_spPixelShader, nullptr, 0);

    // Draw triangle.
    context->Draw(NumVertices, 0);
}

*/