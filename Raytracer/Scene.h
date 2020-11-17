#include "Object.h"
#include "Light.h"

#pragma once
namespace Raytracer {

	class Scene
	{
	public:
		void prepare(){
			for (Objects::Object* obj : scene_objects) {
				obj->prepare();
			}
		}

		void loadFromFile(LPCWSTR path);

		RayHit getClosestIntersection(Ray ray);
		
		void addLight(Lights::Light *p);
		void addObject(Objects::Object *s);

		void setAmbientColour(DirectX::XMVECTOR ambient);
		void setAmbientIntensity(float intensity);

		DirectX::XMVECTOR getAmbientLighting();
		std::list< Raytracer::Lights::Light*>& getSceneLights();
	private:
		DirectX::XMVECTOR ambientLighting;
		float ambientIntensity = 1.f;
		std::list<Raytracer::Lights::Light*>	scene_lights;
		std::list<Raytracer::Objects::Object*>	scene_objects;

		DirectX::XMVECTOR backgroundColour;
	};
}

