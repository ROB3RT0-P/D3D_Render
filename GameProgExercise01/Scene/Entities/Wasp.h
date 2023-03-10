#pragma once

#include "DX\DeviceResources.h"
#include "Scene\Entities\FlyingInsect.h"

namespace scene
{
    class Wasp  final : public FlyingInsect
    {
    public:

        Wasp();
        ~Wasp();

        virtual void Render() override;
        virtual void Initialise() override;
        void Update();

    private:
        virtual void OnDeviceLost() {}
        virtual void OnDeviceRestored() {}

        DirectX::XMVECTOR   Velocity = DirectX::XMVECTOR{ 4.0f, 0.0f, 0.0f };
        DirectX::XMVECTOR   m_flowerPosition;

        float               m_speed;
        float               m_timeStep;
        float               m_thetaPos;
        float               m_maxSpeed;
        float               m_scale;
        bool                m_nectar;
        bool                m_outOfBounds;

        static const UINT   m_waitMillisec = 100000;
        static const UINT   NumVertices = 21;
    };
}