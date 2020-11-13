#include "stdafx.h"
#include "Ray.h"

#include "Object.h"

using namespace DirectX;
using namespace Raytracer;
using namespace Objects;

Raytracer::RayHit::RayHit()
{
	distance = POSITIVE_INFINITY;
	location = XMVECTOR();
	normal = XMVECTOR();
}

Raytracer::RayHit::RayHit(Object* collider, float distance, DirectX::XMVECTOR location, DirectX::XMVECTOR normal)
{
	this->collider = collider;
	this->distance = distance;
	this->location = location;
	this->normal = normal;
	
}

Raytracer::Ray::Ray(DirectX::XMVECTOR origin, DirectX::XMVECTOR direction)
{
	this->origin = origin;
	this->direction = direction;
}
