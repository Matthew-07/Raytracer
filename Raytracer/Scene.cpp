#include "stdafx.h"
#include "Scene.h"

#include "Sphere.h"
#include "Plane.h"
#include "PointLight.h"
#include "SphericalLight.h"

using namespace DirectX;

using namespace Raytracer;
using namespace Objects;
using namespace Lights;

#define CHK_ALLOC(p)        do { if (!(p)) { hr = E_OUTOFMEMORY; goto CleanUp; } } while(0)

UINT convert(float c) { return 255 * max(0, min(1, c)); }

XMVECTOR RGBHexToFloat(LPCWSTR colour) {
	colour = colour + 1;
	int r, g, b;
	swscanf_s(colour, L"%2x%2x%2x", &r, &g, &b);
	return XMVectorSet((float)r/255, (float)g/255, (float)b/255, 1.f);
}

void Raytracer::Scene::loadFromFile(LPCWSTR path)
{
	for (auto object : scene_objects) {
		delete object;
	}
	scene_objects.clear();

	for (auto light : scene_lights) {
		delete light;
	}
	scene_lights.clear();
	
	enum SceneElements {
		ELE_AmbientLight,
		ELE_TruePointLight,
		ELE_PointLight,
		ELE_Sphere,
		ELE_Plane
	};

	std::map<std::wstring, SceneElements> sceneElementsMap;
	sceneElementsMap[L"ambient-light"] = ELE_AmbientLight;
	sceneElementsMap[L"true-point-light"] = ELE_TruePointLight;
	sceneElementsMap[L"point-light"] = ELE_PointLight;
	sceneElementsMap[L"sphere"] = ELE_Sphere;
	sceneElementsMap[L"plane"] = ELE_Plane;

	enum AmbientProperties {
		AM_Colour,
		AM_Intensity
	};

	std::map<std::wstring, AmbientProperties> ambientMap;
	ambientMap[L"colour"] = AM_Colour;
	ambientMap[L"intensity"] = AM_Intensity;

	enum TruePointProperties {
		TP_Colour,
		TP_Intensity,
		TP_X,
		TP_Y,
		TP_Z
	};

	std::map<std::wstring, TruePointProperties> truePointMap;
	truePointMap[L"colour"] = TP_Colour;
	truePointMap[L"intensity"] = TP_Intensity;
	truePointMap[L"x"] = TP_X;
	truePointMap[L"y"] = TP_Y;
	truePointMap[L"z"] = TP_Z;

	enum PointProperties {
		PT_Colour,
		PT_Intensity,
		PT_X,
		PT_Y,
		PT_Z,
		PT_Radius
	};

	std::map<std::wstring, PointProperties> pointMap;
	pointMap[L"colour"] = PT_Colour;
	pointMap[L"intensity"] = PT_Intensity;
	pointMap[L"x"] = PT_X;
	pointMap[L"y"] = PT_Y;
	pointMap[L"z"] = PT_Z;
	pointMap[L"radius"] = PT_Radius;

	enum SphereProperties {
		SP_Colour,
		SP_X,
		SP_Y,
		SP_Z,
		SP_Radius,
		SP_KS,
		SP_KD,
	};

	std::map<std::wstring, SphereProperties> sphereMap;
	sphereMap[L"colour"] = SP_Colour;
	sphereMap[L"x"] = SP_X;
	sphereMap[L"y"] = SP_Y;
	sphereMap[L"z"] = SP_Z;
	sphereMap[L"radius"] = SP_Radius;
	sphereMap[L"kS"] = SP_KS;
	sphereMap[L"kD"] = SP_KD;

	enum PlaneProperties {
		PL_Colour,
		PL_X,
		PL_Y,
		PL_Z,
		PL_NX,
		PL_NY,
		PL_NZ,
		PL_DX,
		PL_DY,
		PL_DZ,
		PL_KD,
		PL_KS,
	};

	std::map<std::wstring, PlaneProperties> planeMap;
	planeMap[L"colour"] = PL_Colour;
	planeMap[L"x"] = PL_X;
	planeMap[L"y"] = PL_Y;
	planeMap[L"z"] = PL_Z;
	planeMap[L"nx"] = PL_NX;
	planeMap[L"ny"] = PL_NY;
	planeMap[L"nz"] = PL_NZ;
	planeMap[L"dx"] = PL_DX;
	planeMap[L"dy"] = PL_DY;
	planeMap[L"dz"] = PL_DZ;
	planeMap[L"kS"] = PL_KS;
	planeMap[L"kD"] = PL_KD;

	MSXML::IXMLDOMDocument2Ptr xmlDoc;
	HRESULT hr;

	if (FAILED(hr = xmlDoc.CreateInstance(__uuidof(MSXML::DOMDocument60),
		NULL, CLSCTX_INPROC_SERVER)));

	xmlDoc->put_async(VARIANT_FALSE);
	xmlDoc->put_validateOnParse(VARIANT_FALSE);
	xmlDoc->put_resolveExternals(VARIANT_FALSE);
	xmlDoc->put_preserveWhiteSpace(VARIANT_TRUE);

	if (xmlDoc->load(path) != VARIANT_TRUE) {
		printf("Unable to load %s\n", path);
	}
	else {
		printf("XML was successfully loaded\n");

		xmlDoc->setProperty("SelectionLanguage", "XPath");
		MSXML::IXMLDOMNodeListPtr pNodes = xmlDoc->selectNodes(L"//scene[1]/*");
		
		if (!pNodes) {
			throw std::exception("Failed to load scene.");
		}

		long length = 0;
		pNodes->get_length(&length);

		MSXML::IXMLDOMNode * pNode;
		BSTR bstrNodeName;

		for (int i = 0; i < length; i++) {
			pNodes->get_item(i, &pNode);
			pNode->get_nodeName(&bstrNodeName);

			MSXML::IXMLDOMNamedNodeMap* pNodeProperties;
			MSXML::IXMLDOMNode* pNodeProperty;

			pNode->get_attributes(&pNodeProperties);
			long numProperties;
			pNodeProperties->get_length(&numProperties);

			BSTR bstrPropertyName;

			switch (sceneElementsMap[bstrNodeName]) {
			case ELE_AmbientLight:
			{		
				for (int p = 0; p < numProperties; p++) {
					pNodeProperties->get_item(p, &pNodeProperty);
					pNodeProperty->get_nodeName(&bstrPropertyName);
					CComVariant value;
					pNodeProperty->get_nodeValue(&value);

					switch (ambientMap[bstrPropertyName]) {
					case AM_Colour:							
						ambientLighting = RGBHexToFloat(value.bstrVal);
						break;
					case AM_Intensity:
						ambientIntensity = std::wcstof(value.bstrVal, NULL);
						break;
					}
				}
				break;
			}
			case ELE_TruePointLight:
			{
				PointLight* newObj = new PointLight();
				for (int p = 0; p < numProperties; p++) {
					pNodeProperties->get_item(p, &pNodeProperty);
					pNodeProperty->get_nodeName(&bstrPropertyName);
					CComVariant value;
					pNodeProperty->get_nodeValue(&value);

					switch (truePointMap[bstrPropertyName]) {
					case TP_Colour:
						newObj->setColour(RGBHexToFloat(value.bstrVal));
						break;
					case TP_Intensity:
						newObj->setIntensity(std::wcstof(value.bstrVal, NULL));
						break;
					case TP_X:
						newObj->setX(std::wcstof(value.bstrVal, NULL));
						break;
					case TP_Y:
						newObj->setY(std::wcstof(value.bstrVal, NULL));
						break;
					case TP_Z:
						newObj->setZ(std::wcstof(value.bstrVal, NULL));
						break;
					}
				}
				addLight(newObj);
				break;
			}
			case ELE_PointLight:
			{
				SphericalLight* newObj = new SphericalLight();
				for (int p = 0; p < numProperties; p++) {
					pNodeProperties->get_item(p, &pNodeProperty);
					pNodeProperty->get_nodeName(&bstrPropertyName);
					CComVariant value;
					pNodeProperty->get_nodeValue(&value);

					switch (pointMap[bstrPropertyName]) {
					case PT_Colour:
						newObj->setColour(RGBHexToFloat(value.bstrVal));
						break;
					case PT_Intensity:
						newObj->setIntensity(std::wcstof(value.bstrVal, NULL));
						break;
					case PT_X:
						newObj->setX(std::wcstof(value.bstrVal, NULL));
						break;
					case PT_Y:
						newObj->setY(std::wcstof(value.bstrVal, NULL));
						break;
					case PT_Z:
						newObj->setZ(std::wcstof(value.bstrVal, NULL));
						break;
					case PT_Radius:
						newObj->setRadius(std::wcstof(value.bstrVal, NULL));
						break;
					}
				}
				addLight(newObj);
				break;
			}
			case ELE_Sphere:
			{
				Sphere *newObj = new Sphere();
				for (int p = 0; p < numProperties; p++) {
					pNodeProperties->get_item(p, &pNodeProperty);
					pNodeProperty->get_nodeName(&bstrPropertyName);
					CComVariant value;
					pNodeProperty->get_nodeValue(&value);

					switch (sphereMap[bstrPropertyName]) {
					case SP_Colour:
						newObj->setDiffuseColour(RGBHexToFloat(value.bstrVal));
						break;
					case SP_Radius:
						newObj->setRadius(std::wcstof(value.bstrVal, NULL));
						break;
					case SP_X:
						newObj->setX(std::wcstof(value.bstrVal, NULL));
						break;
					case SP_Y:
						newObj->setY(std::wcstof(value.bstrVal, NULL));
						break;
					case SP_Z:
						newObj->setZ(std::wcstof(value.bstrVal, NULL));
						break;

					case SP_KD:
						newObj->setPhongKD(std::wcstof(value.bstrVal, NULL));
						break;
					case SP_KS:
						newObj->setPhongKS(std::wcstof(value.bstrVal, NULL));
						break;
					}
				}
				addObject(newObj);
				break;
			}
			case ELE_Plane:
			{
				Plane* newObj = new Plane();
				for (int p = 0; p < numProperties; p++) {
					pNodeProperties->get_item(p, &pNodeProperty);
					pNodeProperty->get_nodeName(&bstrPropertyName);
					CComVariant value;
					pNodeProperty->get_nodeValue(&value);

					switch (planeMap[bstrPropertyName]) {
					case PL_Colour:
						newObj->setDiffuseColour(RGBHexToFloat(value.bstrVal));
						break;
					case PL_X:
						newObj->setX(std::wcstof(value.bstrVal, NULL));
						break;
					case PL_Y:
						newObj->setY(std::wcstof(value.bstrVal, NULL));
						break;
					case PL_Z:
						newObj->setZ(std::wcstof(value.bstrVal, NULL));
						break;

					case PL_NX:
						newObj->setNormalX(std::wcstof(value.bstrVal, NULL));
						break;
					case PL_NY:
						newObj->setNormalY(std::wcstof(value.bstrVal, NULL));
						break;
					case PL_NZ:
						newObj->setNormalZ(std::wcstof(value.bstrVal, NULL));
						break;

					case PL_DX:
						newObj->setDirectionX(std::wcstof(value.bstrVal, NULL));
						break;
					case PL_DY:
						newObj->setDirectionY(std::wcstof(value.bstrVal, NULL));
						break;
					case PL_DZ:
						newObj->setDirectionZ(std::wcstof(value.bstrVal, NULL));
						break;

					case PL_KD:
						newObj->setPhongKD(std::wcstof(value.bstrVal, NULL));
						break;					
					case PL_KS:
						newObj->setPhongKS(std::wcstof(value.bstrVal, NULL));
						break;
					}

				}
				addObject(newObj);
				break;
			}
			}			
		}
	}
}

RayHit Scene::getClosestIntersection(Ray ray)
{
	RayHit closestIntersection = RayHit();
	for (auto object : scene_objects) {
		RayHit intersection = object->getIntersect(ray);
		if (intersection.distance < closestIntersection.distance) {
			closestIntersection = intersection;
		}
	}

	return closestIntersection;
}

void Raytracer::Scene::addLight(Light *p)
{
	scene_lights.push_back(p);
}

void Raytracer::Scene::addObject(Object*s)
{
	scene_objects.push_back(s);
}

void Raytracer::Scene::setAmbientColour(DirectX::XMVECTOR ambient)
{
	ambientLighting = ambient;
}

void Raytracer::Scene::setAmbientIntensity(float intensity)
{
	ambientIntensity = intensity;
}

XMVECTOR Scene::getAmbientLighting()
{
	return ambientLighting * ambientIntensity;
}

std::list<Raytracer::Lights::Light*>& Raytracer::Scene::getSceneLights()
{
	return scene_lights;
}