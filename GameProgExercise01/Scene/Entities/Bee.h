#pragma once

#include "DX\DeviceResources.h"
#include "Scene\Entities\FlyingInsect.h"



namespace scene
{
    class Bee  final : public FlyingInsect
    {

    public:
     Bee();
     ~Bee();

        virtual void Render() override;
        virtual void Initialise() override;
        virtual void Update() override;

    private:
        virtual void OnDeviceLost() {}
        virtual void OnDeviceRestored() {}
        
        DirectX::XMVECTOR Velocity = DirectX::XMVECTOR{ 4.0f, 0.0f, 0.0f };
        DirectX::XMVECTOR m_flowerPosition;
        DirectX::XMVECTOR m_waspPosition;
        
        float m_speed;
        bool m_nectar;

        static const UINT NumVertices = 21;
        static const float RadiusToBoundary;
        static const float WaspDangerDistance;
        static const float FlowerCollisionDist;

        float m_thetaPos;
    };
}
