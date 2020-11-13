#pragma once

#include "Object.h"
#include "Light.h"

namespace Raytracer {
	const float EPSILON = 0.0001f;

	class Scene;

	class Renderer
	{
	public:
		DirectX::XMVECTOR trace(Scene * scene, Ray * ray, UINT bouncesLeft);
		DirectX::XMVECTOR illuminate(Scene * scene, Objects::Object * object, DirectX::XMVECTOR point, DirectX::XMVECTOR normal, DirectX::XMVECTOR origin);
	private:
		DirectX::XMVECTOR backgroundColour = DirectX::XMVectorSet(0.00f, 0.00f, 0.00f, 1.0f);
	};

}