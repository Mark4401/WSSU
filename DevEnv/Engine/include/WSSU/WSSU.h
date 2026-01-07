#ifndef WSSU_H
#define WSSU_H

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
#ifdef WSSU_EXPORT
#define WSSU_API __declspec(dllexport)
#else
#define WSSU_API __declspec(dllimport)
#endif
#else
#define WSSU_API
#endif

#include<WSSU/Window.h>
#include<WSSU/Keyboard.h>
#include<WSSU/Pulse.h>


#endif // WSSU_H
