#include "stdafx.h"
#include "Sphere.h"

using namespace DirectX;
using namespace Raytracer;
using namespace Objects;

Sphere::Sphere(XMVECTOR pos, float radius)
{
	position = pos;
	this->radius = radius;
}

void Raytracer::Objects::Sphere::setRadius(float radius)
{
	this->radius = radius;
}

RayHit Sphere::getIntersect(Ray incomingRay)
{
	XMVECTOR& D = incomingRay.direction;
	XMVECTOR& O = incomingRay.origin;
	float a = XMVectorGetX(XMVector3Dot(D,D));
	float b = 2 * XMVectorGetX(XMVector3Dot(D,O-position));
	float c = XMVectorGetX(XMVector3Dot(O - position, O - position)) - powf(radius, 2);

	float discriminant = powf(b, 2) - 4 * a * c;

	if (discriminant < 0) return RayHit();

	discriminant = sqrtf(discriminant);

	float s1 = (-b + discriminant) / (2 * a);
	float s2 = (-b - discriminant) / (2 * a);

	if (s1 > 0 && s1 < s2) {
		XMVECTOR point = O + s1 * D;
		return RayHit(this, s1, point, getNormalAt(point));
	}
	else if (s2 > 0) {
		XMVECTOR point = O + s2 * D;
		return RayHit(this, s2, point, getNormalAt(point));
	}

	return RayHit();
}

XMVECTOR Sphere::getNormalAt(XMVECTOR point)
{
	return (point - position) / radius;
}
