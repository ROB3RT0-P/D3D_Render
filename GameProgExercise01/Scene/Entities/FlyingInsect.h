#pragma once

#include "DX\DeviceResources.h"
#include "Scene\Entity.h"



namespace scene
{
    class FlyingInsect : public Entity
    {
    public:

        FlyingInsect();
        ~FlyingInsect();

        virtual void Render() override;
        virtual void Initialise() override;
        virtual void Update();
        bool OutOfBounds();
        void SeekingNectar();
        void SeekingHome();

    protected: 
        enum class FIMovement
        {
            SeekingNectar,
            SeekingHome,
            None
        };
        
        FIMovement            m_fIState; //member_flying_Insect_State
    
    private:
        virtual void OnDeviceLost() {}
        virtual void OnDeviceRestored() {}

        
        DirectX::XMVECTOR m_flowerPosition;
        DirectX::XMVECTOR m_waspPosition;
        DirectX::XMVECTOR Velocity = DirectX::XMVECTOR{ 4.0f, 0.0f, 0.0f };
        float m_speed;
        float m_timeStep;
        bool m_nectar;
        bool m_outOfBounds;

        static const UINT NumVertices = 21;
        static const float LerpRate;
        static const float Radius;
        float m_thetaPos;

       
    };
}
