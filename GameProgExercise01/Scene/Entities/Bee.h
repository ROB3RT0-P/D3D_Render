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

    private:

        virtual void OnDeviceLost() {}
        virtual void OnDeviceRestored() {}
    };

}
