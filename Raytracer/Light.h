#pragma once

namespace Raytracer {
	class Scene;

	struct LightContributions{
		DirectX::XMVECTOR diff = DirectX::XMVectorZero();
		DirectX::XMVECTOR spec = DirectX::XMVectorZero();
	};

	namespace Lights {

		class Light
		{
		public:
			virtual LightContributions sample(
				Scene* scene,
				DirectX::XMVECTOR origin,
				DirectX::XMVECTOR normal,
				DirectX::XMVECTOR view,
				float alpha) = 0;

			void setColour(DirectX::XMVECTOR colour);
			void setPosition(DirectX::XMVECTOR position);
			void setX(float x);
			void setY(float y);
			void setZ(float z);
			void setIntensity(float intensity);
		protected:
			DirectX::XMVECTOR colour = DirectX::XMVectorZero();
			float intensity = 0.f;
			//DirectX::XMVECTOR totalColour = DirectX::XMVectorZero();

			DirectX::XMVECTOR position = DirectX::XMVectorZero();

			static void rayContributions(
				Scene* scene,
				DirectX::XMVECTOR origin,
				DirectX::XMVECTOR normal,
				DirectX::XMVECTOR view,
				float alpha,
				DirectX::XMVECTOR lightPosition,
				DirectX::XMVECTOR lightColour,
				float lightIntensity,
				LightContributions &contributions
			);
		};

	}
}