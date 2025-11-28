#ifndef ENGINE_H
#define ENGINE_H

#ifdef _WIN32
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else
#define ENGINE_API
#endif


// ------------------------------
// CUDA wrapper interface (C linkage)
// ------------------------------
#ifdef __cplusplus
extern "C" {
#endif


    ENGINE_API int Addition(int One, int two);
    ENGINE_API int Subtraction(int One, int two);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // ENGINE_H
