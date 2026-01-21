#ifndef WSML_H
#define WSML_H

#include<stdint.h>

typedef int8_t int8_s;
typedef uint8_t int8_u;

typedef int16_t int16_s;
typedef uint16_t int16_u;

typedef int32_t int32_s;
typedef uint32_t int32_u;

typedef int64_t int64_s;
typedef uint64_t int64_u;


#ifdef _WIN32
#ifdef WSML_EXPORT
#define WSML_API __declspec(dllexport)
#else
#define WSML_API __declspec(dllimport)
#endif
#else
#define WSML_API
#endif

#include<WSML/Window.h>
#include<WSML/Keyboard.h>
#include<WSML/Pulse.h>

#ifdef __cplusplus
extern "C" {
#endif

	WSML_API void Cuda_call_from_lib();

	WSML_API void cuda_test_func();

#ifdef __cplusplus
} // extern "C"
#endif

#endif // WSML_H
