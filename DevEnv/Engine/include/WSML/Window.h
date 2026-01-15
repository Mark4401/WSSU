#ifndef WINDOW_H
#define WINDOW_H
#include<WSML/WSML.h>

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

    enum Window_Position
    {
        POS_TOP_LEFT,
        POS_TOP_CENTER,
        POS_TOP_RIGHT,

        CENTER_LEFT,
        CENTER,
        CENTER_RIGHT,

        POS_BOTTOM_LEFT,
        POS_BOTTOM_CENTER,
        POS_BOTTOM_RIGHT
    };
    
    
    WSML_API void Retrieve_All_Active_Window_instances();

    WSML_API void Init_Window(const wchar_t* title, int Width, int Height, bool Black_title_bar, enum Window_Position Position);
    
    WSML_API void Extend_Outer_Window_Borders(int Top, int Bottom, int Left, int Right);

    WSML_API void Process_Lists();

#ifdef __cplusplus
} // extern "C"
#endif

#endif // WINDOW_H
