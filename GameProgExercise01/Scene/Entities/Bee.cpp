#include "GameProgExercise01.h"
#include "Core.h"
#include "Bee.h"
#include "Scene\Scene.h"
#include "Scene\Entities\Flower.h"
#include "Scene\Entities\Wasp.h"

using namespace DirectX;

namespace scene
{
    const float Bee::Radius = 15.0f;

    Bee::Bee()
    {
        FlyingInsect::m_fIState = FlyingInsect::FIMovement::SeekingNectar;
        DirectX::XMVECTORF32 newPos = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
    }

    Bee::~Bee()
    {
    }

    void Bee::Initialise()
    {
        FlyingInsect::Initialise();

        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();

        SetScale(0.2f);
        DirectX::XMVECTOR beeOrientation = DirectX::XMVECTOR{ 1.0f, 0.0f, 1.0f };
        SetOrientation(beeOrientation);

        FlyingInsect::m_fIState = FlyingInsect::FIMovement::SeekingNectar;

        float thetaPos = static_cast<float>((utils::Rand() % 10000) / 10000.0f); // Gives float 0.0 - 1.0f
        thetaPos = thetaPos * XM_2PI;
        DirectX::XMVECTOR startPos = DirectX::XMVECTOR{ XMScalarSin(thetaPos) * Radius, 3.0f, XMScalarCos(thetaPos) * Radius };
        SetPosition(startPos);

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

    void Bee::PosIter()
    {
        m_timeStep = utils::Timers::GetFrameTime();
        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();

        //Check
        DirectX::XMVECTOR checkPos = m_position - m_flowerPosition;
        DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(checkPos);
        float distanceAsFloat = *checkPosLen.m128_f32;
        if (distanceAsFloat < 0.2f)
        {
            m_nectar = true;
            FlyingInsect::m_fIState = FlyingInsect::FIMovement::SeekingHome;
        }

        Wasp* const closestWasp = scene->GetWaspClosestToEntity(this);
        if (closestWasp != nullptr)
        {
            XMVECTOR closestWaspPosition = closestWasp->GetPosition();

            DirectX::XMVECTOR vecToWasp = closestWaspPosition - m_position;
            DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(vecToWasp);
            float distanceAsFloat = *checkPosLen.m128_f32;
            if (distanceAsFloat < 2.0f)
            {
                FlyingInsect::m_fIState = FlyingInsect::FIMovement::AvoidingWasp;
            }
        }
    }

    void Bee::Update()
    {
        FlyingInsect::Update();

        PosIter();
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