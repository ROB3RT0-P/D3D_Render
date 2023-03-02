#pragma once

#include "DX\DeviceResources.h"
#include "Scene\Entity.h"



namespace scene
{

    class Bee  final : public Entity
    {
    public:
        static const UINT NumVertices = 21;

        virtual void Render() override;
        virtual void Initialise() override;
        void Update();
        void PosIter();

        bool OutOfBounds();

        DirectX::XMVECTOR Velocity = DirectX::XMVECTOR{ 4.0f, 0.0f, 0.0f };

        const float speed = utils::Rand() % (5 - 1) + 1;
        
    private:
        bool m_outOfBounds = false;
        virtual void OnDeviceLost() {}
        virtual void OnDeviceRestored() {}
    };
}
