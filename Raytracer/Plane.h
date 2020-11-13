#pragma once
#include "Object.h"


namespace Raytracer {
	namespace Objects {

		class Plane :
			public Object
		{
		public:
			Plane(DirectX::XMVECTOR pos, DirectX::XMVECTOR normal, DirectX::XMVECTOR direction);

			RayHit getIntersect(Ray incomingRay);
			DirectX::XMVECTOR getNormalAt(DirectX::XMVECTOR point);

			DirectX::XMVECTOR getDiffuseColour(DirectX::XMVECTOR position);
			DirectX::XMVECTOR getSpecularColour(DirectX::XMVECTOR position);
		private:
			DirectX::XMVECTOR normal;
			DirectX::XMVECTOR direction;
			DirectX::XMVECTOR perpDirection;
		};

	}
}