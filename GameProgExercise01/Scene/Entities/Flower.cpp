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

        Vertex *allVertices = new Vertex[totalVertices];

        scene::Vertex* firstPetalVertex = allVertices + NumVertices; // NumVertices should be called NumStemVertices or something         static const float PetalLength = 5.0f; // Move this somewhere nicer.
        static const DirectX::XMFLOAT4 PetalColour = DirectX::XMFLOAT4(0.9f, 0.5f, 0.9f, 1.0f); // Move  this somewhere nicer
        float petalAngle = 0.0f;
        float petalAngleWidth = DirectX::XM_2PI / (float)NumPetals * 0.9f;
        const float petalYOffset = 1.0f;
        float sinValue, cosValue;
        for (int petalIndex = 0; petalIndex < NumPetals; ++petalIndex)
        {
            // Calculate the coordinates of the petal edge vertices
            petalAngle = DirectX::XM_2PI / (float)(NumPetals * petalIndex);// Get the vertex for the centre of the petal
            scene::Vertex* const petalCentre = firstPetalVertex + petalIndex * 3;// File in the petal centre (the origin) vertex values
            DirectX::XMStoreFloat4(&petalCentre->position, DirectX::XMVectorZero());
            petalCentre->color = PetalColour;// Get the first petal edge vertex
            DirectX::XMScalarSinCosEst(&sinValue, &cosValue, petalAngle + petalAngleWidth); // Note adding the angle width
            scene::Vertex* const petalEdge1 = firstPetalVertex + petalIndex * 3 + 1; // Advance by 1             // Fill in the first of the edge petal positions
            petalEdge1->position = DirectX::XMFLOAT4(sinValue * PetalLength, petalYOffset, cosValue * PetalLength, 1.0f);
            petalEdge1->color = PetalColour;// Get the second petal edge vertex
            DirectX::XMScalarSinCosEst(&sinValue, &cosValue, petalAngle - petalAngleWidth); // Note subtracting the angle width
            scene::Vertex* const petalEdge2 = firstPetalVertex + petalIndex * 3 + 2; // Advance by 2             // Fill in the first of the edge petal positions
            petalEdge1->position = DirectX::XMFLOAT4(sinValue * PetalLength, petalYOffset, cosValue * PetalLength, 1.0f);
            petalEdge1->color = PetalColour;
        }

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

        const UINT NumVertices = NumPetals * 3;
        // Create petals in a loop
        for (int x; x < NumPetals; ++x)
        {
            for (int z; z < NumPetals; ++z)
            {
                static Vertex s_petalVertexData[NumVertices] = {
                    //Petals
                    // Triangle one - Green
                    { { 0.05f, 2.0f, 0.05f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },  // Centre
                    { { 0.0f, 2.0f,  0.2f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },  // Right
                    { { 0.1f, 2.0f,  0.25f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },  // Left

                    { { 0.1f,  2.0f,  0.25f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },  // Left
                    { { 0.0f, 2.0f,  0.2f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } },  // Right
                    { { 0.05f, 2.0f,  0.3f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } }  // Centre
                };
            }
            //++NumPetals;
        };


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


    //D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
    
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