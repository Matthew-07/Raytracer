#include "stdafx.h"
#include "Camera.h"

#include "Ray.h"

using namespace DirectX;
using namespace Raytracer;

Raytracer::Camera::Camera(float fov, float aspectRatio, UINT pxWidth, UINT pxHeight)
{
	this->fov = fov;
	this->aspectRatio = aspectRatio;
	this->pxWidth = pxWidth;
	this->pxHeight = pxHeight;
	this->width = focalDistance * 2 * tan(XMConvertToRadians(this->fov) / 2);;
	this->height = this->width / this->aspectRatio;
	stepX = width / pxWidth;
	stepY = height / pxHeight;
}

Ray Raytracer::Camera::castRay(int x, int y)
{
	XMVECTOR origin = XMVectorSet(fRand(-depthOfField, depthOfField), fRand(-depthOfField, depthOfField), 0.f, 0.f);
	XMVECTOR pos = XMVectorSet(x * stepX + (0.5 * (stepX - width)), -(y * stepY + (0.5 * stepY - (height/2))), focalDistance, 0.f);
	XMVECTOR aaOffset = XMVectorSet(fRand(-stepX/2, stepX/2), fRand(-stepY / 2, stepY / 2), 0.f, 0.f);
	return Ray(origin, XMVector3Normalize((pos+aaOffset) - origin));
}
