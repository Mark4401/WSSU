#ifndef ENGINE_H
#define ENGINE_H

#include<cstdint>

typedef int8_t int8_s;
typedef uint8_t int8_u;

typedef int16_t int16_s;
typedef uint16_t int16_u;

typedef int32_t int32_s;
typedef uint32_t int32_u;

typedef int64_t int64_s;
typedef uint64_t int64_u;

#ifdef _WIN32
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else
#define ENGINE_API
#endif


#ifdef __cplusplus
extern "C" {
#endif

    /*
    
        - LEGACY STRUCTS
	    - REFERENCE USE ONLY!

    struct	CLIENT
    {
        int                 Width;
        int                 Height;
        const wchar_t*      Title;
        bool                Active_black_title_bar;
    };

    */
    ENGINE_API void Default_Systen_info();


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ENGINE_H
