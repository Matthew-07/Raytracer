#pragma once

#include "Object.h"
#include "Light.h"

#include "Camera.h"

namespace Raytracer {
	const float EPSILON = 0.0001f;

	class Scene;

	class Renderer
	{
	public:
		Renderer(float fov, UINT pxWidth, UINT pxHeight, UINT samplesPerPixel, UINT numBounces);

		IWICBitmap* renderScene(LPCWSTR path, Scene *scene);
	private:
		// Sampling settings
		UINT numberOfBounces = 2;
		UINT samplesPerPixel = 1;

		UINT outputWidth = 1920;
		UINT outputHeight = 1080;

		float viewPlaneDistance = 1.f;

		Camera camera;

		DirectX::XMVECTOR toneMap(DirectX::XMVECTOR colour);

		DirectX::XMVECTOR backgroundColour = DirectX::XMVectorSet(0.00f, 0.00f, 0.00f, 1.0f);

		DirectX::XMVECTOR trace(Scene* scene, Ray* ray, UINT bouncesLeft);
		DirectX::XMVECTOR illuminate(Scene* scene, Objects::Object* object, DirectX::XMVECTOR point, DirectX::XMVECTOR normal, DirectX::XMVECTOR origin);
	};
}