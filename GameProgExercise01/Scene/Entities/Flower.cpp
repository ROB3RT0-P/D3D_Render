#include "GameProgExercise01.h"
#include "Core.h"
#include "Flower.h"
#include "Scene\Entities\Bee.h"
#include "Scene\Scene.h"

namespace scene
{
    const float Flower::Spacing = 1.5f;
    const float Flower::FlowerScale = 0.5f;

	float DegreeToRadian(float degree)
	{
		float radian = 0.0f;
		radian = degree * (DirectX::XM_PI / 180);
		return radian;
	}

    Flower::Flower(const UINT x, const UINT z)
    {
        SetPosition(DirectX::XMVECTOR{ (float)x * Spacing, 2.0f, (float)z * Spacing });
    }

    void Flower::Initialise()
    {
        Entity::Initialise();
        DirectX::XMVECTORF32 petalPos = m_position;
        petalPos.f[1] = PetalHeight;
        NectarLevel = static_cast<float>(utils::Rand() % 100);//Get rand num between 0 - 100.

        Core* const core = Core::Get();
        const DX::DeviceResources* const deviceResources = core->GetDeviceResources();
        HRESULT hr = 0;
        auto device = deviceResources->GetD3DDevice();

        // Create vertex buffer.
        static const Vertex s_vertexData[NumVertices] =
        {
            // Triangle one
            { { 0.0f,  0.0f, 0.0f,  0.0f }, { 0.5f, 0.9f, 0.4f, 1.0f } },   // L
            { { 0.05f, 2.0f, 0.05f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },   // T
            { { 0.2f,  0.0f, 0.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },   // R
            
            //Triangle two
            { { 0.0f,  0.0f, 0.0f,  0.0f }, { 0.5f, 0.9f, 0.4f, 1.0f } },   // L
            { { 0.05f, 2.0f, 0.05f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },   // T
            { { 0.2f,  0.0f, 0.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },   // R

            //Triangle three
            { { 0.0f,  0.0f, 0.0f,  0.0f }, { 0.5f, 0.9f, 0.4f, 1.0f } },   // L
            { { 0.05f, 2.0f, 0.05f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },   // T
            { { 0.2f,  0.0f, 0.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },   // R
        };

        // Fill in the first part of allVertices with the above data
        
        float degreeIncrement = 0.0f;
        UINT totalVertices = PetalNumVertices * NumPetals + 9;
        Vertex* allVertices = new Vertex[totalVertices];
   
        int x = 0;
        // Triangle one
        allVertices[x] =
        { { -0.05f,  -2.0f, 0.0f,  1.0f }, { 0.5f, 0.9f, 0.4f, 1.0f } };    // L
        ++x;
        allVertices[x] =
        { { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.5f, 0.5f, 0.4f, 1.0f } };         // T
        ++x;
        allVertices[x] =
        { { 0.05f,  -2.0f, 0.0f,  1.0f }, { 0.5f, 0.9f, 0.4f, 1.0f } };     // R
        ++x;

        //Triangle two
        allVertices[x] =
        { { 0.05f,  -2.0f, 0.0f,  1.0f }, { 0.5f, 0.9f, 0.4f, 1.0f } };     // L
        ++x;
        allVertices[x] =
        { { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.5f, 0.9f, 0.4f, 1.0f } };         // T
        ++x;
        allVertices[x] =
        { { 0.0f, -2.0f, 0.1f, 1.0f }, {0.5f, 0.9f, 0.4f, 1.0f } };        // R
        ++x;

        //Triangle three    
        allVertices[x] =
        { { 0.0f, -2.0f, 0.1f, 1.0f }, { 0.5f, 0.9f, 0.4f, 1.0f } };        // L
        ++x;
        allVertices[x] =
        { { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.5f, 0.9f, 0.4f, 1.0f } };         // T
        ++x;
        allVertices[x] =
        { { -0.05f,  -2.0f, 0.0f,  1.0f }, { 0.5f, 0.9f, 0.4f, 1.0f } };    // R
        ++x;
        
        // Create petals in a loop
        for (; x < (NumPetals * 3) + 9; ++x)
        {
            //Petals
            allVertices[x] =
            { { 0.0f, PetalHeight - 2.0f,  0.0f, 1.0f},{1.0f, 0.0f, 1.0f, 1.0f}};
            ++x;
            allVertices[x] =
            { { std::sin(DegreeToRadian(degreeIncrement)) * FlowerScale, PetalHeight - 2.0f, std::cos(DegreeToRadian(degreeIncrement)) * FlowerScale, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};
            ++x;
            allVertices[x] =
            { { std::sin(DegreeToRadian(degreeIncrement + 45)) * FlowerScale, PetalHeight - 2.0f, std::cos(DegreeToRadian(degreeIncrement + 45)) * FlowerScale, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}};

            degreeIncrement += 45;
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

       delete[] allVertices;
    }

    void Flower::Update()
    {
        float timeStep = utils::Timers::GetFrameTime();
        NectarLevel += timeStep;

        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();

        Bee* const closestBee = scene->GetBeeClosestToFlower(this);
        if (closestBee != nullptr)
        {
            DirectX::XMVECTOR beePos = closestBee->GetPosition();
            DirectX::XMVECTOR vecToBee = beePos - m_position;
            DirectX::XMVECTOR checkPosLenBee = DirectX::XMVector3LengthEst(vecToBee);
            float distanceAsFloatBee = *checkPosLenBee.m128_f32;
            
            if (distanceAsFloatBee < CollisionDist)
            {
                NectarLevel = 0.0f;
            }
        }
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
        context->Draw(PetalNumVertices * NumPetals + NumVertices, 0);
    }
}