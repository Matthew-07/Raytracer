#include "stdafx.h"
#include "Renderer.h"

#include "Scene.h"

using namespace DirectX;
using namespace Raytracer;
using namespace Objects;
using namespace Lights;

XMVECTOR Renderer::trace(Scene* scene, Ray* ray, UINT bouncesLeft)
{
    RayHit intersect = scene->getClosestIntersection(*ray);
    if (intersect.collider == NULL) return backgroundColour;

    XMVECTOR directIllumination = illuminate(scene, intersect.collider, intersect.location, intersect.normal, ray->origin);

    float reflectivity = intersect.collider->getRelectivity();

    if (bouncesLeft == 0 || reflectivity == 0) {
        return directIllumination;
    }
    else {
        XMVECTOR R = XMVector3Reflect(-ray->direction, intersect.normal);
        Ray reflectedRay = Ray(intersect.location + (intersect.normal * EPSILON), -R);
        XMVECTOR reflectedIllumination = trace(scene, &reflectedRay, bouncesLeft - 1);

        directIllumination *= (1.0f - reflectivity);
        reflectedIllumination *= reflectivity;

        return directIllumination + reflectedIllumination;
    }

}

XMVECTOR Renderer::illuminate(Scene* scene, Object* object, XMVECTOR point, XMVECTOR normal, XMVECTOR origin)
{
    XMVECTOR c_diff = object->getDiffuseColour(point);
    XMVECTOR c_spec = object->getSpecularColour(point);
    
    float k_d = object->getPhongKD();
    float k_s = object->getPhongKS();

    // Ambient Component
    XMVECTOR returnColour = c_diff * scene->getAmbientLighting();

    for (auto light : scene->getSceneLights()) {
        LightContributions components = light->sample(scene, point, normal, XMVector3Normalize(origin - point), object->getAlpha());

        // Diffuse Component
        returnColour += k_d * c_diff * components.diff;
        
        // Specular Component
        returnColour += k_s * c_spec * components.spec;
    }

    return returnColour;
}
