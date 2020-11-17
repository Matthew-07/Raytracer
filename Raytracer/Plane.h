#pragma once
#include "Object.h"

namespace Raytracer {
	namespace Objects {

		class Plane :
			public Object
		{
		public:
			Plane() {}
			Plane(DirectX::XMVECTOR pos, DirectX::XMVECTOR normal, DirectX::XMVECTOR direction);

			void prepare();

			void setNormal(DirectX::XMVECTOR normal);
			void setNormalX(float x);
			void setNormalY(float y);
			void setNormalZ(float z);

			void setDirection(DirectX::XMVECTOR normal);
			void setDirectionX(float x);
			void setDirectionY(float y);
			void setDirectionZ(float z);
										
			RayHit getIntersect(Ray incomingRay);
			DirectX::XMVECTOR getNormalAt(DirectX::XMVECTOR point);

			DirectX::XMVECTOR getDiffuseColour(DirectX::XMVECTOR position);
		private:
			DirectX::XMVECTOR normal;
			DirectX::XMVECTOR direction;
			DirectX::XMVECTOR perpDirection;
		};

	}
}