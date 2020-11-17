#include "stdafx.h"
#include "SphericalLight.h"

#include "Ray.h"
#include "Renderer.h"
#include "Scene.h"

using namespace DirectX;
using namespace Raytracer;
using namespace Lights;

LightContributions Raytracer::Lights::SphericalLight::sample(Scene* scene, DirectX::XMVECTOR origin, DirectX::XMVECTOR normal, DirectX::XMVECTOR view, float alpha)
{

    LightContributions result;
    for (int i = 0; i < numberOfSamples; i++) {
        XMVECTOR offset = radius * XMVector3Normalize(XMVectorSet(rand(),rand(),rand(),0));
        if (XMVectorGetX(XMVector3Dot(offset, normal)) > 0) offset *= -1;
        rayContributions(scene, origin, normal, view, alpha, position+offset, colour, intensity / numberOfSamples, result);
    }
    return result;
}

void Raytracer::Lights::SphericalLight::setRadius(float radius)
{
    this->radius = radius;
}
