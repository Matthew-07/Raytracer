#pragma once

#include "Ray.h"

namespace Raytracer {

	const DirectX::XMFLOAT4		DEFAULT_DIFF_C = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	const DirectX::XMFLOAT4		DEFAULT_SPEC_C = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	const float					DEFAULT_K_D = 0.6f;
	const float					DEFAULT_K_S = 0.0f;
	const float					DEFAULT_ALPHA = 0.0f;
	const float					DEFAULT_REFLECTIVITY = 0.1f;

	namespace Objects {
		class Object
		{
		public:
			virtual RayHit getIntersect(Ray incomingRay) = 0;
			virtual DirectX::XMVECTOR getNormalAt(DirectX::XMVECTOR point) = 0;

			virtual void prepare() {} // Ensure state is valid before render

			void setPosition(DirectX::XMVECTOR pos);
			void setX(float x);
			void setY(float y);
			void setZ(float z);

			void setDiffuseColour(DirectX::XMVECTOR colour);
			void setPhongKD(float kd);
			void setPhongKS(float ks);
			void setAlpha(float a);
			void setReflectivity(float relectivity);

			DirectX::XMVECTOR getPosition();

			virtual DirectX::XMVECTOR getDiffuseColour(DirectX::XMVECTOR position);
			float getPhongKD();
			float getPhongKS();
			float getAlpha();
			float getRelectivity();

		protected:
			DirectX::XMVECTOR position = DirectX::XMVectorZero();

			DirectX::XMVECTOR diff_c = DirectX::XMVectorZero();
			float k_d = 0.8, k_s = 1.2, alpha = 10, reflectivity = 0.3;
		};
	}
}
