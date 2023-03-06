#include "GameProgExercise01.h"
#include "Core.h"
#include "Bee.h"
#include "Scene\Scene.h"
#include "Scene\Entities\Flower.h"
#include "Scene\Entities\Wasp.h"

using namespace DirectX;

namespace scene
{
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

        m_speed = static_cast<float>((utils::Rand() % 10000) / 10000.0f); // Gives float 0.0 - 1.0f
        m_speed *= MaxSpeed / 100;

        m_nectar = false;
        
        //Tell bee to collect nectar
        m_state = Movement::SeekingNectar;

        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();
        Flower* const flower = scene->GetRandFlower();
        m_flowerPosition = flower->GetPosition();

        Wasp* const wasp = scene->GetRandWasp();
        m_waspPosition = wasp->GetPosition();

        float zPos = static_cast<float>(utils::Rand() % 5);
        DirectX::XMVECTOR startPos = DirectX::XMVECTOR{ -15.0f, 3.0f, zPos };
        SetPosition( startPos );

        const DX::DeviceResources* const deviceResources = core->GetDeviceResources();

        HRESULT hr = 0;

        const float scale = 0.1f;

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
            { { 1.01f, 0.0f,  0.4f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },     //1
            { { 1.01f, 0.0f,  0.6f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },     //2
            { { 1.01f, 1.01f,  0.4f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },     //3
            { { 1.01f, 1.01f,  0.6f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },     //4
            { { -0.01f, 1.01f,  0.4f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },     //5
            { { -0.01f, 1.01f,  0.6f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },     //6
            { { -0.01f, 0.0f,  0.4f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },     //7
            { { -0.01f, 0.0f,  0.6f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } }      //8

            //Stripe - other dir
            /*
            { { 0.4f, 0.0f,  -0.01f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },    //1
            { { 0.6f, 0.0f,  -0.01f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },    //2
            { { 0.4f, 1.01f, -0.01f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },    //3
            { { 0.6f, 1.01f, -0.01f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },    //4
            { { 0.4f, 1.01f,  1.01f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },    //5
            { { 0.6f, 1.01f,  1.01f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },    //6
            { { 0.4f, 0.0f,   1.01f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } },    //7
            { { 0.6f, 0.0f,   1.01f, 1.0f },{ 0.0f, 0.0f, 0.0f, 1.0f } }     //8
            */
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

  
    
    void Bee::PosIter()
    {
        m_timeStep = utils::Timers::GetFrameTime();

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


        DirectX::XMVECTOR vecToWasp = m_waspPosition - m_position;
        DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(vecToWasp);
        float distanceAsFloat = *checkPosLen.m128_f32;
        if (distanceAsFloat < 3.0f)
        {
            m_state = Movement::AvoidingWasp;
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

        DirectX::XMVECTOR lerpDir = DirectX::XMVectorLerp(m_orientationAsVector, dirFromWasp, 0.12f * m_timeStep);
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

            float xBounds = 14.9f;

            DirectX::XMVECTOR curPos = m_position;

            float randZ = static_cast<float>(utils::Rand() % 5);
            DirectX::XMVECTOR leaveDir = DirectX::XMVECTOR{ 15.0f, 3.0f, randZ };

            DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(leaveDir, m_position);
            DirectX::XMVECTOR normalisedDir = DirectX::XMVector3Normalize(direction);
            DirectX::XMVECTOR BoundaryVelocity = DirectX::XMVectorScale(normalisedDir, m_speed * 80);

            DirectX::XMVECTOR newPos = DirectX::XMVectorScale(BoundaryVelocity, m_timeStep);
            m_position.v = DirectX::XMVectorAdd(m_position.v, newPos);

            SetPosition(m_position.v);

            if (m_position.f[0] >= xBounds)
            {
                m_outOfBounds = true;
            }
        }
        else 
        {
            m_state = Movement::SeekingNectar;
        }

        /*
  if (bee < dist to wasp)
  {
      m_state = AvoidingWasp;
  }else
  {

  }*/
    }


    void Bee::Update()
    {
        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();
        Wasp* const wasp = scene->GetRandWasp();
        m_waspPosition = wasp->GetPosition();

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

        PosIter();
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

        // Draw triangle.
        context->Draw(NumVertices, 0);
    }
}