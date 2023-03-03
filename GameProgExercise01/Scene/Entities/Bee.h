#pragma once

#include "DX\DeviceResources.h"
#include "Scene\Entity.h"



namespace scene
{
   

    class Bee  final : public Entity
    { 
       

    public:

     Bee();
     ~Bee();

        virtual void Render() override;
        virtual void Initialise() override;
        void Update();
        void PosIter();
        bool OutOfBounds();

    private:
        virtual void OnDeviceLost() {}
        virtual void OnDeviceRestored() {}
        
        DirectX::XMVECTOR Velocity = DirectX::XMVECTOR{ 4.0f, 0.0f, 0.0f };
        DirectX::XMVECTOR m_flowerPosition;
        
        float m_speed;
        float m_timeStep;
        bool m_nectar;
        bool m_outOfBounds;

        static const UINT NumVertices = 21;
    };
}
