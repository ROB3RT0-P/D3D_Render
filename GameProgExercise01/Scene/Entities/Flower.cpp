#include "GameProgExercise01.h"
#include "Core.h"
#include "Flower.h"

namespace scene
{
    
    Flower::Flower(const UINT x, const UINT z)
    {
        
        SetPosition(DirectX::XMVECTOR{ (float)x, 0.0f, (float)z });
    }

    void Flower::Initialise()
    {
        Entity::Initialise();

        Core* const core = Core::Get();

        const DX::DeviceResources* const deviceResources = core->GetDeviceResources();

        HRESULT hr = 0;

        auto device = deviceResources->GetD3DDevice();

        UINT totalVertices = NumVertices + 3 * NumPetals;

        scene::Vertex allVertices = new Vertex[totalVertices];

        // Create vertex buffer.
        static const Vertex s_vertexData[NumVertices] =
        {
            // Triangle one
            { { 0.0f,   0.0f,  0.0f, 0.0f },{ 0.5f, 0.9f, 0.4f, 1.0f } },  // L
            { { 0.05f,  2.0f,  0.05f, 1.0f },{ 0.0f, 0.8f, 0.4f, 1.0f } },  // T
            { { 0.2f, 0.0f,  0.0f, 1.0f },{ 0.5f, 0.9f, 0.4f, 1.0f } },  // R

            // Triangle two
            { { 0.2f,  0.0f,  0.0f, 1.0f },{ 0.5f, 0.9f, 0.4f, 1.0f } },   // L
            { { 0.05f,  2.0f,  0.05f, 1.0f },{ 0.0f, 0.8f, 0.4f, 1.0f } },  // T
            { { 0.1f,   0.0f,  0.1f, 1.0f },{ 0.5f, 0.9f, 0.4f, 1.0f } }, // R

            // Triangle three
            { { 0.1f,  0.0f,  0.1f, 1.0f },{ 0.5f, 0.9f, 0.4f, 1.0f } },   // L
            { { 0.05f,  2.0f,  0.05f, 1.0f },{ 0.0f, 0.8f, 0.4f, 1.0f } },  // T
            { { 0.0f,   0.0f,  0.0f, 1.0f },{ 0.5f, 0.9f, 0.4f, 1.0f } }, // R
        };

        // Fill in the first part of allVertices with the above data
        {
         //   NumVertices
        }

        // Create petals in a loop
        for (int x; x < NumPetals; ++x)
            {
            for (int z; z < NumPetals; ++z)
            {
                 //Petals
                 // Triangle one - Green
                 { { 0.05f,  2.0f,  0.05f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },  // Centre
                 { { 0.0f, 2.0f,  0.2f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },  // Right
                 { { 0.1f, 2.0f,  0.25f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },  // Left

                 { { 0.1f,  2.0f,  0.25f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },  // Left
                 { { 0.0f, 2.0f,  0.2f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },  // Right
                 { { 0.05f, 2.0f,  0.3f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } }  // Centre
            }
            ++NumPetals;
        }


        D3D11_SUBRESOURCE_DATA initialData = {};
        initialData.pSysMem = allVertices;

        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.ByteWidth = sizeof(Vertex) * totalVertices;
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.StructureByteStride = sizeof(Vertex);


        hr = device->CreateBuffer(&bufferDesc, &initialData,
            &m_vertexBuffer);
        ASSERT_HANDLE(hr);

        delete allVertices;
    }



    void Flower::Render()
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