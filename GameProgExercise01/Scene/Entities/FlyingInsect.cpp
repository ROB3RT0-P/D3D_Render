#include "GameProgExercise01.h"
#include "Core.h"
#include "FlyingInsect.h"
#include "Scene\Scene.h"
#include "Scene\Entities\Flower.h"
#include "Scene\Entities\Wasp.h"
#include "Scene\Entity.h"

using namespace DirectX;

namespace scene
{
    const float FlyingInsect::RadiusToBoundary = 10.0f;
    const float FlyingInsect::LerpRate = 0.9f;
    const float FlyingInsect::FlowerCollisionDist = 0.2f;
    const float FlyingInsect::ExitCollisionDist = 0.1f;
    const float FlyingInsect::WaspSafeDistance = 10.0f;
    const float FlyingInsect::MaxSpeed = 0.4f;

    float lerpSpeed = 10.0f; // Make this a static const member - call Max if that's what it is
    // or make local?

    FlyingInsect::FlyingInsect() :
        m_fIState( FIMovement::SeekingNectar ),
        m_nectar(false),
        m_outOfBounds(false),
        m_speed( 0.0f )
    {
    
    }

    FlyingInsect::~FlyingInsect()
    {
    }

    void FlyingInsect::Initialise()
    {
        Entity::Initialise();

        m_radiusPos = static_cast<float>((utils::Rand() % 10000) / 10000.0f) * DirectX::XM_2PI; // Gives float 0.0 - 1.0f
        m_speed = static_cast<float>((utils::Rand() % 10000) / 10000.0f); // Gives float 0.0 - 1.0f
        m_speed *= MaxSpeed;
    }

    void FlyingInsect::SeekingNectar()
    {
        float timeStep = utils::Timers::GetFrameTime(); 
        const Core* const core = Core::Get();
        Scene* scene = core->GetScene();
        Flower* const flower = scene->GetHighestNectarFlower();
        m_flowerPosition = flower->GetPosition();

        if (!m_nectar)
        {
            float distanceAsFloat = PosUpdate(m_flowerPosition);

            if ( distanceAsFloat < FlowerCollisionDist )
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
        if (m_nectar) 
        {
            DirectX::XMVECTOR leavePos = DirectX::XMVECTOR{ DirectX::XMScalarSin(m_radiusPos) * RadiusToBoundary, 3.0f, DirectX::XMScalarCos(m_radiusPos) * RadiusToBoundary };
            float distanceToExitPoint = PosUpdate(leavePos);
            if ( distanceToExitPoint <= ExitCollisionDist )
            {
                m_outOfBounds = true;
            }
        }
        else
        {
            m_fIState = FIMovement::SeekingNectar;
        }
    }

    void FlyingInsect::AvoidingWasp()
    {
        // Calculate the inverse velocity of the wasp.
        float timeStep = utils::Timers::GetFrameTime();
        DirectX::XMVECTOR vecToWasp = m_position - m_waspPosition;
        DirectX::XMVECTOR checkPosLen = DirectX::XMVector3LengthEst(vecToWasp);
        XMVECTOR vecFromWasp = XMVectorNegate(vecToWasp);//
        XMVECTOR dirFromWasp = XMVector3Normalize(vecToWasp);
        DirectX::XMVECTOR waspVelocity = DirectX::XMVectorScale(dirFromWasp, m_speed);

        // This is doing the same thing as above, which one is it?
        DirectX::XMVECTOR lerpDir = DirectX::XMVectorLerp(m_orientationAsVector, dirFromWasp, lerpSpeed * timeStep);
        SetOrientation(lerpDir);
        SetPosition(m_position + (DirectX::XMVectorScale(lerpDir, m_speed)));

        // Check bee is safe distance from wasp.
        float distanceAsFloat = *checkPosLen.m128_f32;
        if (distanceAsFloat > WaspSafeDistance)
        {
            FlyingInsect::m_fIState = FlyingInsect::FIMovement::SeekingNectar;
        }
    }

    float FlyingInsect::PosUpdate(DirectX::XMVECTOR trajectory)
    {
        float timeStep = utils::Timers::GetFrameTime();
        DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(trajectory, m_position);
        DirectX::XMVECTOR normalisedDir = DirectX::XMVector3Normalize(direction);
        DirectX::XMVECTOR lerpDir = DirectX::XMVectorLerp(m_orientationAsVector, normalisedDir, LerpRate * timeStep);
        SetPosition(m_position + (DirectX::XMVectorScale(lerpDir, m_speed)));
        SetOrientation(lerpDir);

        DirectX::XMVECTOR distanceToExitPointVec = DirectX::XMVector3LengthEst(direction);
        float distance = *distanceToExitPointVec.m128_f32;

        return distance;
    }

    void FlyingInsect::Update()
    {
        Entity::Update();

        switch (m_fIState)
        {
        case FIMovement::SeekingNectar:
            SeekingNectar();
            break;
        case FIMovement::SeekingHome:
            SeekingHome();
            break;
        case FIMovement::AvoidingWasp:
            AvoidingWasp();
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