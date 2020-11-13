#include "stdafx.h"
#include "Light.h"

#include "Renderer.h"
#include "Scene.h"

using namespace DirectX;

void Raytracer::Lights::Light::setColour(XMVECTOR colour)
{
	this->colour = colour;
    totalColour = colour * intensity;
}

void Raytracer::Lights::Light::setIntensity(float intensity)
{
	this->intensity = intensity;
    totalColour = colour * intensity;
}

void Raytracer::Lights::Light::rayContributions(
	Scene* scene,
	XMVECTOR origin,
	XMVECTOR normal,
	XMVECTOR view,
	float alpha,
	XMVECTOR lightPosition,
    XMVECTOR lightIntensity,
	LightContributions& contributions)
{
    XMVECTOR L = XMVector3Normalize(lightPosition - origin);
    // Cast shadow ray
    Ray shadowRay = Ray(origin + normal * EPSILON, L);

    float distance = XMVectorGetX(XMVector3Length(lightPosition - origin));

    RayHit intersection = scene->getClosestIntersection(shadowRay);
    if (intersection.distance > distance) {

        XMVECTOR incidentColour = lightIntensity / (4 * g_XMPi * powf(distance, 2));
        contributions.diff += incidentColour * max(0.0f, XMVectorGetX(XMVector3Dot(normal, L)));
        contributions.spec += incidentColour * max(0.0f, powf(XMVectorGetX(XMVector3Dot(XMVector3Reflect(L, normal), view)), alpha));
    }
    else {
        return;
    }
}



void Raytracer::Lights::Light::setPosition(XMVECTOR position) {
	this->position = position;
}