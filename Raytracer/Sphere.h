#pragma once
#include "Object.h"

namespace Raytracer {
	namespace Objects {

		class Sphere :
			public Object
		{
		public:
			Sphere() {}
			Sphere(DirectX::XMVECTOR pos, float radius);

			void setRadius(float radius);

			RayHit getIntersect(Ray incomingRay);
			DirectX::XMVECTOR getNormalAt(DirectX::XMVECTOR point);

		private:
			float radius;
		};

	}
}