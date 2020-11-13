#pragma once
namespace Raytracer {
	namespace Objects {
		class Object;
	}

	class Ray {
	public:
		Ray(DirectX::XMVECTOR origin, DirectX::XMVECTOR direction);

		DirectX::XMVECTOR origin;
		DirectX::XMVECTOR direction;
	};

	class RayHit {
	public:
		RayHit();
		RayHit(Objects::Object * collider, float distance, DirectX::XMVECTOR location, DirectX::XMVECTOR normal);

		Objects::Object * collider = NULL;
		DirectX::XMVECTOR location;
		DirectX::XMVECTOR normal;
		float distance;
	};
}