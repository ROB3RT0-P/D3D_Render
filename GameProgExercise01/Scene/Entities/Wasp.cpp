#include "GameProgExercise01.h"
#include "Core.h"
#include "Wasp.h"
#include "Scene\Scene.h"
#include "Scene\Entities\Flower.h"

namespace scene
{
    Wasp::Wasp() :
        m_outOfBounds(false)
    {
        m_state = Movement::SeekingNectar;
        DirectX::XMVECTORF32 newPos = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
    }

    Wasp::~Wasp()
    {
    }

    void Wasp::Initialise()
    {
        static const float MaxSpeed = 4.0f;
        

        Entity::Initialise();
        SetScale(0.2f);
        DirectX::XMVECTOR beeOrientation = DirectX::XMVECTOR{ 1.0f, 0.0f, 1.0f };
        SetOrientation(beeOrientation);

        m_thetaPos = static_cast<float>((utils::Rand() % 10000) / 10000.0f) * DirectX::XM_2PI;; // Gives float 0.0 - 1.0f
        m_speed = static_cast<float>((utils::Rand() % 10000) / 10000.0f); // Gives float 0.0 - 1.0f
        m_speed *= MaxSpeed*2;
        m_nectar = false;
        m_state = Movement::SeekingNectar;

        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();
        Flower* const flower = scene->GetRandFlower();
        m_flowerPosition = flower->GetPosition();

        float zPos = static_cast<float>(utils::Rand() % 5);
        DirectX::XMVECTOR startPos = DirectX::XMVECTOR{ -15.0f, 3.0f, zPos };
        SetPosition(startPos);

        const DX::DeviceResources* const deviceResources = core->GetDeviceResources();

        HRESULT hr = 0;

        auto device = deviceResources->GetD3DDevice();

        // Create vertex buffer.
        static const Vertex s_vertexData[NumVertices] =
        {
            //Body
            { { 0.0f, 0.0f,  0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //1
            { { 0.0f, 1.0f,  0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //2
            { { 1.0f, 0.0f,  0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //3
            { { 1.0f, 1.0f,  0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //4
            { { 1.0f, 0.0f,  1.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //5
            { { 1.0f, 1.0f,  1.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //6
            { { 0.0f, 0.0f,  1.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //7
            { { 0.0f, 1.0f,  1.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //8
            { { 0.0f, 0.0f,  0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //9
            { { 0.0f, 1.0f,  0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //10
            { { 1.0f, 1.0f,  0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //11
            { { 0.0f, 1.0f,  1.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //12
            { { 1.0f, 1.0f,  1.0f, 1.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } },     //13

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

        hr = device->CreateBuffer(&bufferDesc, &initialData,
            &m_vertexBuffer);
        ASSERT_HANDLE(hr);
    }

    
    void Wasp::PosIter()
    {
        m_timeStep = utils::Timers::GetFrameTime();
        m_direction = DirectX::XMVectorSubtract(m_flowerPosition, m_position);
        m_normalisedDir = DirectX::XMVector3Normalize(m_direction);
        m_flowerVelocity = DirectX::XMVectorScale(m_normalisedDir, m_speed);
    }

    void Wasp::SeekingNectar()
    {
        if (!m_nectar)
        {
            m_timeStep = utils::Timers::GetFrameTime();

            if (!m_nectar)
            {
                DirectX::XMVECTORF32 newPos = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
                //NewPos = DirectX::XMVectorScale( Velocity , timeStep );
                newPos.v = DirectX::XMVectorScale(m_flowerVelocity, m_timeStep);
                newPos.v += m_position;

                DirectX::XMVECTOR lerpDir = DirectX::XMVectorLerp(m_orientationAsVector, m_direction, 0.12f * m_timeStep);
                SetOrientation(lerpDir);
                SetPosition(newPos + (DirectX::XMVectorScale(lerpDir, m_speed * m_timeStep)));

                DirectX::XMVECTOR checkPos = m_position - m_flowerPosition;
                DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(checkPos);
                float distanceAsFloat = *checkPosLen.m128_f32;
                if (distanceAsFloat < 0.2f)
                {
                    m_nectar = true;
                    m_state = Movement::SeekingHome;
                }
            }
        }
        else
        {
            m_state = Movement::SeekingHome;
        }
    }

    void Wasp::SeekingHome()
    {
        if (m_nectar) {

            m_timeStep = utils::Timers::GetFrameTime();
            float Radius = 15.0f;
            
            DirectX::XMVECTOR leavePos = DirectX::XMVECTOR{ DirectX::XMScalarSin(m_thetaPos) * Radius, 3.0f, DirectX::XMScalarCos(m_thetaPos) * Radius };

            DirectX::XMVECTOR directionToExitPoint = DirectX::XMVectorSubtract(leavePos, m_position);
            DirectX::XMVECTOR distanceToExitPointVec = DirectX::XMVector3LengthEst(directionToExitPoint);
            float distanceToExitPoint = *distanceToExitPointVec.m128_f32;
            ASSERT(distanceToExitPoint > 0.0001f, "Tiny distance\n");
            DirectX::XMVECTOR normalisedDir = DirectX::XMVector3Normalize(directionToExitPoint);
            DirectX::XMVECTOR desiredVelocity = DirectX::XMVectorScale(normalisedDir, m_speed);

            DirectX::XMVECTOR delta = DirectX::XMVectorScale(desiredVelocity, m_timeStep);
            m_position.v = DirectX::XMVectorAdd(m_position.v, delta);

            SetPosition(m_position.v);


            ///DirectX::XMVECTOR distanceOriginToExitPointVec = DirectX::XMVector3LengthEst(leavePos);
            //float distanceOriginToExitPoint = *distanceOriginToExitPointVec.m128_f32;

            if (distanceToExitPoint <= 0.1f)
            {
                m_outOfBounds = true;
            }
        }
        else {
            m_state = Movement::SeekingNectar;
        }
    }

    void Wasp::Update()
    {
        PosIter();
        
        switch (m_state)
        {
        case Movement::SeekingNectar:
            SeekingNectar();
            break;
        case Movement::SeekingHome:
            SeekingHome();
            break;
        default:
            break;
        }
    }

    bool Wasp::OutOfBounds()
    {
        return m_outOfBounds;
    }

    void Wasp::Render()
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