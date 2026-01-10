#ifndef WIN_32_WINDOW_MANAGER_H
#define WIN_32_WINDOW_MANAGER_H

#include<Runtime_variables.h>

void Display_DPI_Properties(bool state);

void Top_Level_Windows();

void Create_Win32_Window(const wchar_t* title, int X_Pos, int Y_Pos,  int Width, int Height, bool Black_title_bar);

static void Retrieve_Window_Destruction_By_User(HWND WIndow);

void ALL_Process_Window_Lists();


#endif // !WIN_32_WINDOW_MANAGER_H
