#pragma once

#include "DX\DeviceResources.h"
#include "Scene\Entity.h"


namespace scene
{ 

    class Ground  final : public Entity
    {
    public:
        static const UINT NumVertices = 6;

        virtual void Render() override;
        virtual void Initialise() override;

    private:
        virtual void OnDeviceLost() {}
        virtual void OnDeviceRestored() {}
    };

}
