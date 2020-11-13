#include "Object.h"
#include "Light.h"
#include "Renderer.h"
#include "Camera.h"

#pragma once
namespace Raytracer {

	class Scene
	{
	public:
		Scene(float fov, float aspectRatio, UINT pxWidth, UINT pxHeight, UINT numBounces);

		IWICBitmap* renderScene(LPCWSTR path);
		RayHit getClosestIntersection(Ray ray);
		
		void addLight(Lights::Light *p);
		void addObject(Objects::Object *s);

		void setAmbientLighting(DirectX::XMVECTOR ambient);

		DirectX::XMVECTOR toneMap(DirectX::XMVECTOR colour);

		DirectX::XMVECTOR getAmbientLighting();
		std::list< Raytracer::Lights::Light*>& getSceneLights();
	private:
		UINT outputWidth = 1920/2;
		UINT outputHeight = 1080/2;

		float viewPlaneDistance = 1.f;

		DirectX::XMVECTOR ambientLighting;
		std::list<Raytracer::Lights::Light*>	scene_lights;
		std::list<Raytracer::Objects::Object*>	scene_objects;

		DirectX::XMVECTOR backgroundColour;

		// Sampling settings
		UINT numberOfBounces = 2;
		UINT samplesPerPixel = 10;

		Camera camera;
		Renderer renderer;
	};
}

