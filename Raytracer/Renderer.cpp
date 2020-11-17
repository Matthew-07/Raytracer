#include "stdafx.h"
#include "Renderer.h"

#include "Scene.h"

using namespace DirectX;
using namespace Raytracer;
using namespace Objects;
using namespace Lights;

Renderer::Renderer(float fov, UINT pxWidth, UINT pxHeight, UINT samplesPerPixel, UINT numBounces) : camera(fov, (float) pxWidth / pxHeight, pxWidth, pxHeight)
{
	numberOfBounces = numBounces;
	this->samplesPerPixel = samplesPerPixel;
	outputWidth = pxWidth;
	outputHeight = pxHeight;
}

IWICBitmap* Raytracer::Renderer::renderScene(LPCWSTR path, Scene* scene)
{
	ID2D1Factory* pFactory;
	IWICImagingFactory* pImageFactory;
	ID2D1RenderTarget* pRenderTarget;
	IWICBitmap* pOutput;

	HRESULT hr;

	if (FAILED(CoCreateInstance(
		CLSID_WICImagingFactory2,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pImageFactory)
	))) throw std::exception("Failed to create WIC Imaging factory.");

	if (pImageFactory == NULL) throw std::exception("Imaging Factory was NULL.");

	if (FAILED(pImageFactory->CreateBitmap(
		outputWidth,
		outputHeight,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapCacheOnDemand,
		&pOutput
	))) throw std::exception("Faield to create Bitmap");

	WICRect rect;
	rect.Width = outputWidth;
	rect.Height = outputHeight;
	rect.X = 0;
	rect.Y = 0;

	IWICBitmapLock* lock;

	if (FAILED(pOutput->Lock(&rect, WICBitmapLockWrite, &lock))) throw std::exception("Failed to achieve bitmap lock.");

	UINT cbBufferSize = 0;
	UINT cbStride = 0;
	UINT8* pv = NULL;

	if (FAILED(lock->GetStride(&cbStride))) throw std::exception("Failed to get lock stride.");

	if (FAILED(lock->GetDataPointer(&cbBufferSize, &pv))) throw std::exception("Failed to get data pointer.");

	UINT seed = time(0);

	scene->prepare();

#pragma omp parallel for
	for (int x = 0; x < outputWidth; x++) {
#pragma omp parallel for
		for (int y = 0; y < outputHeight; y++) {
			XMVECTOR colour = XMVECTOR();
			// TODO: Calculate pixel colour
			for (int s = 0; s < samplesPerPixel; s++) {
				Ray ray = camera.castRay(x, y);
				colour += trace(scene, &ray, numberOfBounces);
			}

			srand(seed + x + y * outputWidth);

			colour /= samplesPerPixel;
			colour = toneMap(colour);
			colour = XMVectorClamp(colour, XMVectorZero(), XMVectorSet(1.f, 1.f, 1.f, 1.f));

			XMFLOAT3 rgb;
			XMStoreFloat3(&rgb, colour);

			UINT offset = x * 4 + y * cbStride;
			UINT8 red = rgb.x * 255;
			UINT8 green = rgb.y * 255;
			UINT8 blue = rgb.z * 255;
			*(pv + offset) = red;
			*(pv + offset + 1) = green;
			*(pv + offset + 2) = blue;
			*(pv + offset + 3) = 255;
		}
	}

	SafeRelease(&lock);

	// Save Bitmap to file

	IWICStream* stream;
	if (FAILED(hr = pImageFactory->CreateStream(&stream)))
		throw std::exception("Failed to create stream.");

	if (FAILED(hr = stream->InitializeFromFilename(path, GENERIC_WRITE)))
		throw std::exception("Failed to initalise stream.");

	IWICBitmapEncoder* pEncoder;

	if (FAILED(hr = pImageFactory->CreateEncoder(
		GUID_ContainerFormatBmp, // GUID_ContainerFormatPng
		NULL,    // No preferred codec vendor.
		&pEncoder
	))) throw std::exception("Failed to create bitmap encoder.");

	if (FAILED(hr = pEncoder->Initialize(
		stream,
		WICBitmapEncoderNoCache
	))) throw std::exception("Failed to initalise bitmap encoder.");

	IWICBitmapFrameEncode* pFrameEncoder;
	if (FAILED(pEncoder->CreateNewFrame(
		&pFrameEncoder,
		NULL
	))) throw std::exception("Failed to create bitmap frame encoder.");

	if (FAILED(hr = pFrameEncoder->Initialize(nullptr))) throw std::exception("Failed to initalise frame encoder.");
	//if (FAILED(hr = pFrameEncoder->SetSize(outputWidth, outputHeight))) throw std::exception("Failed to set size of frame encoder.");
	WICPixelFormatGUID format = GUID_WICPixelFormat32bppPRGBA;
	//if (FAILED(hr = pFrameEncoder->SetPixelFormat(&format))) throw std::exception("Failed to set frame encoder format.");

	if (FAILED(hr = pFrameEncoder->WriteSource(pOutput, NULL))) throw std::exception("Failed to write source to frame encoder.");

	pEncoder->SetThumbnail(pOutput);

	pFrameEncoder->Commit();
	pEncoder->Commit();


	// Release Bitmap
	SafeRelease(&pOutput);
	SafeRelease(&pImageFactory);

	SafeRelease(&pEncoder);
	SafeRelease(&pFrameEncoder);
	SafeRelease(&stream);
}

XMVECTOR Renderer::trace(Scene* scene, Ray* ray, UINT bouncesLeft)
{
    RayHit intersect = scene->getClosestIntersection(*ray);
    if (intersect.collider == NULL) return backgroundColour;

    XMVECTOR directIllumination = illuminate(scene, intersect.collider, intersect.location, intersect.normal, ray->origin);

    float reflectivity = intersect.collider->getRelectivity();

    if (bouncesLeft == 0 || reflectivity == 0) {
        return directIllumination;
    }
    else {
        XMVECTOR R = XMVector3Reflect(-ray->direction, intersect.normal);
        Ray reflectedRay = Ray(intersect.location + (intersect.normal * EPSILON), -R);
        XMVECTOR reflectedIllumination = trace(scene, &reflectedRay, bouncesLeft - 1);

        directIllumination *= (1.0f - reflectivity);
        reflectedIllumination *= reflectivity;

        return directIllumination + reflectedIllumination;
    }

}

XMVECTOR Renderer::illuminate(Scene* scene, Object* object, XMVECTOR point, XMVECTOR normal, XMVECTOR origin)
{
    XMVECTOR c_diff = object->getDiffuseColour(point);
    
    float k_d = object->getPhongKD();
    float k_s = object->getPhongKS();

    // Ambient Component
    XMVECTOR returnColour = c_diff * scene->getAmbientLighting();

    for (auto light : scene->getSceneLights()) {
        LightContributions components = light->sample(scene, point, normal, XMVector3Normalize(origin - point), object->getAlpha());

        // Diffuse Component
        returnColour += k_d * c_diff * components.diff;
        
        // Specular Component
        returnColour += k_s * components.spec;
    }

    return returnColour;
}

XMVECTOR Renderer::toneMap(XMVECTOR linearRGB)
{
	float invGamma = 1. / 2.2;
	float a = 2;  // controls brightness
	float b = 1.3; // controls contrast

	// Sigmoidal tone mapping
	XMVECTOR powRGB = XMVectorPow(linearRGB, XMVectorSet(b, b, b, b));
	float c = pow(0.5 / a, b);
	XMVECTOR displayRGB = powRGB * (XMVectorSet(1, 1, 1, 1) / (powRGB + XMVectorSet(c, c, c, c)));

	// Display encoding - gamma
	XMVECTOR gammaRGB = XMVectorPow(displayRGB, XMVectorSet(invGamma, invGamma, invGamma, invGamma));

	return gammaRGB;
}