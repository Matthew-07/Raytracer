#pragma once
#include "Object.h"

namespace Raytracer {
	namespace Objects {

		class Sphere :
			public Object
		{
		public:
			Sphere(DirectX::XMVECTOR pos, float radius);

			RayHit getIntersect(Ray incomingRay);
			DirectX::XMVECTOR getNormalAt(DirectX::XMVECTOR point);

		private:
			float radius;
		};

	}
}