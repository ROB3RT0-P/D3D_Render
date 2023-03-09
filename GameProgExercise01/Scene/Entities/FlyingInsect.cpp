#include "GameProgExercise01.h"
#include "Core.h"
#include "FlyingInsect.h"
#include "Scene\Scene.h"
#include "Scene\Entities\Flower.h"
#include "Scene\Entities\Wasp.h"

using namespace DirectX;

namespace scene
{
    const float FlyingInsect::Radius = 15.0f;
    const float FlyingInsect::LerpRate = 0.75f;
    static const float MaxSpeed = .1f;

    FlyingInsect::FlyingInsect() :
        m_fIState( FIMovement::None ),
        m_nectar(false),
        m_outOfBounds(false)
    {
        DirectX::XMVECTORF32 newPos = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
    }

    FlyingInsect::~FlyingInsect()
    {
    }

    void FlyingInsect::Initialise()
    {
        Entity::Initialise();
        m_thetaPos = static_cast<float>((utils::Rand() % 10000) / 10000.0f) * DirectX::XM_2PI;; // Gives float 0.0 - 1.0f
        m_speed = static_cast<float>((utils::Rand() % 10000) / 10000.0f); // Gives float 0.0 - 1.0f
        m_speed *= MaxSpeed;
        
        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();
        Flower* const flower = scene->GetRandFlower();
        m_flowerPosition = flower->GetPosition();
    }

    void FlyingInsect::SeekingNectar()
    {
        m_timeStep = utils::Timers::GetFrameTime();
        
        if (!m_nectar)
        {
            DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(m_flowerPosition, m_position);
            DirectX::XMVECTOR normalisedDir = DirectX::XMVector3Normalize(direction);
            DirectX::XMVECTOR flowerVelocity = DirectX::XMVectorScale(normalisedDir, m_speed);

            DirectX::XMVECTORF32 newPos = DirectX::XMVECTORF32{ 0.0f, 0.0f, 0.0f };
            //NewPos = DirectX::XMVectorScale( Velocity , timeStep );
            //newPos.v = DirectX::XMVectorScale(flowerVelocity, m_timeStep);
            //newPos.v += m_position;

            DirectX::XMVECTOR lerpDir = DirectX::XMVectorLerp(m_orientationAsVector, direction, LerpRate * m_timeStep);
            SetOrientation(lerpDir);
            SetPosition(m_position + (DirectX::XMVectorScale(lerpDir, m_speed)));

            DirectX::XMVECTOR checkPos = m_position - m_flowerPosition;
            DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(checkPos);
            float distanceAsFloat = *checkPosLen.m128_f32;
            if (distanceAsFloat < 0.2f)
            {
                m_nectar = true;
            }
        }
        else
        {
            m_fIState = FIMovement::SeekingHome;
        }
    }

    void FlyingInsect::SeekingHome()
    {
        if (m_nectar) {

            m_timeStep = utils::Timers::GetFrameTime();

            DirectX::XMVECTOR leavePos = DirectX::XMVECTOR{ DirectX::XMScalarSin(m_thetaPos) * Radius, 3.0f, DirectX::XMScalarCos(m_thetaPos) * Radius };

            DirectX::XMVECTOR directionToExitPoint = DirectX::XMVectorSubtract(leavePos, m_position);
            DirectX::XMVECTOR distanceToExitPointVec = DirectX::XMVector3LengthEst(directionToExitPoint);
            float distanceToExitPoint = *distanceToExitPointVec.m128_f32;
            DirectX::XMVECTOR normalisedDir = DirectX::XMVector3Normalize(directionToExitPoint);
            //DirectX::XMVECTOR desiredVelocity = DirectX::XMVectorScale(normalisedDir, m_speed);

            //DirectX::XMVECTOR delta = DirectX::XMVectorScale(desiredVelocity, m_timeStep);
            //m_position.v = DirectX::XMVectorAdd(m_position.v, delta);


            SetPosition(m_position + (DirectX::XMVectorScale(normalisedDir, m_speed)));

            //SetPosition(m_position.v);

            if (distanceToExitPoint <= 0.1f)
            {
                m_outOfBounds = true;
            }
        }
        else
        {
            m_fIState = FIMovement::SeekingNectar;
        }
    }


    void FlyingInsect::Update()
    {
        Entity::Update();


        //Check
       /* DirectX::XMVECTOR checkPos = m_position - m_flowerPosition;
        DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(checkPos);
        float distanceAsFloat = *checkPosLen.m128_f32;
        if (distanceAsFloat < 0.2f)
        {
            m_nectar = true;
            FlyingInsect::m_fIState = FlyingInsect::FIMovement::SeekingHome;
        }*/
        switch (m_fIState)
        {
        case FIMovement::SeekingNectar:
            SeekingNectar();
            break;
        case FIMovement::SeekingHome:
            SeekingHome();
            break;
        case FIMovement::None:
            break;
        default:
            break;
        }
    }

    bool FlyingInsect::OutOfBounds()
    {
        return m_outOfBounds;
    }

    void FlyingInsect::Render()
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