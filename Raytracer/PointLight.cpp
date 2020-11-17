#include "stdafx.h"
#include "PointLight.h"

#include "Ray.h"
#include "Renderer.h"
#include "Scene.h"

using namespace DirectX;
using namespace Raytracer;
using namespace Lights;

LightContributions Raytracer::Lights::PointLight::sample(Scene* scene, DirectX::XMVECTOR origin, DirectX::XMVECTOR normal, DirectX::XMVECTOR view, float alpha)
{
    LightContributions result;
    rayContributions(scene, origin, normal, view, alpha, position, colour, intensity, result);
    return result;
}
