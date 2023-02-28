#include "GameProgExercise01.h"
#include "Core.h"
#include "Ground.h"

namespace scene
{

    void Ground::Initialise()
    {
        Entity::Initialise();

        Core* const core = Core::Get();

        const DX::DeviceResources* const deviceResources = core->GetDeviceResources();

        HRESULT hr = 0;

        auto device = deviceResources->GetD3DDevice();

        // Create vertex buffer.
        static const Vertex s_vertexData[NumVertices] =
        {
              /* // Triangle one
            { { -0.5f,   0.0f,  0.0f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },  // L
            { { 0.0f,  1.0f,  0.5f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },  // T
            { { 0.5f, 0.0f,  0.0f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },  // R

            // Triangle two
            { { 0.0f,  0.0f,  1.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },   // Bottom
            { { 0.0f,  1.0f,  0.5f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },  // Left
            { { -0.5f,   0.0f,  0.0f, 1.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } }, // Right

            // Triangle three
            { { 0.5f,  0.0f,  0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },   // Bottom
            { { 0.0f,  1.0f,  0.5f, 1.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },  // Left
            { { 0.0f,   0.0f,  1.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } } // Right
 */

         
            // Triangle one - Green
            { { -1.0f,   0.0f,  -1.0f, 1.0f },{ 0.5f, 0.7f, 0.1f, 1.0f } },  // Top
            { { -1.0f,  0.0f,  5.0f, 1.0f },{ 0.5f, 0.7f, 0.1f, 1.0f } },  // Right
            { { 4.0f, 0.0f,  -1.0f, 1.0f },{0.5f, 0.7f, 0.1f, 1.0f } },  // Left

            // Triangle two - Green
            { { 4.0f,   0.0f,  -1.0f, 1.0f },{ 0.5f, 0.7f, 0.1f, 1.0f } },   // Bottom
            { { -1.0f, 0.0f,  5.0f, 1.0f },{ 0.5f, 0.7f, 0.1f, 1.0f } },  // Left
            { { 4.0f, 0.0f,  5.0f, 1.0f },{ 0.5f, 0.7f, 0.1f, 1.0f } }, // Right

           
        };

        D3D11_SUBRESOURCE_DATA initialData = {};
        initialData.pSysMem = s_vertexData;

        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.ByteWidth = sizeof(s_vertexData);
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.StructureByteStride = sizeof( Vertex );


        hr = device->CreateBuffer(&bufferDesc, &initialData,
            &m_vertexBuffer);
        ASSERT_HANDLE(hr);
    }



    void Ground::Render()
    {
        Entity::Render();

        Core* const core = Core::Get();

        const DX::DeviceResources* const deviceResources = core->GetDeviceResources();

        auto context = deviceResources->GetD3DDeviceContext();


        UINT strides = sizeof(Vertex);
        UINT offsets = 0;
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &strides, &offsets);

        // Draw triangle.
        context->Draw(NumVertices, 0);
    }
}