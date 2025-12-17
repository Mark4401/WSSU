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


#ifdef __cplusplus
extern "C" {
#endif

    #define SUCCESSFUL_QUEUE_POST    10
    #define FAILURE_QUEUE_POST       5

    typedef struct	__CLIENT__
    {
        int                 Width;
        int                 Height;
        const wchar_t*      Title;
        bool                Active_black_title_bar;
    }	CLIENT;

    ENGINE_API int Create_Client_Window(CLIENT* Client_reference);
    
    ENGINE_API bool Queue(CLIENT* Client_reference);
    ENGINE_API void Destroy_Client_Window(CLIENT* Client_reference);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ENGINE_H
