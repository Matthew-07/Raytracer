#pragma once
#include "Light.h"

namespace Raytracer {
    namespace Lights {

        class PointLight :
            public Light
        {
            LightContributions sample(Scene* scene, DirectX::XMVECTOR origin, DirectX::XMVECTOR normal, DirectX::XMVECTOR view, float alpha);
        };

    }
}
