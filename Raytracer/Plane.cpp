#include "stdafx.h"
#include "Plane.h"

#include "stdafx.h"
#include "Plane.h"

using namespace DirectX;
using namespace Raytracer;
using namespace Objects;

Plane::Plane(XMVECTOR pos, XMVECTOR normal, XMVECTOR direction)
{
	position = pos;
	this->normal = XMVector3Normalize(normal);
	this->direction = XMVector3Normalize(direction);
	perpDirection = XMVector3Cross(this->normal, this->direction);
}

RayHit Plane::getIntersect(Ray incomingRay)
{
	float s = XMVectorGetX(XMVector3Dot(position - incomingRay.origin, normal)) / XMVectorGetX(XMVector3Dot(incomingRay.direction, normal));

	if (s >= 0) {
		XMVECTOR point = incomingRay.origin + s * incomingRay.direction;
		return RayHit(this, s, point, getNormalAt(point));
	}
	return RayHit();
}

XMVECTOR Plane::getNormalAt(XMVECTOR point)
{
	return normal;
}

XMVECTOR Plane::getDiffuseColour(XMVECTOR position)
{
	float tripleProduct = XMVectorGetX(XMVector3Dot(normal,XMVector3Cross(direction,perpDirection)));

	float x = XMVectorGetX(XMVector3Dot(position, XMVector3Cross(direction, normal))) / tripleProduct;
	float y = XMVectorGetX(XMVector3Dot(position, XMVector3Cross(perpDirection, normal))) / tripleProduct;

	return ((fmod(x + 1000000, 0.1f) < 0.05f ? false : true) == (fmod(y + 1000000, 0.1f) < 0.05f ? false : true) ?  0.8f : 0.2f) * diff_c;
}

XMVECTOR Plane::getSpecularColour(XMVECTOR position)
{
	return XMVECTOR();
}
