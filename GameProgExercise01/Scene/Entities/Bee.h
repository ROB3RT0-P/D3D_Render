#pragma once

#include "DX\DeviceResources.h"
#include "Scene\Entities\FlyingInsect.h"



namespace scene
{
    class Bee  final : public FlyingInsect
    {
        enum class Movement
        {
            SeekingNectar,
            AvoidingWasp,
            SeekingHome
        };       

    public:

     Bee();
     ~Bee();

        virtual void Render() override;
        virtual void Initialise() override;
        void Update();
        void PosIter();
        bool OutOfBounds();
        void SeekingNectar();
        void AvoidingWasp();
        void SeekingHome();

    private:
        virtual void OnDeviceLost() {}
        virtual void OnDeviceRestored() {}
        
        DirectX::XMVECTOR Velocity = DirectX::XMVECTOR{ 4.0f, 0.0f, 0.0f };
        DirectX::XMVECTOR m_flowerPosition;
        DirectX::XMVECTOR m_waspPosition;
        
        float m_speed;
        float m_timeStep;
        bool m_nectar;
        bool m_outOfBounds;

        static const UINT NumVertices = 21;
        static const float Radius;
        float m_thetaPos;

        Movement            m_state;
    };
}
