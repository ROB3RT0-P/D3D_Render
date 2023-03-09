#pragma once

#include "DX\DeviceResources.h"
#include "Scene\Entity.h"



namespace scene
{
    class Wasp  final : public Entity
    {
        enum class Movement
        {
            SeekingNectar,
            SeekingHome
        };

    public:

        Wasp();
        ~Wasp();

        virtual void Render() override;
        virtual void Initialise() override;
        void Update();
        void PosIter();
        bool OutOfBounds();
        void SeekingNectar();
        void SeekingHome();

    private:
        virtual void OnDeviceLost() {}
        virtual void OnDeviceRestored() {}

        DirectX::XMVECTOR   Velocity = DirectX::XMVECTOR{ 4.0f, 0.0f, 0.0f };
        DirectX::XMVECTOR   m_flowerPosition;
        DirectX::XMVECTOR   m_direction;
        DirectX::XMVECTOR   m_normalisedDir;
        DirectX::XMVECTOR   m_flowerVelocity;
        DirectX::XMVECTOR   m_checkPos;
        DirectX::XMVECTOR   m_checkPosLen;

        float               m_speed;
        float               m_timeStep;
        bool                m_nectar;
        bool                m_outOfBounds;
        float               m_thetaPos;

        static const UINT   m_waitMillisec = 100000;
        static const UINT   NumVertices = 21;

        Movement            m_state;
    };
}