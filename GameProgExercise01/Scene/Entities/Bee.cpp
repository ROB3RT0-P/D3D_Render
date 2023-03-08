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

    Bee::Bee() :
        m_outOfBounds( false )
    {
        m_state = Movement::SeekingNectar;
        DirectX::XMVECTORF32 newPos = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
    }

    Bee::~Bee()
    {
    }

    void Bee::Initialise()
    {
        static const float MaxSpeed = 4.0f;

        Entity::Initialise();
        SetScale(0.2f);
        DirectX::XMVECTOR beeOrientation = DirectX::XMVECTOR{ 1.0f, 0.0f, 1.0f };
        SetOrientation( beeOrientation );

        m_thetaPos = static_cast<float>((utils::Rand() % 10000) / 10000.0f) * DirectX::XM_2PI;; // Gives float 0.0 - 1.0f
        m_speed = static_cast<float>((utils::Rand() % 10000) / 10000.0f); // Gives float 0.0 - 1.0f
        m_speed *= MaxSpeed/4;
        m_nectar = false;
        m_state = Movement::SeekingNectar;

        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();
        Flower* const flower = scene->GetRandFlower();
        m_flowerPosition = flower->GetPosition();

        float thetaPos = static_cast<float>((utils::Rand() % 10000) / 10000.0f); // Gives float 0.0 - 1.0f
        thetaPos = thetaPos * XM_2PI;
        DirectX::XMVECTOR startPos = DirectX::XMVECTOR{ XMScalarSin(thetaPos) * Radius, 3.0f, XMScalarCos(thetaPos) * Radius };
        SetPosition( startPos );

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

        /*  
        Wasp* const wasp = scene->GetWasps();
        m_waspPosition = wasp->GetPosition();
        */

        //Check
        DirectX::XMVECTOR checkPos = m_position - m_flowerPosition;
        DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(checkPos);
        float distanceAsFloat = *checkPosLen.m128_f32;
        if (distanceAsFloat < 0.2f)
        {
            m_nectar = true;
            m_state = Movement::SeekingHome;
        } 
    }

    void Bee::SeekingNectar()
    {
        if (!m_nectar)
        {
            m_timeStep = utils::Timers::GetFrameTime();

            if (!m_nectar)
            {
                DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(m_flowerPosition, m_position);
                DirectX::XMVECTOR normalisedDir = DirectX::XMVector3Normalize(direction);
                DirectX::XMVECTOR flowerVelocity = DirectX::XMVectorScale(normalisedDir, m_speed);

                DirectX::XMVECTORF32 newPos = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
                //NewPos = DirectX::XMVectorScale( Velocity , timeStep );
                newPos.v = DirectX::XMVectorScale(flowerVelocity, m_timeStep);
                newPos.v += m_position;

                DirectX::XMVECTOR lerpDir = DirectX::XMVectorLerp(m_orientationAsVector, direction, 0.12f * m_timeStep);
                SetOrientation(lerpDir);
                SetPosition(newPos + (DirectX::XMVectorScale(lerpDir, m_speed)));

                DirectX::XMVECTOR checkPos = m_position - m_flowerPosition;
                DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(checkPos);
                float distanceAsFloat = *checkPosLen.m128_f32;
                if (distanceAsFloat < 0.2f)
                {
                    m_nectar = true;
                }
            }
        }
        else
        {
            m_state = Movement::SeekingHome;
        }

        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();

        Wasp* const closestWasp = scene->GetWaspClosestToEntity(this);
        if (closestWasp != nullptr)
        {
            XMVECTOR closestWaspPosition = closestWasp->GetPosition();

            DirectX::XMVECTOR vecToWasp = closestWaspPosition - m_position;
            DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(vecToWasp);
            float distanceAsFloat = *checkPosLen.m128_f32;
            if (distanceAsFloat < 2.0f)
            {
                m_state = Movement::AvoidingWasp;
            }
        }
    }

    void Bee::AvoidingWasp()
    {
        m_timeStep = utils::Timers::GetFrameTime();
        DirectX::XMVECTOR vecToWasp = m_position - m_waspPosition;
        DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(vecToWasp);
        XMVECTOR vecFromWasp = XMVectorNegate(vecToWasp);//
        XMVECTOR dirFromWasp = XMVector3Normalize(vecToWasp);
        DirectX::XMVECTOR waspVelocity = DirectX::XMVectorScale(dirFromWasp, m_speed);
        DirectX::XMVECTORF32 newPos = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
        //NewPos = DirectX::XMVectorScale( Velocity , timeStep );
        newPos.v = DirectX::XMVectorScale(waspVelocity, m_timeStep);
        newPos.v += m_position;

        DirectX::XMVECTOR lerpDir = DirectX::XMVectorLerp(m_orientationAsVector, dirFromWasp, 10.0f * m_timeStep);
        SetOrientation(lerpDir);
        SetPosition(newPos + (DirectX::XMVectorScale(lerpDir, m_speed)));

        float distanceAsFloat = *checkPosLen.m128_f32;
        if (distanceAsFloat > 10.0f)
        {
            m_state = Movement::SeekingNectar;
        }
    }

    void Bee::SeekingHome()
    {
        if (m_nectar) {

            m_timeStep = utils::Timers::GetFrameTime();
            float Radius = 150.0f;

            DirectX::XMVECTOR leavePos = DirectX::XMVECTOR{ DirectX::XMScalarSin(m_thetaPos) * Radius, 3.0f, DirectX::XMScalarCos(m_thetaPos) * Radius };

            DirectX::XMVECTOR directionToExitPoint = DirectX::XMVectorSubtract(leavePos, m_position);
            DirectX::XMVECTOR distanceToExitPointVec = DirectX::XMVector3LengthEst(directionToExitPoint);
            float distanceToExitPoint = *distanceToExitPointVec.m128_f32;
           // ASSERT(distanceToExitPoint > 0.0001f, "Tiny distance\n");
            DirectX::XMVECTOR normalisedDir = DirectX::XMVector3Normalize(directionToExitPoint);
            DirectX::XMVECTOR desiredVelocity = DirectX::XMVectorScale(normalisedDir, m_speed * 80);

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
        else 
        {
            m_state = Movement::SeekingNectar;
        }

        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();

        Wasp* const closestWasp = scene->GetWaspClosestToEntity(this);
        if (closestWasp != nullptr)
        {
            XMVECTOR closestWaspPosition = closestWasp->GetPosition();

            DirectX::XMVECTOR vecToWasp = closestWaspPosition - m_position;
            DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(vecToWasp);
            float distanceAsFloat = *checkPosLen.m128_f32;
            if (distanceAsFloat < 2.0f)
            {
                m_state = Movement::AvoidingWasp;
            }
        }
    }


    void Bee::Update()
    {
        PosIter();

        switch (m_state)
        {
        case Movement::SeekingNectar:
            SeekingNectar();
            break;
        case Movement::AvoidingWasp:
            AvoidingWasp();
            break;
        case Movement::SeekingHome:
            SeekingHome();
            break;
        default:
            break;
        }
    }
    
    bool Bee::OutOfBounds()
    {
        return m_outOfBounds;
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