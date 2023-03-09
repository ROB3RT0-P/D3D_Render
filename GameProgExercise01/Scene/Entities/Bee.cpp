#include "GameProgExercise01.h"
#include "Core.h"
#include "Bee.h"
#include "Scene\Scene.h"
#include "Scene\Entities\Flower.h"
#include "Scene\Entities\Wasp.h"

using namespace DirectX;

namespace scene
{
    const float Bee::RadiusToBoundary = 15.0f;
    const float Bee::WaspDangerDistance = 2.0f;
    const float Bee::FlowerCollisionDist = 0.2f;
    float timeStep;

    Bee::Bee()
    {
        FlyingInsect::m_fIState = FlyingInsect::FIMovement::SeekingNectar;
    }

    Bee::~Bee()
    {
    }

    void Bee::Initialise()
    {
        FlyingInsect::Initialise();

        SetScale(0.2f);
        DirectX::XMVECTOR beeOrientation = DirectX::XMVECTOR{ 1.0f, 0.0f, 1.0f };
        SetOrientation(DirectX::XMVector3Normalize(beeOrientation));

        FlyingInsect::m_fIState = FlyingInsect::FIMovement::SeekingNectar;

        float thetaPos = static_cast<float>((utils::Rand() % 10000) / 10000.0f); // Gives float 0.0 - 1.0f
        thetaPos = thetaPos * XM_2PI;
        DirectX::XMVECTOR startPos = DirectX::XMVECTOR{ XMScalarSin(thetaPos) * RadiusToBoundary, 3.0f, XMScalarCos(thetaPos) * RadiusToBoundary };
        SetPosition(startPos);
        
        const Core* const core = Core::Get();
        const DX::DeviceResources* const deviceResources = core->GetDeviceResources();

        HRESULT hr = 0;

        auto device = deviceResources->GetD3DDevice();

        // Create vertex buffer.
        static const Vertex s_vertexData[NumVertices] =
        {
            //Body
            { { 0.0f, 0.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //1
            { { 0.0f, 1.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //2
            { { 1.0f, 0.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //3
            { { 1.0f, 1.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //4
            { { 1.0f, 0.0f,  1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //5
            { { 1.0f, 1.0f,  1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //6
            { { 0.0f, 0.0f,  1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //7
            { { 0.0f, 1.0f,  1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //8
            { { 0.0f, 0.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //9
            { { 0.0f, 1.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //10
            { { 1.0f, 1.0f,  0.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //11
            { { 0.0f, 1.0f,  1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //12
            { { 1.0f, 1.0f,  1.0f, 1.0f },{ 1.0f, 1.0f, 0.0f, 1.0f } },     //13

            //Stripe
            { { 1.01f, 0.0f,  0.4f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },    //1
            { { 1.01f, 0.0f,  0.6f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },    //2
            { { 1.01f, 1.01f,  0.4f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },   //3
            { { 1.01f, 1.01f,  0.6f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },   //4
            { { -0.01f, 1.01f,  0.4f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },  //5
            { { -0.01f, 1.01f,  0.6f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },  //6
            { { -0.01f, 0.0f,  0.4f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },   //7
            { { -0.01f, 0.0f,  0.6f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } }    //8
        };

        D3D11_SUBRESOURCE_DATA initialData = {};
        initialData.pSysMem = s_vertexData;
        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.ByteWidth = sizeof(s_vertexData);
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.StructureByteStride = sizeof(Vertex);
        hr = device->CreateBuffer(&bufferDesc, &initialData, &m_vertexBuffer);
        ASSERT_HANDLE(hr);
    }

    void Bee::Update()
    {
        FlyingInsect::Update();

        timeStep = utils::Timers::GetFrameTime();
        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();

        // Check distance between entity and flower.
        DirectX::XMVECTOR checkDir = m_position - m_flowerPosition;
        DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(checkDir);
        float distanceAsFloat = *checkPosLen.m128_f32;
        if (distanceAsFloat < FlowerCollisionDist)
        {
            m_nectar = true;
            FlyingInsect::m_fIState = FlyingInsect::FIMovement::SeekingHome;
        }

        // Check distance between entity and closest wasp.
        Wasp* const closestWasp = scene->GetWaspClosestToEntity(this);
        if (closestWasp != nullptr)
        {
            XMVECTOR closestWaspPosition = closestWasp->GetPosition();

            DirectX::XMVECTOR vecToWasp = closestWaspPosition - m_position;
            DirectX::XMVECTOR checkPosLenWasp = DirectX::XMVector3LengthEst(vecToWasp);
            float distanceAsFloatWasp = *checkPosLenWasp.m128_f32;
            if (distanceAsFloatWasp < WaspDangerDistance)
            {
                FlyingInsect::m_fIState = FlyingInsect::FIMovement::AvoidingWasp;
            }
        }
    }

    void Bee::Render()
    {
        Entity::Render();
        Core* const core = Core::Get();
        const DX::DeviceResources* const deviceResources = core->GetDeviceResources();
        auto context = deviceResources->GetD3DDeviceContext();
        UINT strides = sizeof(Vertex);
        UINT offsets = 0;
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        context->IASetVertexBuffers(0, 1, &m_vertexBuffer, &strides, &offsets);
        context->Draw(NumVertices, 0);
    }
}