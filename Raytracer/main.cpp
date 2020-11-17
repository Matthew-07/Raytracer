#include "stdafx.h"

#include "Scene.h"
#include "Renderer.h"
#include "Sphere.h"
#include "Plane.h"
#include "PointLight.h"
#include "SphericalLight.h"

//const UINT numberOfBounces = 2;

int wmain(int argc, wchar_t* argv[]) {

	CoInitialize(NULL);

	UINT numberOfBounces = 2;
	UINT samplesPerPixel = 10;
	UINT samplesPerSphericalLight = 20;

	UINT outputWidth = 640;
	UINT outputHeight = 480;
	
	LPCWSTR sceneFile = L"default_scene.xml";
	LPCWSTR outputFile = L"output.png";

	enum Arguments {
		NumberOfBounces,
		SamplesPerPixel,
		SamplesPerSphericalLight,
		SceneFile,
		OutputFile
	};

	std::map<std::wstring, Arguments> argMap;
	argMap[L"--bounces"] = NumberOfBounces;
	argMap[L"-b"] = NumberOfBounces;

	argMap[L"--samples"] = SamplesPerPixel;
	argMap[L"-s"] = SamplesPerPixel;

	argMap[L"--shadowrays"] = SamplesPerSphericalLight;
	argMap[L"-r"] = SamplesPerSphericalLight;

	argMap[L"--scene"] = SceneFile;
	argMap[L"-i"] = SceneFile;

	argMap[L"--output"] = OutputFile;
	argMap[L"-o"] = OutputFile;

	for (int arg = 1; arg < argc; arg+=2) {
		if (argc <= arg + 1) { break; } // There is no value specified for this option
		switch (argMap[argv[arg]]) {
		case NumberOfBounces:
			numberOfBounces = std::wcstoul(argv[arg + 1],NULL,10);
			break;

		case SamplesPerPixel:
			samplesPerPixel = std::wcstoul(argv[arg + 1], NULL, 10);
			break;

		case SamplesPerSphericalLight:
			samplesPerSphericalLight = std::wcstoul(argv[arg + 1], NULL, 10);
			break;

		case SceneFile:
			sceneFile = argv[arg + 1];
			break;

		case OutputFile:
			outputFile = argv[arg + 1];
			break;

		}
	}
	
	Raytracer::Scene scene;
	/*
	scene.setAmbientColour(DirectX::XMVectorSet(0.1f, 0.1f, 0.1f, 0.f));
	scene.setAmbientIntensity(1.f);

	Raytracer::Lights::SphericalLight light1;
	light1.setPosition(DirectX::XMVectorSet(1, 3, 2, 0));
	light1.setColour(DirectX::XMVectorSet(0.6f, 0.6f, 1.f, 0.f));
	light1.setIntensity(80.f);

	Raytracer::Lights::SphericalLight light2;
	light2.setPosition(DirectX::XMVectorSet(-3, 0.6, 4, 0));
	light2.setColour(DirectX::XMVectorSet(1.f, 0.4f, 0.1f, 0.f));
	light2.setIntensity(80.f);

	Raytracer::Objects::Sphere sphere1 = Raytracer::Objects::Sphere(DirectX::XMVectorSet(0.55f, -0.16f, 3.5f, 0.f), 0.5f);
	sphere1.setDiffuseColour(DirectX::XMVectorSet(0.1f, 1.f, 0.5f, 0.f));

	Raytracer::Objects::Sphere sphere2 = Raytracer::Objects::Sphere(DirectX::XMVectorSet(-0.55f, 0.f, 5.f, 0.f), 0.9f);
	sphere2.setDiffuseColour(DirectX::XMVectorSet(1.f, 0.5f, 0.5f, 0.f));

	Raytracer::Objects::Sphere sphere3 = Raytracer::Objects::Sphere(DirectX::XMVectorSet(-0.35f, -0.3f, 2.5f, 0.f), 0.25f);
	sphere3.setDiffuseColour(DirectX::XMVectorSet(0.85f, 0.55f, 0.1f, 0.f));

	Raytracer::Objects::Sphere sphere4 = Raytracer::Objects::Sphere(DirectX::XMVectorSet(1.6f, 0.5f,8.f, 0.f), 1.2f);
	sphere4.setDiffuseColour(DirectX::XMVectorSet(0.8f, 0.8f, 0.8f, 0.f));
	sphere4.setReflectivity(0.5f);

	Raytracer::Objects::Plane plane1 = Raytracer::Objects::Plane(
		DirectX::XMVectorSet(0.f, -1.f, 0.f, 0.f),
		DirectX::XMVectorSet(0.f, 1.f, -0.01f, 0.f),
		DirectX::XMVectorSet(0.f, 0.01f, 1.f, 0.f)
		);
	plane1.setDiffuseColour(DirectX::XMVectorSet(0.4f, 0.4f, 0.4f, 0.f));

	//Raytracer::Objects::Plane plane2 = Raytracer::Objects::Plane(
	//	DirectX::XMVectorSet(0.f, -2.f, 4.7f, 0.f),
	//	DirectX::XMVectorSet(4.f, 1.2f, -2.2f, 0.f));
	//plane2.setDiffuseColour(DirectX::XMVectorSet(0.8f, 0.4f, 0.4f, 0.f));
	//plane2.setSpecularColour(DirectX::XMVectorSet(0.8f, 0.4f, 0.4f, 0.f));

	scene.addLight(&light1);
	scene.addLight(&light2);
	scene.addObject(&sphere1);
	scene.addObject(&sphere2);
	scene.addObject(&sphere3);
	scene.addObject(&sphere4);
	scene.addObject(&plane1);
	*/
	//scene.addObject(&plane2);
	
	scene.loadFromFile(sceneFile);
	Raytracer::Renderer renderer = Raytracer::Renderer(45.f, outputWidth, outputHeight, samplesPerPixel, numberOfBounces);

	try {
		auto start = std::chrono::steady_clock::now();
		renderer.renderScene(L"output.png", &scene);
		auto end = std::chrono::steady_clock::now();
		printf("%i",std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
	}
	catch (std::exception e) {
		printf(e.what());
	}
	
	std::getchar();
}