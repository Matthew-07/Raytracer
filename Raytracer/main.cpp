#include "stdafx.h"

#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "PointLight.h"
#include "SphericalLight.h"

const UINT numberOfBounces = 100;

int main() {
	srand(time(0));

	Raytracer::Scene scene = Raytracer::Scene(45.f, 16.f / 9.f, 1920/2, 1080/2, numberOfBounces);
	scene.setAmbientLighting(DirectX::XMVectorSet(0.1f, 0.1f, 0.1f, 0.f));

	Raytracer::Lights::SphericalLight light1;
	light1.setPosition(DirectX::XMVectorSet(1, 3, 2, 0));
	light1.setColour(DirectX::XMVectorSet(1.f, 1.f, 1.f, 0.f));
	light1.setIntensity(80.f);

	Raytracer::Objects::Sphere sphere1 = Raytracer::Objects::Sphere(DirectX::XMVectorSet(0.55f, -0.16f, 3.5f, 0.f), 0.5f);
	sphere1.setDiffuseColour(DirectX::XMVectorSet(0.1f, 1.f, 0.5f, 0.f));
	sphere1.setSpecularColour(DirectX::XMVectorSet(0.1f, 1.f, 0.5f, 0.f));

	Raytracer::Objects::Sphere sphere2 = Raytracer::Objects::Sphere(DirectX::XMVectorSet(-0.55f, 0.f, 5.f, 0.f), 0.9f);
	sphere2.setDiffuseColour(DirectX::XMVectorSet(1.f, 0.5f, 0.5f, 0.f));
	sphere2.setSpecularColour(DirectX::XMVectorSet(1.f, 0.5f, 0.5f, 0.f));

	Raytracer::Objects::Sphere sphere3 = Raytracer::Objects::Sphere(DirectX::XMVectorSet(-0.35f, -0.3f, 2.5f, 0.f), 0.25f);
	sphere3.setDiffuseColour(DirectX::XMVectorSet(0.85f, 0.55f, 0.1f, 0.f));
	sphere3.setSpecularColour(DirectX::XMVectorSet(0.85f, 0.55f, 0.1f, 0.f));

	Raytracer::Objects::Plane plane1 = Raytracer::Objects::Plane(
		DirectX::XMVectorSet(0.f, -1.f, 4.7f, 0.f),
		DirectX::XMVectorSet(0.f, 4.2f, -2.2f, 0.f),
		DirectX::XMVectorSet(0.f, -4.2f, -2.2f, 0.f)
		);
	plane1.setDiffuseColour(DirectX::XMVectorSet(0.4f, 0.4f, 0.4f, 0.f));
	plane1.setSpecularColour(DirectX::XMVectorSet(0.4f, 0.4f, 0.4f, 0.f));

	//Raytracer::Objects::Plane plane2 = Raytracer::Objects::Plane(
	//	DirectX::XMVectorSet(0.f, -2.f, 4.7f, 0.f),
	//	DirectX::XMVectorSet(4.f, 1.2f, -2.2f, 0.f));
	//plane2.setDiffuseColour(DirectX::XMVectorSet(0.8f, 0.4f, 0.4f, 0.f));
	//plane2.setSpecularColour(DirectX::XMVectorSet(0.8f, 0.4f, 0.4f, 0.f));

	scene.addLight(&light1);
	scene.addObject(&sphere1);
	scene.addObject(&sphere2);
	scene.addObject(&sphere3);
	scene.addObject(&plane1);
	//scene.addObject(&plane2);
	try {
		scene.renderScene(L"output.png");
	}
	catch (std::exception e) {
		printf(e.what());
	}
	
}