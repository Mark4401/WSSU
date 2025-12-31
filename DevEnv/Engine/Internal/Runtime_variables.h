#ifndef TEST_INTERNAL_H
#define TEST_INTERNAL_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif 

//// 8-bit
//typedef signed char       int8_s;
//typedef unsigned char     int8_u;
//
//// 16-bit
//typedef signed short      int16_s;
//typedef unsigned short    int16_u;
//
//// 32-bit
//typedef signed int        int32_s;
//typedef unsigned int      int32_u;
//
//// 64-bit
//typedef signed long long  int64_s;
//typedef unsigned long long int64_u;

#include<cstdint>

typedef int8_t int8_s;
typedef uint8_t int8_u;

typedef int16_t int16_s;
typedef uint16_t int16_u;

typedef int32_t int32_s;
typedef uint32_t int32_u;

typedef int64_t int64_s;
typedef uint64_t int64_u;

// typedefs

typedef const wchar_t* Wide_Char;

#define DEFAULT_WINDOW_ID									1
#define BLANK_WINDOW_STYLE									0


#define WIN32_LIBRARIY_PROPERTIES_ACTIVE					2
#define WIN32_LIBRARIY_PROPERTIES_SUCCESSFUL_DELETION		4
#define WIN32_LIBRARIY_PROPERTIES_FAILURE_DELETION			8

#define CLIENT_REFERENCE_MISSING							5
#define CLIENT_REFERENCE_PRESENT							10

/*	USECASE

	int8_s		a = -100;
	int8_u		b = 200;
	int16_s		c = -30000;
	int16_u		d = 60000;
	int32_s		e = -1000000000;
	int32_u		f = 3000000000U;
	int64_s		g = -5000000000LL;
	int64_u		h = 10000000000ULL;

*/

#include<Windows.h>
#include <dwmapi.h>
#include <d3d11.h>         // Main Direct3D 11 API
#include <dxgi.h>          // DXGI (swap chain, adapters)
#include <d3dcompiler.h>   // Shared compilation (optional, needed if compiling HLSL at runtime)
#include <DirectXMath.h>  // Optional, but handy for math
#include <shellscalingapi.h> 
#include <strsafe.h>

#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dwmapi.lib")

#include<iostream>
#include<String>


// Enable Unicode for Win32 API
#ifndef UNICODE
#define UNICODE
#endif 


#endif // !TEST_INTERNAL_H
