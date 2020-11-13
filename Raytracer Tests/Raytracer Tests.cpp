#include "pch.h"
#include "CppUnitTest.h"

#include "Scene.h"

#include "Sphere.h"
#include "PointLight.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template <class T>
bool approxEqual(T a, T b) {
	return abs(a - b) < 0.001f;
}

namespace RaytracerTests
{
	TEST_CLASS(RaytracerTests)
	{
	public:
		
		TEST_METHOD(SphereIntersect_MissFromInside)
		{
			Raytracer::Objects::Sphere sphere = Raytracer::Objects::Sphere(DirectX::XMVectorZero(), 1.f);
			Raytracer::Ray ray = Raytracer::Ray(DirectX::XMVectorZero(), DirectX::XMVectorSet(1.f,0.f,0.f,0.f));
			Raytracer::RayHit intersect = sphere.getIntersect(ray);

			Assert::AreEqual((int) intersect.collider, NULL);
		}

		TEST_METHOD(SphereIntersect)
		{
			Raytracer::Objects::Sphere sphere = Raytracer::Objects::Sphere(DirectX::XMVectorZero(), 1.f);
			Raytracer::Ray ray = Raytracer::Ray(DirectX::XMVectorSet(-2.f, 0.f, 0.f, 0.f), DirectX::XMVectorSet(1.f, 0.f, 0.f, 0.f));
			Raytracer::RayHit intersect = sphere.getIntersect(ray);

			Assert::AreEqual(intersect.collider == &sphere, true);
			Assert::AreEqual(approxEqual(intersect.distance, 1.f), true);
			Assert::AreEqual(approxEqual(DirectX::XMVectorGetX(intersect.normal),-1.f),true);
			Assert::AreEqual(approxEqual(DirectX::XMVectorGetX(DirectX::XMVector3Length(intersect.normal)),1.f), true);
			
		}
	};
}
