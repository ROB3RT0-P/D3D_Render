#pragma once

#include "DX\DeviceResources.h"
#include "Scene\Entity.h"


namespace scene
{

    class Flower  final : public Entity
    {
    public:
        Flower(const UINT x, const UINT z );
        static const UINT NumVertices = 9;
        static UINT NumPetals;

        virtual void Render() override;
        virtual void Initialise() override;

    private:

        virtual void OnDeviceLost() {}
        virtual void OnDeviceRestored() {}
    };

}