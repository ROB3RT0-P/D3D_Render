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
        static const UINT PetalNumVertices = 3;
        static const UINT NumPetals = 8;
        const float PetalHeight = 2.0f;
        float NectarLevel = 0.0f;
        float CollisionDist = 0.2f;

        virtual void Render() override;
        virtual void Initialise() override;
        virtual void Update();

        float GetNectarFloat() const
        {
            return NectarLevel;
        }

    private:
        virtual void OnDeviceLost() {}
        virtual void OnDeviceRestored() {}

        static const float Spacing;
        static const float FlowerScale;
    };
}