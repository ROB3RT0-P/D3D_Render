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
        void AvoidingWasp();


    protected: 
        enum class FIMovement
        {
            SeekingNectar,
            SeekingHome,
            AvoidingWasp
        };
        
        FIMovement            m_fIState; //member_flying_Insect_State
        UINT                  m_padding[3];
    
    private:
        virtual void OnDeviceLost() {}
        virtual void OnDeviceRestored() {}

        
        DirectX::XMVECTOR m_flowerPosition;
        DirectX::XMVECTOR m_waspPosition;

        float m_speed;
    
        bool m_nectar;
        bool m_outOfBounds;

        static const UINT NumVertices = 21;
        static const float LerpRate;
        
        static const float FlowerCollisionDist;
        static const float ExitCollisionDist;
        static const float WaspSafeDistance;
        static const float MaxSpeed;
        static const float RadiusToBoundary;
        float m_radiusPos;
    };
}
