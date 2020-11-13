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
			virtual LightContributions sample(Scene* scene, DirectX::XMVECTOR origin, DirectX::XMVECTOR normal, DirectX::XMVECTOR view, float alpha) = 0;

			void setColour(DirectX::XMVECTOR colour);
			void setPosition(DirectX::XMVECTOR position);
			void setIntensity(float intensity);
		protected:
			DirectX::XMVECTOR colour;
			float intensity;
			DirectX::XMVECTOR totalColour;

			DirectX::XMVECTOR position;

			static void rayContributions(
				Scene* scene,
				DirectX::XMVECTOR origin,
				DirectX::XMVECTOR normal,
				DirectX::XMVECTOR view,
				float alpha,
				DirectX::XMVECTOR lightPosition,
				DirectX::XMVECTOR lightIntensity,
				LightContributions &contributions
			);
		};

	}
}