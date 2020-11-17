#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

#include <wincodec.h>
#include <d2d1.h>
#include <DirectXMath.h>

//#include <algorithm>

#pragma comment(lib, "d2d1")

#include <shcore.h>

#include <exception>

#include <list>
#include <random>
#include <ctime>
#include <chrono>
#include <limits>
#include <map>
#include <fstream>

#include <tchar.h>
#import <msxml6.dll> rename_namespace(_T("MSXML"))
#include <atlbase.h>

#define POSITIVE_INFINITY std::numeric_limits<float>::infinity();
#define NEGATIVE_INFINITY (-1 * std::numeric_limits<float>::infinity());

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

inline float fRand(float min, float max) {
    return ((float) rand() / RAND_MAX) * (max - min) + min;
}