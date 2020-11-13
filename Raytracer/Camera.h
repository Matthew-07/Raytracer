#pragma once

namespace Raytracer {

	class Ray;

	class Camera
	{
	public:
		Camera(float fov, float aspectRatio, UINT pxWidth, UINT pxHeight);

		Ray castRay(int x, int y);

	private:
		float aspectRatio = 16.f / 9.f;
		float fov = 70.f;
		float depthOfField = 0.02f;
		float focalDistance = 3.5f;

		UINT pxWidth, pxHeight;
		float width, height;		
		float stepX, stepY;

	};

}