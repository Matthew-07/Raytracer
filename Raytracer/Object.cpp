#include "stdafx.h"
#include "Object.h"

using namespace DirectX;
using namespace Raytracer;
using namespace Objects;

void Object::setPosition(XMVECTOR pos)
{
	position = pos;
}

void Object::setDiffuseColour(XMVECTOR colour)
{
	diff_c = colour;
}

void Object::setSpecularColour(XMVECTOR colour)
{
	spec_c = colour;
}

void Object::setPhongKD(float kd)
{
	k_d = kd;
}

void Object::setPhongKS(float ks)
{
	k_s = ks;
}

void Object::setAlpha(float a)
{
	alpha = a;
}

void Object::setReflectivity(float reflectivity)
{
	this->reflectivity = reflectivity;
}

XMVECTOR Object::getPosition()
{
	return position;
}

XMVECTOR Object::getDiffuseColour(DirectX::XMVECTOR position)
{
	return diff_c;
}

XMVECTOR Object::getSpecularColour(DirectX::XMVECTOR position)
{
	return spec_c;
}

float Object::getPhongKD()
{
	return k_d;
}

float Object::getPhongKS()
{
	return k_s;
}

float Object::getAlpha()
{
	return alpha;
}

float Object::getRelectivity()
{
	return reflectivity;
}

