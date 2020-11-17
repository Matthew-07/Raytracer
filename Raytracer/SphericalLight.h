#pragma once
#include "Light.h"

namespace Raytracer {
    namespace Lights {

        class SphericalLight :
            public Light
        {
        public:
            SphericalLight() {}
            LightContributions sample(Scene* scene, DirectX::XMVECTOR origin, DirectX::XMVECTOR normal, DirectX::XMVECTOR view, float alpha);
            void setRadius(float radius);

        private:
            float radius = 0.4f;
            UINT numberOfSamples = 20;
        };

    }
}
