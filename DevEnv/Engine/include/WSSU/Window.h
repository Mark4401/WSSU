#ifndef WINDOW_H
#define WINDOW_H

#include<WSSU/WSSU.h>

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

    WSSU_API void Retrieve_All_Active_Window_instances();

    WSSU_API void Init_Window(const wchar_t* title, int Width, int Height, bool Black_title_bar, enum Window_Position Position);

    WSSU_API void Process_Lists();

#ifdef __cplusplus
} // extern "C"
#endif

#endif // WINDOW_H
