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

void Raytracer::Objects::Plane::prepare()
{
	normal = XMVector3Normalize(normal);
	direction = XMVector3Normalize(direction);
	perpDirection = XMVector3Cross(normal, direction);
}

void Raytracer::Objects::Plane::setNormal(XMVECTOR normal)
{
	this->normal = normal;
}

void Raytracer::Objects::Plane::setNormalX(float x)
{
	normal = XMVectorSetX(normal, x);
}

void Raytracer::Objects::Plane::setNormalY(float y)
{
	normal = XMVectorSetY(normal, y);
}

void Raytracer::Objects::Plane::setNormalZ(float z)
{
	normal = XMVectorSetZ(normal, z);
}

void Raytracer::Objects::Plane::setDirectionX(float x)
{
	direction = XMVectorSetX(direction, x);
}

void Raytracer::Objects::Plane::setDirectionY(float y)
{
	direction = XMVectorSetX(direction, y);
}

void Raytracer::Objects::Plane::setDirectionZ(float z)
{
	direction = XMVectorSetX(direction, z);
}

void Raytracer::Objects::Plane::setDirection(XMVECTOR normal){
		this->direction = direction;	
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
	/*float tripleProduct = XMVectorGetX(XMVector3Dot(normal,XMVector3Cross(direction,perpDirection)));

	float x = XMVectorGetX(XMVector3Dot(position, XMVector3Cross(direction, normal))) / tripleProduct;
	float y = XMVectorGetX(XMVector3Dot(position, XMVector3Cross(perpDirection, normal))) / tripleProduct;

	return ((fmod(x + 1000000.2, 0.2f) < 0.1f ? false : true) == (fmod(y + 1000000.2, 0.2f) < 0.1f ? false : true) ?  1.0f : 0.7f) * diff_c;*/

	return diff_c;
}
